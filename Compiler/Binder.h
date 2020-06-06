#pragma once
#include <map>
#include <set>
#include <stack>

#include "AllExpressionSyntax.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "BoundProgram.h"
#include "BoundScope.h"
#include "BoundStatement.h"
#include "CompilationUnitSyntax.h"
#include "ConditionStatement.h"
#include "Conversion.h"
#include "ExpressionSyntax.h"
#include "Operator.h"
namespace Compiler {
class Binder {
public:
  Binder(std::shared_ptr<BoundScope> _parent,
         std::shared_ptr<FunctionSymbol> _function) {
    scope = std::make_shared<BoundScope>(_parent);
    function = _function;
  }
  std::shared_ptr<BoundProgram> program;
  std::shared_ptr<FunctionSymbol> function;
  // std::map<VariableSymbol, Object> variables;
  static std::shared_ptr<BoundGlobalScope>
  BindGlobalScope(std::shared_ptr<BoundGlobalScope> previoue,
                  std::shared_ptr<CompilationUnitSyntax> syntax) {
    auto parentscope = CreateParentScopes(previoue);
    auto binder = std::make_shared<Binder>(parentscope, nullptr);
    std::vector<std::shared_ptr<BoundStatement>> statements;
    for (auto member : syntax->members) {
      if (member->Kind == SyntaxKind::FunctionDeclarition) {
        binder->BindFunctionDeclaration(
            std::dynamic_pointer_cast<FunctionDeclaritionSyntax>(member));
      } else if (member->Kind == SyntaxKind::GlobalStatement) {
        auto globalstatement =
            std::dynamic_pointer_cast<GlobalStatementSyntax>(member);
        auto statement = binder->BindStatement(globalstatement->statement);
        statements.emplace_back(statement);
      }
    }
    auto statement = std::make_shared<BoundBlockStatement>(statements);
    auto _variables = binder->scope->GetDeclaredVariables();
    auto _functions = binder->scope->GetDeclaredFunctions();
    return std::make_shared<BoundGlobalScope>(previoue, _variables, _functions,
                                              statement);
  }
  static std::shared_ptr<BoundProgram>
  BindProgram(std::shared_ptr<BoundGlobalScope> globalScope) {
    auto parentScope = CreateParentScopes(globalScope);
    std::map<FunctionSymbol, std::shared_ptr<BoundBlockStatement>>
        functionBodys;
    for (auto function : globalScope->functions) {
      auto binder = std::make_shared<Binder>(parentScope, nullptr);
      // body的类型是boundBlockStatement
      auto body = binder->BindStatement(function.declaration->statement);
      auto bodyblock = std::dynamic_pointer_cast<BoundBlockStatement>(body);
      functionBodys.insert(std::make_pair(function, bodyblock));
    }
    return std::make_shared<BoundProgram>(functionBodys, globalScope);
  }
  void BindFunctionDeclaration(
      std::shared_ptr<FunctionDeclaritionSyntax> _function) {
    std::vector<ParameterSymbol> parameters;
    std::set<std::string> seenparameter;
    for (auto parameterSyntax : _function->parameters) {
      auto name = parameterSyntax->identifier->text;
      auto type = BindTypeClause(parameterSyntax->type);
      if (auto result = seenparameter.insert(name); result.second == true) {
        ParameterSymbol parameter(name, type);
        parameters.emplace_back(parameter);
      } else {
        // todo add error
      }
    }
    auto _functiontype = BindTypeClause(_function->type);
    auto type =
        _functiontype == BuildinType::Default ? BuildinType::Void : _functiontype;
    // there is temporary code
    if (type != BuildinType::Void) {
      //当前只支持void
    }
    FunctionSymbol function(_function->identifier->text, parameters, type,
                            _function);
    if (!scope->TryDeclareFunction(function)) {
      // todo 函数重复定义error
    }
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
      for (auto f : previous->functions) {
        scope->TryDeclareFunction(f);
      }
      for (auto u : previous->variables) {
        scope->TryDeclareVariable(u);
      }
      parent = scope;
    }
    return parent;
  }
  static inline auto CreateRootScope() -> std::shared_ptr<BoundScope> {
    auto result = std::make_shared<BoundScope>(nullptr);
    return result;
  }
  auto LookupType(std::string name) -> BuildinType {
    if (name == "bool")
      return BuildinType::Bool;
    else if (name == "int")
      return BuildinType::Int;
    else if (name == "string")
      return BuildinType::String;
    else if (name == "void")
      return BuildinType::Void;
    else {
      return BuildinType::Default;
    }
  }
  std::shared_ptr<BoundScope> scope;
  auto BindExpressionInternal(std::shared_ptr<ExpressionSyntax> syntax,
                              SyntaxKind kind)
      -> std::shared_ptr<BoundExpression>;
  auto BindExpression(std::shared_ptr<ExpressionSyntax> syntax, bool canBeVoid)
      -> std::shared_ptr<BoundExpression>;
  auto BindExpression(std::shared_ptr<ExpressionSyntax> syntax,
                      BuildinType type) -> std::shared_ptr<BoundExpression>;
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
  auto BindDoWhileStatement(std::shared_ptr<DoWhileStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindForStatement(std::shared_ptr<ForStatementSyntax> syntax)
      -> std::shared_ptr<BoundStatement>;
  auto BindCallExpression(std::shared_ptr<CallExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindTypeClause(std::shared_ptr<SyntaxToken> syntax) -> BuildinType {
    if (syntax == nullptr)
      return BuildinType::Default;
    auto type = LookupType(syntax->text);
    if (type == BuildinType::Default) {
      // TODO ADD ERROR
      // return BuildinType::Default;
    }
    return type;
  }
  // auto BindElseClauseStatement(
  //    std::shared_ptr<ElseClauseSyntax> syntax)
  //    -> std::shared_ptr<BoundStatement>;
  auto BindConversion(BuildinType type,
                      std::shared_ptr<ExpressionSyntax> syntax,
                      bool allowExplicit = false)
      -> std::shared_ptr<BoundExpression> {
    auto expression = BindExpression(syntax, false);
    auto conversion = Convert::Classify(expression->type, type);
    if (!conversion.existes) {
      // if () {
      //   // todo add error
      // }
      return std::make_shared<BoundConversionExpression>(type, expression);
    }
    if (!allowExplicit && conversion.isEmplicit) {
      // add error
    }
    if (conversion.isIdentity) {
      return expression;
    }
    return std::make_shared<BoundConversionExpression>(type, expression);
  }

private:
  // BoundUnaryOperatorKind BindUnaryOperatorKind(SyntaxKind kind, Type type);
  // BoundBinaryOperatorKind BindBinaryOperatorKind(SyntaxKind kind, Type
  // lefttype,
  //                                               Type righttype);
};
} // namespace Compiler
