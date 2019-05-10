// functionality related to emitting code

// docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v "$(pwd)":/files tbesard/compilers:pract3
// Instruction reference: https://www.felixcloutier.com/x86/

// 64 bit platform
// stack grows downwards
// parameters to function are passed on the stack in reverse order
// functions are called using the call instruction that pushes the address of the next instruction to the stack and jumps
// the stack is 16-byte aligned just before the call instruction is called
// the return value is stored in the %rax register
// 


#include "ast.hpp"
#include "auxiliary.hpp"
#include "codegen.hpp"

#include <map>

using namespace cheetah;

// LLVM constants
namespace cheetah {
extern llvm::LLVMContext LLVMContext;
}
const auto T_void = llvm::Type::getVoidTy(LLVMContext);
const auto T_int = llvm::Type::getInt64Ty(LLVMContext);

// System V AMD64 ABI
const std::array<std::string, 6> param_regs = {"%rdi", "%rsi", "%rdx",
                                               "%rcx", "%r8",  "%r9"};
const std::string ret_reg = "%rax";
const std::array<std::string, 8> callee_saved_regs = {
    "%rbx", "%rbp", "%rdi", "%rsi", "%r12", "%r13", "%r14", "%r15"};

// main entry-point
Program cheetah::codegen(AST::CompoundStmt *root) {
  auto prog = Program();
  // first generate code for all function declarations...
  AST::CompoundStmt *toplevel = new AST::CompoundStmt();
  for (auto const &S : root->body) {
    if (AST::DeclStmt *D = dynamic_cast<AST::DeclStmt *>(S)) {
      if (AST::FuncDecl *F = dynamic_cast<AST::FuncDecl *>(D->decl)) {
        F->emit(prog);
        continue;
      }
    }
    toplevel->body.push_back(S);
  }
  toplevel->body.push_back(new AST::ReturnStmt(new AST::IntLiteral(0)));

  // then process toplevel code in a fake main function
  auto main = new AST::FuncDecl(new AST::Identifier("main"),
                                llvm::Type::getInt32Ty(LLVMContext),
                                AST::VariableList(), toplevel);
  main->location = root->location;
  main->emit(prog);

  return prog;
}

// global state of variables
static std::map<std::string, int> var_decls;

// 5.4 global state of function parameters
static std::map<std::string, int> func_param;

// global state of functions
static std::string func_exit;
static std::map<std::string, std::tuple<llvm::Type *, size_t>> func_decls = {
    {"echo", std::make_tuple(T_void, 1)}, {"read", std::make_tuple(T_int, 0)}};


//
// Helper functions
//

// operators to emit code into program structures
Program &cheetah::operator<<(Program &prog, Block block) {
  prog.blocks.push_back(block);
  return prog;
}
Program &cheetah::operator<<(Program &prog, Instruction inst) {
  prog.blocks.back().instructions.push_back(inst);
  return prog;
}

// string formatting
template <typename... Args>
std::string str(const std::string &format, Args... args) {
  size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1);
}

// generate a unique label
std::string label(const Program &prog, std::string name) {
  for (int count = 0;; count++) {
    std::string unique_name = str(".%s.%d", name.c_str(), count);

    bool exists = false;
    for (auto const &block : prog.blocks) {
      if (block.name == unique_name) {
        exists = true;
        break;
      }
    }

    if (!exists)
      return unique_name;
  }
}

// return the location of a variable
std::string variable(const AST::Identifier *name) {
  auto it = var_decls.find(name->string);
  if (it == var_decls.end())
    codegen_error("undefined variable " + name->string);

  return str("%d(%%rbp)", it->second);
}

// 5.4 Returns a reference to a parameter
//std::string parameter(size_t i) {
  
//}

//
// Declarations
//

void AST::FuncDecl::emit(Program &prog) const {
  // register the function
  auto it = func_decls.find(name->string);
  if (it != func_decls.end())
    codegen_error("cannot redefine function function " + name->string);
  func_decls[name->string] = std::make_tuple(type, args.size());

  var_decls.clear();

  prog << Block{name->string, true, "start of function " + name->string};
  func_exit = name->string + ".exit";

  // begin function prologue
  // 5.2 save callee-saved registers
  for(const std::string& s : callee_saved_regs){
    prog << Instruction{"pushq", {s}, "save callee-saved register"};
  }


  // 5.4 push parameters onto stack
  //for(const VarDecl * v : args){
  //  v->emit(prog);
  //}

  // 5.2 set the base pointer
  // volgende lijn waarschijnlijk niet nodig aangezien %rbp ook al callee-saved register is
  prog << Instruction{"pushq", {"%rbp"}, "store value of base pointer on stack"};
  prog << Instruction{"movq", {"%rsp", "%rbp"}, "copy value of stack pointer into base pointer"};

  // 5.2 align the stack pointer by 16 bytes
  prog << Instruction{"subq", {"$16", "%rsp"}, "align the stack pointer by 16 bytes"}; // to make room for local variables
  // end function prologue

  body->emit(prog);
  prog << Block{func_exit, false, "end of function " + name->string};

  // begin function epilogue
  // 5.2 restore the stack pointer
  prog << Instruction{"movq", {"%rbp", "%rsp"}, "restore stack pointer value to base pointer value"};
  // volgende lijn waarschijnlijk niet nodig aangezien %rbp ook al callee-saved register is
  prog << Instruction{"popq", {"%rbp"}, "restore base pointer value"};

  // 5.2 restore callee-saved registers
  for(int i = callee_saved_regs.size() - 1; i >= 0; i--){
    prog << Instruction{"popq", {callee_saved_regs[i]}, "restore callee-saved register"};
  }
  // end function epilogue
//
  prog << Instruction{"retq", {}, "return to the caller"};
}

