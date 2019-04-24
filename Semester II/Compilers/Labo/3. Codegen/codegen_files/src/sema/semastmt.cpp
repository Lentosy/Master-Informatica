//
// Configuration
//

#include "ast.hpp"
#include "auxiliary.hpp"
#include "sema.hpp"

#define DEBUG_TYPE "cheetah::sema"

using namespace cheetah;

AST::CompoundStmt *
Sema::ParseCompoundStmt(const Location &Loc, AST::Stmt *SubStmt,
                        AST::CompoundStmt *RunningCompoundStmt) {
  // Re-use any running compound statement (this is due to how we parse groups
  // of statements)
  auto *CompoundStmt = RunningCompoundStmt;
  if (CompoundStmt == nullptr)
    CompoundStmt = new AST::CompoundStmt();

  // Ignore empty statements
  if (SubStmt != nullptr)
    CompoundStmt->push_back(SubStmt);

  CompoundStmt->location = Loc;

  return CompoundStmt;
}
