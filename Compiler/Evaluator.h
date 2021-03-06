#pragma once
#include <map>
#include <memory>
#include <stack>
#include <string>

#include "AllExpressionSyntax.h"
#include "Binder.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "ExpressionSyntax.h"
#include "Symbol.h"
#include "SyntaxTree.h"
#include "Type.h"
namespace Compiler {
class Evaluator {
 public:
  Evaluator(std::shared_ptr<BoundProgram> _program,
            std::map<VariableSymbol, Object> &_variables)
      : program(_program), variables(_variables),functionBodys(_program->functions) {}
  std::shared_ptr<BoundProgram> program;
  std::map<VariableSymbol, Object> &variables;
  std::map<FunctionSymbol, std::shared_ptr<BoundBlockStatement>> functionBodys;
  std::stack<std::map<VariableSymbol, Object>> locals;
  Object Evaluate();
  Object Evaluate(std::shared_ptr<BoundStatement> statement) {
    EvaluateStatement(statement);
    return lastValue;
  }
  Object lastValue{0};
  Object EvaluateExpression(std::shared_ptr<BoundExpression> _root);
  Object EvaluateCallExpression(std::shared_ptr<BoundCallExpression> statement);
  void EvaluateStatement(std::shared_ptr<BoundStatement> _root);
  void EvaluateBlockStatement(std::shared_ptr<BoundBlockStatement> statement);
  void EvaluateIfStatement(std::shared_ptr<BoundIfStatement> statement);
  void EvaluateWhileStatement(std::shared_ptr<BoundWhileStatement> statement);
  void EvaluateDoWhileStatement(std::shared_ptr<BoundDoWhileStatement> statement);
  void EvaluateForStatement(std::shared_ptr<BoundForStatement> statement);
  void EvaluateVariableDeclaration(
      std::shared_ptr<BoundVariableDeclaration> statement);
  void EvaluateExpressionStatement(
      std::shared_ptr<BoundExpressionStatement> statement);
  // std::shared_ptr<BoundExpression> root;
  template <typename T>
  bool Equals(T T1, T T2) {
    return T1 == T2;
  }
  Object EvaluateConversionExpression(
      std::shared_ptr<BoundConversionExpression> syntax) {
    auto value = EvaluateExpression(syntax->expression);
    if (syntax->type == BuildinType::Bool) {
      switch (value.index()) {
        case 0 /* constant-expression */:
          /* code */
          return (bool)std::get<0>(value);
          break;
        case 1:
          return (bool)std::get<1>(value);
        default:
          return 0;
      }
    } else if (syntax->type == BuildinType::Int) {
      switch (value.index()) {
        case 0 /* constant-expression */:
          /* code */
          return (int)std::get<0>(value);
          break;
        case 1:
          return (int)std::get<1>(value);
        default:
          return 0;
      }
    } else if (syntax->type == BuildinType::String) {
      switch (value.index()) {
        case 0 /* constant-expression */:
          /* code */
          return std::to_string(std::get<0>(value));
          break;
        case 1:
          return std::to_string(std::get<1>(value));
        case 2:
          return std::get<2>(value);
        default:
          return 0;
      }
    }
  }
};

class EvaluationResult {
 public:
  EvaluationResult(Object _value) : value(_value) {}
  Object value;
};

class Compilation {
 public:
  Compilation(std::shared_ptr<Compilation> _previous,
              std::shared_ptr<SyntaxTree> _syntax)
      : previous(_previous), syntax(_syntax) {}
  Compilation(std::shared_ptr<SyntaxTree> _syntax)
      : Compilation(nullptr, _syntax) {}
  std::shared_ptr<BoundGlobalScope> globalScope;
  std::shared_ptr<Compilation> previous;
  inline std::shared_ptr<BoundGlobalScope> GetglobalScope() {
    if (globalScope == nullptr) {
      globalScope = Binder::BindGlobalScope(
          previous == nullptr ? nullptr : previous->globalScope, syntax->root);
    }
    return globalScope;
  }
  std::shared_ptr<Compilation> ContinueWith(
      std::shared_ptr<SyntaxTree> _syntax) {
    return std::make_shared<Compilation>(std::make_shared<Compilation>(*this),
                                         _syntax);
  }

  std::shared_ptr<SyntaxTree> syntax;
  std::unique_ptr<EvaluationResult> Evaluate(
      std::map<VariableSymbol, Object> &variables) {
    auto _globalScope = GetglobalScope();
    auto program = Binder::BindProgram(_globalScope);
    auto boundexpression = globalScope->statement;
    auto evaluator = std::make_unique<Evaluator>(program, variables);
    return std::make_unique<EvaluationResult>(evaluator->Evaluate());
  }
};

}  // namespace Compiler