void AST::VarDecl::emit(Program &prog) const {
  // disallow redefinitions
  auto it = var_decls.find(name->string);
  if (it != var_decls.end())
    codegen_error(str("cannot redefine variable '%s'", name->string.c_str()));

  // 5.3 determine the size (you should only support int)
  int size = 4; // 8 bytes = 64 bit

  // 5.3 reserve stack space, making sure the stack remains 16-byte aligned
  prog << Instruction{"subq", {"$4", "%rsp"}, "allocate space for the variable"};

  // 5.3 add the location of the variable relative to the base pointer in var_decls
  if(var_decls.size() == 0){
    var_decls[name->string] = size;
  } else { // find the smallest offset
    int lastOffset = var_decls.begin()->second;
    for(auto it = var_decls.begin(); it != var_decls.end(); it++){
      if(it->second < lastOffset){
        lastOffset = it->second;
      }
    }
    var_decls[name->string] = lastOffset + size;
  }
}


//
// Statements
//

void AST::DeclStmt::emit(Program &prog) const { decl->emit(prog); }

void AST::CompoundStmt::emit(Program &prog) const {
  for (auto const &S : body) {
    S->emit(prog);
    if (dynamic_cast<AST::Expr *>(S) != nullptr) {
      // expressions put stuff on the stack
      prog << Instruction{"popq", {ret_reg}, "discard expr output"};
    }
  }
}

void AST::ReturnStmt::emit(Program &prog) const {
  if (expr) {
    expr->emit(prog);
    prog << Instruction{"popq", {ret_reg}, "return a value"};
  }

  prog << Instruction{"jmp", {func_exit}, "exit function"};
}


// 5.6 If Statement
void AST::IfStmt::emit(Program &prog) const {
  //cond->emit(prog);
  //prog << Block{label(prog, "iftrue"), false};
  //then->emit(prog);
  //prog << Instruction{"jmp", {"next"}};
  //prog << Block{label(prog, "iffalse"), false};
  //elsev->emit(prog);
  //prog << Instruction{"jmp", {"next"}};
  //prog << Block{"next", false};
}

// 5.6 While Statement
void AST::WhileStmt::emit(Program &prog) const {
  codegen_error("TODO: implement WhileStmt");
}

// 5.6 For Statement
void AST::ForStmt::emit(Program &prog) const {
  codegen_error("TODO: implement ForStmt");
}


//
// Expressions
//

void AST::IntLiteral::emit(Program &prog) const {
  prog << Instruction{"pushq", {str("$%d", value)}};
}

void AST::DeclRefExpr::emit(Program &prog) const {
  if (index)
    codegen_error("variable indexes are not supported");
  prog << Instruction{"movq",
                      {variable(decl), "%rax"},
                      str("access variable '%s'", decl->string.c_str())};

  prog << Instruction{"pushq", {"%rax"}};
}

void AST::Assignment::emit(Program &prog) const {
  right->emit(prog);
  prog << Instruction{"popq", {"%rax"}, "assignment RHS"};

  if (left->index)
    codegen_error("variable indexes are not supported");
  prog << Instruction{"movq",
                      {"%rax", variable(left->decl)},
                      "assign variable " + left->decl->string};

  prog << Instruction{"pushq", {"%rax"}, "assignment result"};
}

void AST::CallExpr::emit(Program &prog) const {
  // look up the function declaration
  auto it = func_decls.find(name->string);
  if (it == func_decls.end())
    codegen_error("unknown function " + name->string);
  auto decl = it->second;

  // check arguments
  size_t argc = std::get<1>(decl);
  if (argc != args.size())
    codegen_error(str("invalid call to %s: expected %d arguments, got %d",
                      name->string, argc, args.size()));

  // 5.1 emit and store arguments
  int j = 0;
  for(int i = argc - 1; i >= 0 ; i-- ){ // reverse order!!
    args[i]->emit(prog);
    prog << Instruction{"popq", {param_regs[j]}};
    j++;
  }

  

  // 5.1 generating the call
  prog << Instruction{"call", {name->string}};

  // 5.1 return a value
  if(std::get<0>(decl) == T_void){
    prog << Instruction{"pushq", {"$0xABCDEF"} , "void sentinel value"};
  }else {
    prog << Instruction{"pushq", {"%rax"}, "return value of the function"}; // %rax is the return registerexi
  }
}

