//
// Configuration
//

#include <list>
#include <map>
#include <sstream>

#include "ast.hpp"


//
// Helpers
//

namespace cheetah {

size_t count = 0;
std::string unique(const std::string &type) {
  count += 1;
  return type + std::to_string(count);
}

template <typename T> std::string stringify(T *obj) {
  std::string str;
  llvm::raw_string_ostream rso(str);
  obj->print(rso);
  return str;
}

std::string quote(const std::string &val) { return "'" + val + "'"; }


//
// DOT creation
//

typedef std::string Node;

Node node(llvm::raw_ostream &out, const std::string &name,
          const std::list<std::pair<std::string, std::string>> &records = {},
          const std::map<std::string, std::string> &extra_options = {}) {
  std::string id = unique(name);

  auto options(extra_options);

  std::stringstream label;
  label << "{" << name;
  if (records.size() > 0) {
    label << "|{";
    bool first = true;
    for (auto record : records) {
      if (first)
        first = false;
      else
        label << "|";
      label << "<" << record.first << ">" << record.second;
    }
    label << "}";
  }
  label << "}";
  options["label"] = label.str();

  out << id << " [";
  for (auto option : options)
    out << option.first << "=\"" << option.second << "\", ";
  out << "];\n";

  return id;
}

Node record(const Node &id, const std::string &rec) { return id + ":" + rec; }

void edge(llvm::raw_ostream &out, const Node &a, const Node &b,
          const std::map<std::string, std::string> &options = {}) {
  out << a << " -- " << b << " [";
  for (auto option : options)
    out << option.first << "=\"" << option.second << "\", ";
  out << "];\n";
}

// Higher-level helpers

Node decl(llvm::raw_ostream &out, const std::string &name,
          const std::list<std::pair<std::string, std::string>> &records = {},
          const std::map<std::string, std::string> &extra_options = {}) {
  auto options(extra_options);
  options["color"] = "green";

  return node(out, name, records, options);
}

Node stmt(llvm::raw_ostream &out, const std::string &name,
          const std::list<std::pair<std::string, std::string>> &records = {},
          const std::map<std::string, std::string> &extra_options = {}) {
  auto options(extra_options);
  options["color"] = "red";

  return node(out, name, records, options);
}

Node expr(llvm::raw_ostream &out, const std::string &name,
          const std::list<std::pair<std::string, std::string>> &records = {},
          const std::map<std::string, std::string> &extra_options = {}) {
  auto options(extra_options);
  options["color"] = "blue";

  return node(out, name, records, options);
}


//
// Declarations
//

Node AST::VarDecl::dump(llvm::raw_ostream &out) const {
  auto id = decl(out, "Var",
                 {{"name", quote(name->string)},
                  {"type", stringify(type)},
                  {"init", "init?"}});
  if (init)
    edge(out, record(id, "init"), init->dump(out));
  return id;
}

Node AST::FuncDecl::dump(llvm::raw_ostream &out) const {
  auto id = decl(out, "Func", {{"name", quote(name->string)}});
  edge(out, id, body->dump(out));
  return id;
}


//
// Statements
//

Node AST::DeclStmt::dump(llvm::raw_ostream &out) const {
  // passthrough
  return decl->dump(out);
}

Node AST::ReturnStmt::dump(llvm::raw_ostream &out) const {
  auto id = stmt(out, "Return");
  if (expr)
    edge(out, id, expr->dump(out));
  return id;
}

bool active = false;
Node AST::CompoundStmt::dump(llvm::raw_ostream &out) const {
  bool activated = false;
  if (!active) {
    out << "graph {\n"
        << "node [shape=record];\n";
    active = true;
    activated = true;
  }
  auto id = stmt(out, "Compound");
  for (auto S : body)
    edge(out, id, S->dump(out));
  if (activated) {
    out << "}\n";
    active = false;
  }
  return id;
}

Node AST::IfStmt::dump(llvm::raw_ostream &out) const {
  auto id =
      stmt(out, "If", {{"cond", "cond"}, {"then", "then"}, {"else", "else?"}});
  edge(out, record(id, "cond"), cond->dump(out));
  edge(out, record(id, "then"), then->dump(out));
  if (elsev)
    edge(out, record(id, "else"), elsev->dump(out));
  return id;
}

Node AST::WhileStmt::dump(llvm::raw_ostream &out) const {
  auto id = stmt(out, "While", {{"cond", "cond"}, {"body", "body"}});
  edge(out, record(id, "cond"), cond->dump(out));
  edge(out, record(id, "body"), body->dump(out));
  return id;
}

Node AST::ForStmt::dump(llvm::raw_ostream &out) const {
  auto id = stmt(
      out, "For",
      {{"init", "init"}, {"cond", "cond"}, {"inc", "inc"}, {"body", "body"}});
  edge(out, record(id, "init"), init->dump(out));
  edge(out, record(id, "cond"), cond->dump(out));
  edge(out, record(id, "inc"), inc->dump(out));
  edge(out, record(id, "body"), body->dump(out));
  return id;
}


//
// Expressions
//


Node AST::IntLiteral::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "IntLiteral", {{"value", std::to_string(value)}});
  return id;
}

Node AST::FloatLiteral::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "FloatLiteral", {{"value", std::to_string(value)}});
  return id;
}

Node AST::StringLiteral::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "StringLiteral", {{"value", quote(value)}});
  return id;
}

Node AST::UnaryOp::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "UnaryOp", {{"right", to_string(op)}});
  edge(out, record(id, "right"), right->dump(out));
  return id;
}

Node AST::BinaryOp::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "BinaryOp",
                 {{"left", "left"}, {"op", to_string(op)}, {"right", "right"}});
  edge(out, record(id, "left"), left->dump(out));
  edge(out, record(id, "right"), right->dump(out));
  return id;
}

Node AST::DeclRefExpr::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "DeclRef",
                 {{"decl", quote(decl->string)}, {"index", "index?"}});
  if (index)
    edge(out, record(id, "index"), index->dump(out));
  return id;
}

Node AST::CallExpr::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "Call", {{"name", quote(name->string)}});
  for (auto *arg : args)
    edge(out, id, arg->dump(out));
  return id;
}

Node AST::Assignment::dump(llvm::raw_ostream &out) const {
  auto id = expr(out, "Assignment", {{"left", "left"}, {"right", "right"}});
  edge(out, record(id, "left"), left->dump(out));
  edge(out, record(id, "right"), right->dump(out));
  return id;
}

} // namespace cheetah
