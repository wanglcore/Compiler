#pragma once
#include <map>
#include <stack>

#include "AllExpressionSyntax.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "BoundScope.h"
#include "BoundStatement.h"
#include "CompilationUnitSyntax.h"
#include "ConditionStatement.h"
#include "ExpressionSyntax.h"
#include "Operator.h"
namespace Compiler {
class Binder {
public:
  Binder(std::shared_ptr<BoundScope> _parent) {
    scope = std::make_shared<BoundScope>(_parent);
  }
  // std::map<VariableSymbol, Object> variables;
  static std::shared_ptr<BoundGlobalScope>
  BindGlobalScope(std::shared_ptr<BoundGlobalScope> previoue,
                  std::shared_ptr<CompilationUnitSyntax> syntax) {
    auto parentscope = CreateParentScopes(previoue);

    auto binder = std::make_shared<Binder>(parentscope);
    auto expression = binder->BindStatement(syntax->statement);
    auto _variables = binder->scope->GetDeclaredVariables();
    return std::make_shared<BoundGlobalScope>(previoue, _variables, expression);
  }
  static std::shared_ptr<BoundScope>
  CreateParentScopes(std::shared_ptr<BoundGlobalScope> previous) {
    std::stack<std::shared_ptr<BoundGlobalScope>> scopestack;
    while (previous != nullptr) {
      scopestack.push(previous);
      previous = previous->previous;
    }
    auto parent = CreateRootScope();
    while (!scopestack.empty()) {
      auto scope = std::make_shared<BoundScope>(parent);
      previous = scopestack.top();
      scopestack.pop();
      for (auto u : previous->variables) {
        scope->TryDeclareVariable(u);
      }
      parent = scope;
    }
    return parent;
  }
  static auto CreateRootScope() -> std::shared_ptr<BoundScope> {
    auto result = std::make_shared<BoundScope>(nullptr);
    return result;
  }
  auto LookupType(std::string name) -> TypeSymbol {
    if (name == "bool")
      return BaseType::Bool;
    else if (name == "int")
      return BaseType::Int;
    else if (name == "string")
      return BaseType::String;
    else {
      return BaseType::Default;
    }
  }
  std::shared_ptr<BoundScope> scope;
  auto BindExpressionInternal(std::shared_ptr<ExpressionSyntax> syntax,
                              SyntaxKind kind)
      -> std::shared_ptr<BoundExpression>;
  auto BindExpression(std::shared_ptr<ExpressionSyntax> syntax, bool canBeVoid)
      -> std::shared_ptr<BoundExpression>;
  auto BindExpression(std::shared_ptr<ExpressionSyntax> syntax, TypeSymbol type)
      -> std::shared_ptr<BoundExpression>;
  auto BindLiteralExpression(std::shared_ptr<LiteralExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindBinaryExpression(std::shared_ptr<BinaryExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindUnaryExpression(std::shared_ptr<UnaryExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindNameExpression(std::shared_ptr<NameExpressionSyntax> syntax,
                          SyntaxKind kind) -> std::shared_ptr<BoundExpression>;
  auto
  BindAssignmentExpression(std::shared_ptr<AssignmentExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindParenthesizedExpression(
      std::shared_ptr<ParenthesizedExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindStatement(std::shared_ptr<StatementSyntax> statement)
      -> std::shared_ptr<BoundStatement>;
  auto BindBlockStatement(std::shared_ptr<BlockStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto
  BindExpressionStatement(std::shared_ptr<ExpressionStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindVariableDeclarationStatement(
      std::shared_ptr<VariableDeclarationSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindIfStatement(std::shared_ptr<IfStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindWhileStatement(std::shared_ptr<WhileStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindForStatement(std::shared_ptr<ForStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindCallExpression(std::shared_ptr<CallExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  // auto BindElseClauseStatement(
  //    std::shared_ptr<ElseClauseSyntax> syntax)
  //    -> std::shared_ptr<BoundStatement>;
  auto BindConversion(TypeSymbol type, std::shared_ptr<ExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression> {
    auto expression = BindExpression(syntax, false);
    // if (expression->type == type)
    return expression;
    /*
      auto conversion = Conversion.Classify(expression.Type,type);
      if(!conversion.Exists){

      }
      return std::make_shared<BoundConversionExpression>(type,expression);
    */
  }

private:
  // BoundUnaryOperatorKind BindUnaryOperatorKind(SyntaxKind kind, Type type);
  // BoundBinaryOperatorKind BindBinaryOperatorKind(SyntaxKind kind, Type
  // lefttype,
  //                                               Type righttype);
};
} // namespace Compiler
