#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "BoundExpression.h"
#include "BoundStatement.h"
#include "Symbol.h"
#include "Type.h"
namespace Compiler {
class BoundScope {
private:
  std::map<std::string, VariableSymbol> variables;
  std::map<std::string, FunctionSymbol> functions;

public:
  BoundScope(std::shared_ptr<BoundScope> _parent) : parent(_parent) {}
  bool TryDeclareVariable(VariableSymbol variable) {
    auto result = variables.insert(std::make_pair(variable.name, variable));
    return result.second;
  }
  bool TryLookUpVariable(std::string name, VariableSymbol &variable) {
    if (auto iter = variables.find(name); iter != variables.end()) {
      variable = iter->second;
      return true;
    }
    if (parent == nullptr)
      return false;
    return parent->TryLookUpVariable(name, variable);
  }
  bool TryDeclareFunction(FunctionSymbol function) {
    auto result = functions.insert(std::make_pair(function.name, function));
    return result.second;
  }
  bool TryLookUpFunction(std::string name, FunctionSymbol &function) {
    if (auto iter = functions.find(name); iter != functions.end()) {
      function = iter->second;
      return true;
    }
    if (parent == nullptr)
      return false;
    return parent->TryLookUpFunction(name, function);
  }
  std::vector<VariableSymbol> GetDeclaredVariables() {
    std::vector<VariableSymbol> variablekeys;
    for (auto const &pair : variables) {
      variablekeys.push_back(pair.second);
    }
    return variablekeys;
  }
  std::vector<FunctionSymbol> GetDeclaredFunctions() {
    std::vector<FunctionSymbol> functionkeys;
    for (auto const &pair : functions) {
      functionkeys.push_back(pair.second);
    }
    return functionkeys;
  }
  std::shared_ptr<BoundScope> parent;
};

class BoundGlobalScope {
public:
  BoundGlobalScope(std::shared_ptr<BoundGlobalScope> _previous,
                   std::vector<VariableSymbol> _variables,
                   std::shared_ptr<BoundStatement> _statement)
      : previous(_previous), variables(_variables), statement(_statement) {}
  std::shared_ptr<BoundGlobalScope> previous;
  std::vector<VariableSymbol> variables;
  std::shared_ptr<BoundStatement> statement;
};
} // namespace Compiler
