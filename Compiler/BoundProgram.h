#pragma once
#include <map>
#include <memory>
#include <string>

#include "BoundScope.h"
#include "BoundStatement.h"
#include "Symbol.h"
namespace Compiler {
class BoundProgram final {
 public:
  BoundProgram(
      std::map<FunctionSymbol, std::shared_ptr<BoundBlockStatement>> _functions,
      std::shared_ptr<BoundGlobalScope> _statement)
      : functions(_functions), statement(_statement) {}
  std::map<FunctionSymbol, std::shared_ptr<BoundBlockStatement>> functions;
  std::shared_ptr<BoundGlobalScope> statement;
};
}  // namespace Compiler