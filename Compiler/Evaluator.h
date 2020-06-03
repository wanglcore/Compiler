#pragma once
#include <map>
#include <memory>
#include <string>

#include "BinaryExpressionSyntax.h"
#include "Binder.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
#include "ParenthesizedExpressionSyntax.h"
#include "SyntaxTree.h"
#include "Type.h"
#include "UnaryExpressionSyntax.h"
#include "VariableDeclarationSyntax.h"
namespace Compiler {
class Evaluator {
 public:
  Evaluator(std::shared_ptr<BoundStatement> _root,
            std::map<VariableSymbol, Object> &_variables)
      : root(_root), variables(_variables) {}
  Object Evaluate();
  Object lastValue{0};
  Object EvaluateExpression(std::shared_ptr<BoundExpression> _root);
  void EvaluateStatement(std::shared_ptr<BoundStatement> _root);
  void EvaluateBlockStatement(std::shared_ptr<BoundBlockStatement> statement);
  void EvaluateIfStatement(std::shared_ptr<BoundIfStatement> statement);
  void EvaluateVariableDeclaration(
      std::shared_ptr<BoundVariableDeclaration> statement);
  void EvaluateExpressionStatement(
      std::shared_ptr<BoundExpressionStatement> statement);
  // std::shared_ptr<BoundExpression> root;
  std::shared_ptr<BoundStatement> root;
  std::map<VariableSymbol, Object> &variables;
  template <typename T>
  bool Equals(T T1, T T2) {
    return T1 == T2;
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
    auto boundexpression = globalScope->statement;
    auto evaluator = std::make_unique<Evaluator>(boundexpression, variables);
    return std::make_unique<EvaluationResult>(evaluator->Evaluate());
  }
};

}  // namespace Compiler