void AST::BinaryOp::emit(Program &prog) const {
  left->emit(prog);
  right->emit(prog);

  prog << Instruction{"popq", {"%rbx"}, "binary op RHS"}; // 5
  prog << Instruction{"popq", {"%rax"}, "binary op LHS"}; // 6


  // 5.5 Binary Operators
  switch (op) {
    case cheetah::AST::Operator::PLUS:
      prog << Instruction{"addq", {"%rbx", "%rax"}, "add numbers"}; // 5 + 6, %rax = 11 
      break;
    case cheetah::AST::Operator::MINUS:
      prog << Instruction{"subq", {"%rbx", "%rax"}, "subtract numbers"}; // 5 - 6, %rax = -1
      break;
    case cheetah::AST::Operator::MUL:
      prog << Instruction{"mulq", {"%rbx"}, "multiply"}; // 5 * 6, %rax = 30, 
      break;
    case cheetah::AST::Operator::DIV:
      prog << Instruction{"divq", {"%rbx"}, "divide"};
      prog << Instruction{"addq", {"%rdx", "%rax"}, "add remainder"};
      break;
    case cheetah::AST::Operator::EXP:
      break;
    case cheetah::AST::Operator::MOD:
      prog << Instruction{"divq", {"%rbx"}, "modulo operation"};
      break;
    case cheetah::AST::Operator::EQUAL:
      break;
    case cheetah::AST::Operator::CEQ:  
      prog << Instruction{"cmp", {"%rbx", "%rax"}, "compare operands"};
      prog << Instruction{"pushf", {}, "push vaue of EFLAGS register on stack"};
      prog << Instruction{"popq", {"%rsi"}, "get EFLAGS value"};
      prog << Instruction{"and", {"$64", "%rsi"}, "check if 7th bit is set"}; // zero bit
      prog << Instruction{"shr", {"$6", "%rsi"}};
      prog << Instruction{"movq", {"%rsi", "%rax"}};
      break;
      
    case cheetah::AST::Operator::CNE:
      prog << Instruction{"cmp", {"%rbx", "%rax"}, "compare operands"};
      prog << Instruction{"pushf", {}, "push vaue of EFLAGS register on stack"};
      prog << Instruction{"popq", {"%rsi"}, "get EFLAGS value"};
      prog << Instruction{"not" , {"%rsi"}, "one's complement negation"};
      prog << Instruction{"and", {"$64", "%rsi"}, "check if 7th bit is not set"}; // zero bit
      prog << Instruction{"shr", {"$6", "%rsi"}};
      prog << Instruction{"movq", {"%rsi", "%rax"}};
      break;
    case cheetah::AST::Operator::CLT:
      prog << Instruction{"cmp", {"%rbx", "%rax"}, "compare operands"};
      prog << Instruction{"pushf", {}, "push vaue of EFLAGS register on stack"};
      prog << Instruction{"popq", {"%rsi"}, "get EFLAGS value"};
      
      prog << Instruction{"not" , {"%rsi"}, "one's complement negation"};
      prog << Instruction{"and", {"$64", "%rsi"}, "check if 7th bit is not set"}; // zero bit
      prog << Instruction{"shr", {"$6", "%rsi"}};
      prog << Instruction{"movq", {"%rsi", "%rax"}};
      break;    
    case cheetah::AST::Operator::CLE:
      break;
    case cheetah::AST::Operator::CGT:
      break;
    case cheetah::AST::Operator::CGE:
      break;
  }

  prog << Instruction{"pushq", {"%rax"}, "binary op result"};
}

void AST::UnaryOp::emit(Program &prog) const {
  right->emit(prog);
  prog << Instruction{"popq", {"%rax"}, "unary op RHS"};

  // 5.5 Unary Operators
  switch(op){
    case cheetah::AST::Operator::MINUS:  
      prog << Instruction{"movq", {"$-1", "%rsi"}};
      prog << Instruction{"mulq", {"%rsi"}, "negative number"};
      break;
  }
   // no other unary operations
  prog << Instruction{"pushq", {"%rax"}, "unary op result"};
}


//
// Unsupported
//

void AST::FloatLiteral::emit(Program &) const {
  codegen_error("floating-point literals are not supported");
}

void AST::StringLiteral::emit(Program &) const {
  codegen_error("string literals are not supported");
}
