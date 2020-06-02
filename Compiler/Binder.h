#pragma once
#include <map>
#include <stack>

#include "BinaryExpressionSyntax.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "BoundScope.h"
#include "BoundStatement.h"
#include "CompilationUnitSyntax.h"
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
#include "NameAndAssignmentExpressionSyntax.h"
#include "Operator.h"
#include "ParenthesizedExpressionSyntax.h"
#include "UnaryExpressionSyntax.h"
namespace Compiler {
class Binder {
 public:
  Binder(std::shared_ptr<BoundScope> _parent) {
    scope = std::make_shared<BoundScope>(_parent);
  }
  // std::map<VariableSymbol, Object> variables;
  static std::shared_ptr<BoundGlobalScope> BindGlobalScope(
      std::shared_ptr<BoundGlobalScope> previoue,
      std::shared_ptr<CompilationUnitSyntax> syntax) {
    auto parentscope = CreateParentScopes(previoue);
    auto binder = std::make_shared<Binder>(parentscope);
    auto expression = binder->BindStatement(syntax->statement);
    auto _variables = binder->scope->GetDeclaredVariables();
    return std::make_shared<BoundGlobalScope>(previoue, _variables, expression);
  }
  static std::shared_ptr<BoundScope> CreateParentScopes(
      std::shared_ptr<BoundGlobalScope> previous) {
    std::stack<std::shared_ptr<BoundGlobalScope>> scopestack;
    while (previous != nullptr) {
      scopestack.push(previous);
      previous = previous->previous;
    }
    std::shared_ptr<BoundScope> parent = nullptr;
    while (!scopestack.empty()) {
      auto scope = std::make_shared<BoundScope>(parent);
      previous = scopestack.top();
      scopestack.pop();
      for (auto u : previous->variables) {
        scope->TryDeclare(u);
      }
      parent = scope;
    }
    return parent;
  }
  std::shared_ptr<BoundScope> scope;
  auto BindExpression(std::shared_ptr<ExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindLiteralExpression(std::shared_ptr<LiteralExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindBinaryExpression(std::shared_ptr<BinaryExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindUnaryExpression(std::shared_ptr<UnaryExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindNameExpression(std::shared_ptr<NameExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindAssignmentExpression(
      std::shared_ptr<AssignmentExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindParenthesizedExpression(
      std::shared_ptr<ParenthesizedExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindStatement(std::shared_ptr<StatementSyntax> statement)
      -> std::shared_ptr<BoundStatement>;
  auto BindBlockStatement(std::shared_ptr<BlockStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindExpressionStatement(std::shared_ptr<ExpressionStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;

 private:
  // BoundUnaryOperatorKind BindUnaryOperatorKind(SyntaxKind kind, Type type);
  // BoundBinaryOperatorKind BindBinaryOperatorKind(SyntaxKind kind, Type
  // lefttype,
  //                                               Type righttype);
};
}  // namespace Compiler