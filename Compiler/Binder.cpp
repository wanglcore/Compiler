#include "Binder.h"
namespace Compiler {
auto Binder::BindExpression(std::shared_ptr<ExpressionSyntax> syntax,
                            SyntaxKind kind = SyntaxKind::DefaultToken)
    -> std::shared_ptr<BoundExpression> {
  switch (syntax->Kind) {
    case SyntaxKind::LiteralExpression:
      return BindLiteralExpression(
          std::dynamic_pointer_cast<LiteralExpressionSyntax>(syntax));
    case SyntaxKind::BinaryExpression:
      return BindBinaryExpression(
          std::dynamic_pointer_cast<BinaryExpressionSyntax>(syntax));
    case SyntaxKind::ParenthesizedExpression:
      return BindParenthesizedExpression(
          std::dynamic_pointer_cast<ParenthesizedExpressionSyntax>(syntax));
    case SyntaxKind::UnaryExpression:
      return BindUnaryExpression(
          std::dynamic_pointer_cast<UnaryExpressionSyntax>(syntax));
    case SyntaxKind::NameExpression:
      return BindNameExpression(
          std::dynamic_pointer_cast<NameExpressionSyntax>(syntax),kind);
    case SyntaxKind::AssignmentExpression:
      return BindAssignmentExpression(
          std::dynamic_pointer_cast<AssignmentExpressionSyntax>(syntax));
    default:
      return nullptr;
  }
}
auto Binder::BindExpression(std::shared_ptr<ExpressionSyntax> syntax, Type type)
    -> std::shared_ptr<BoundExpression> {
  if (syntax == nullptr) {
    return nullptr;
  }
  auto result = BindExpression(syntax);
  if (result->type != type) {
    // TODO
  }
  return result;
}
auto Binder::BindLiteralExpression(
    std::shared_ptr<LiteralExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  return std::make_shared<BoundLiteralExpression>(syntax->value, syntax->type);
}

auto Binder::BindBinaryExpression(
    std::shared_ptr<BinaryExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  auto left = BindExpression(syntax->left,syntax->op->Kind);
  auto right = BindExpression(syntax->right,syntax->op->Kind);
  auto oper =
      Operators::BindBinaryOperator(syntax->op->Kind, left->type, right->type);
  /*BindBinaryOperatorKind(syntax->op->Kind,,left->type,right->type)*/
  return std::make_shared<BoundBinaryExpression>(left, oper, right);
}

auto Binder::BindUnaryExpression(std::shared_ptr<UnaryExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  auto boundOperand = BindExpression(syntax->operand);
  auto boundOperator =
      Operators::BindUnaryOperator(syntax->op->Kind, boundOperand->type);
  /* BindUnaryOperatorKind(syntax->op->Kind, boundOperand->type);*/
  return std::make_shared<BoundUnaryExpression>(boundOperator, boundOperand);
}
auto Binder::BindNameExpression(std::shared_ptr<NameExpressionSyntax> syntax,
                                SyntaxKind kind)
    -> std::shared_ptr<BoundExpression> {
  auto name = syntax->identifierToken->text;
  if (VariableSymbol variable; scope->TryLookUp(name, variable)) {
    if ((kind == SyntaxKind::PlusEqualsToken ||
        kind == SyntaxKind::MinusEqualsToken)&&variable.isReadlyOnly==true) {
      std::cout <<"variable "<<name<< " is readonly" << std::endl;
      //return std::make_shared<>(0, Type::IntType);
    }
    return std::make_shared<BoundVariableExpression>(variable);
  }
  /*if (auto value =
          std::find_if(variables.begin(), variables.end(),
                       [name](const std::pair<VariableSymbol, Object>& t) {
                         return t.first.name == name;
                       });
      value != variables.end()) {
    return std::make_shared<BoundVariableExpression>(value->first);
  }*/
  return std::make_shared<BoundLiteralExpression>(0, Type::IntType);
}
auto Binder::BindAssignmentExpression(
    std::shared_ptr<AssignmentExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  auto name = syntax->identifierToken->text;
  auto boundexpression = BindExpression(syntax->expression);
  // auto variable = VariableSymbol(name, boundexpression->type);
  VariableSymbol variable;
  if (!scope->TryLookUp(name, variable)) {
    /*variable = VariableSymbol(name, boundexpression->type);
    scope->TryDeclare(variable);*/
    return boundexpression;
  }
  if (variable.isReadlyOnly) {
    std::cout << "variable is readonly\n";
  }
  if (boundexpression->type != variable.type) {
    return boundexpression;
  }
  return std::make_shared<BoundAssignmentExpression>(variable, boundexpression);
  // if (scope->TryDeclare(variable)) {
  //  return std::make_shared<BoundAssignmentExpression>(variable,
  //                                                     boundexpression);
  //}
  /* Object defaultValue =
       boundexpression->type == Type::IntType
           ? 0
           : Type::BoolType == boundexpression->type ? false : nullptr;*/
  // auto iter = std::find_if(variables.begin(), variables.end(),
  //                         [name](const std::pair<VariableSymbol, Object>& t)
  //                         {
  //                           return t.first.name == name;
  //                         });
  //
  // if (iter != variables.end()) {
  //  variables.erase(iter->first);
  //}
  // variables.emplace(variable, nullptr);
  // return std::make_shared<BoundAssignmentExpression>(variable,
  // boundexpression);
}
auto Binder::BindParenthesizedExpression(
    std::shared_ptr<ParenthesizedExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  return BindExpression(syntax->expression);
}
auto Binder::BindStatement(std::shared_ptr<StatementSyntax> statement)
    -> std::shared_ptr<BoundStatement> {
  switch (statement->Kind) {
    case SyntaxKind::BlockStatement:
      return BindBlockStatement(
          std::dynamic_pointer_cast<BlockStatementSyntax>(statement));
    case SyntaxKind::ExpressionStatement:
      return BindExpressionStatement(
          std::dynamic_pointer_cast<ExpressionStatementSyntax>(statement));
    case SyntaxKind::VariableDeclaration:
      return BindVariableDeclarationStatement(
          std::dynamic_pointer_cast<VariableDeclarationSyntax>(statement));
    case SyntaxKind::IfStatement:
      return BindIfStatement(
          std::dynamic_pointer_cast<IfStatementSyntax>(statement));
    case SyntaxKind::WhileStatement:
      return BindWhileStatement(
          std::dynamic_pointer_cast<WhileStatementSyntax>(statement));
    case SyntaxKind::ForStatement:
      return BindForStatement(
          std::dynamic_pointer_cast<ForStatementSyntax>(statement));
    default:
      break;
  }
}
auto Binder::BindBlockStatement(std::shared_ptr<BlockStatementSyntax> syntax)
    -> std::shared_ptr<BoundStatement> {
  std::vector<std::shared_ptr<BoundStatement>> _statements;
  scope = std::make_shared<BoundScope>(scope);
  for (auto _statement : syntax->statements) {
    auto state = BindStatement(_statement);
    _statements.push_back(state);
  }
  scope = scope->parent;
  return std::make_shared<BoundBlockStatement>(_statements);
}
auto Binder::BindExpressionStatement(
    std::shared_ptr<ExpressionStatementSyntax> syntax)
    -> std::shared_ptr<BoundStatement> {
  auto expression = BindExpression(syntax->expression);
  return std::make_shared<BoundExpressionStatement>(expression);
}
auto Binder::BindVariableDeclarationStatement(
    std::shared_ptr<VariableDeclarationSyntax> syntax)
    -> std::shared_ptr<BoundStatement> {
  auto name = syntax->identifier->text;
  auto isReadOnly = syntax->keyword->Kind == SyntaxKind::LetToken &&
                    syntax->mutkeyword == nullptr;
  auto initializer = BindExpression(syntax->initializer);
  auto variable = VariableSymbol(name, initializer->type, isReadOnly);
  if (scope->TryDeclare(variable)) {
  }
  return std::make_shared<BoundVariableDeclaration>(variable, initializer);
}
auto Binder::BindIfStatement(std::shared_ptr<IfStatementSyntax> syntax)
    -> std::shared_ptr<BoundStatement> {
  auto condition = BindExpression(syntax->condition, Type::BoolType);
  auto statement = BindStatement(syntax->thenstatement);
  auto elseStatement = syntax->elseClause == nullptr
                           ? nullptr
                           : BindStatement(syntax->elseClause->elsestatement);
  return std::make_shared<BoundIfStatement>(condition, statement,
                                            elseStatement);
}
auto Binder::BindWhileStatement(std::shared_ptr<WhileStatementSyntax> syntax)
    -> std::shared_ptr<BoundStatement> {
  auto condition = BindExpression(syntax->condition, Type::BoolType);
  auto statement = BindStatement(syntax->statement);
  return std::make_shared<BoundWhileStatement>(condition, statement);
}
auto Binder::BindForStatement(std::shared_ptr<ForStatementSyntax> syntax)
    -> std::shared_ptr<BoundStatement> {
  auto iterbegin = BindExpression(syntax->iterbegin, Type::IntType);
  auto iterend = BindExpression(syntax->iterend, Type::IntType);
  auto iterstep = BindExpression(syntax->iterstep, Type::IntType);
  scope = std::make_shared<BoundScope>(scope);
  auto name = syntax->identifier->text;
  VariableSymbol variable(name, Type::IntType, true);
  if (!scope->TryDeclare(variable)) {
  }
  auto statement = BindStatement(syntax->statement);
  scope = scope->parent;
  return std::make_shared<BoundForStatement>(variable, iterbegin, iterend,
                                             iterstep, statement);
}
// auto Binder::BindElseClauseStatement(std::shared_ptr<ElseClauseSyntax>
// syntax)
//    -> std::shared_ptr<BoundStatement> {}
//
// inline BoundUnaryOperatorKind Binder::BindUnaryOperatorKind(SyntaxKind kind,
//                                                            Type type) {
//  if (type == Type::IntType) {
//    switch (kind) {
//      case SyntaxKind::PlusToken:
//        return BoundUnaryOperatorKind::Identity;
//      case SyntaxKind::MinusToken:
//        return BoundUnaryOperatorKind::Negation;
//    }
//  } else if (type == Type::BoolType) {
//    switch (kind) {
//      case SyntaxKind::BangToken:
//        return BoundUnaryOperatorKind::LogicalNegation;
//    }
//  } else {
//    return BoundUnaryOperatorKind::DefaultType;
//  }
//}
//
// inline BoundBinaryOperatorKind Binder::BindBinaryOperatorKind(SyntaxKind
// kind,
//                                                              Type lefttype,
//                                                              Type righttype)
//                                                              {
//  if (lefttype == Type::IntType && righttype == Type::IntType) {
//    switch (kind) {
//      case SyntaxKind::PlusToken:
//        return BoundBinaryOperatorKind::Addition;
//      case SyntaxKind::MinusToken:
//        return BoundBinaryOperatorKind::Subtraction;
//      case SyntaxKind::StarToken:
//        return BoundBinaryOperatorKind::Multiplication;
//      case SyntaxKind::SlashToken:
//        return BoundBinaryOperatorKind::Division;
//      default:
//        // throw exception
//        break;
//    }
//  }
//  else if (lefttype == Type::BoolType && righttype == Type::BoolType)
//  {
//    switch (kind) {
//      case SyntaxKind::AmpersandAmpersandToken:
//        return BoundBinaryOperatorKind::LogicalAnd;
//      case SyntaxKind::PipePipeToken:
//        return BoundBinaryOperatorKind::LogicalOr;
//    }
//  }
//  else
//  {
//      return BoundBinaryOperatorKind::DefaultType;
//  }
//}

}  // namespace Compiler