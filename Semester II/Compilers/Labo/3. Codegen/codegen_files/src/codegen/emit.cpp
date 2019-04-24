// functionality related to emitting code

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

  // TODO: implement function prologue

  body->emit(prog);

  prog << Block{func_exit, false, "end of function " + name->string};

  // TODO: implement function epilogue

  prog << Instruction{"retq", {}, "return to the caller"};
}

void AST::VarDecl::emit(Program &prog) const {
  // disallow redefinitions
  auto it = var_decls.find(name->string);
  if (it != var_decls.end())
    codegen_error(str("cannot redefine variable '%s'", name->string.c_str()));

  codegen_error("TODO: implement VarDecl");
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
      prog << Instruction{"popq", {"%rax"}, "discard expr output"};
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

void AST::IfStmt::emit(Program &prog) const {
  codegen_error("TODO: implement IfStmt");
}

void AST::WhileStmt::emit(Program &prog) const {
  codegen_error("TODO: implement WhileStmt");
}

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

  codegen_error("TODO: implement CallExpr");
}

void AST::BinaryOp::emit(Program &prog) const {
  left->emit(prog);
  right->emit(prog);

  prog << Instruction{"popq", {"%rbx"}, "binary op RHS"};
  prog << Instruction{"popq", {"%rax"}, "binary op LHS"};

  switch (op) {
  default:
    codegen_error("TODO: implement BinaryOp");
  }

  prog << Instruction{"pushq", {"%rax"}, "binary op result"};
}

void AST::UnaryOp::emit(Program &prog) const {
  right->emit(prog);
  prog << Instruction{"popq", {"%rax"}, "unary op RHS"};

  switch (op) {
  default:
    codegen_error("TODO: implement UnaryOp");
  }

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
