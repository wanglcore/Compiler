#pragma once
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "BoundStatement.h"
#include "Type.h"
namespace Compiler {
class BoundTreeRewriter {
 public:
  virtual std::shared_ptr<BoundStatement> RewriteStatement(
      std::shared_ptr<BoundStatement> node) {
    switch (node->Kind) {
      case BoundNodeKind::BlockStatement:
        return RewriteBlockStatement(
            std::dynamic_pointer_cast<BoundBlockStatement>(node));
      case BoundNodeKind::VariableDeclaration:
        return RewriteVariableDeclaration(
            std::dynamic_pointer_cast<BoundVariableDeclaration>(node));
      case BoundNodeKind::IfStatement:
        return RewriteIfStatement(
            std::dynamic_pointer_cast<BoundIfStatement>(node));
      case BoundNodeKind::WhileStatement:
        return RewriteWhileStatement(
            std::dynamic_pointer_cast<BoundWhileStatement>(node));
      case BoundNodeKind::ForStatement:
        return RewriteForStatement(
            std::dynamic_pointer_cast<BoundForStatement>(node));
      case BoundNodeKind::LabelStatement:
        return RewriteLabelStatement(
            std::dynamic_pointer_cast<BoundLabelStatement>(node));
      case BoundNodeKind::GotoStatement:
        return RewriteGotoStatement(
            std::dynamic_pointer_cast<BoundGotoStatement>(node));
      case BoundNodeKind::ConditionalGotoStatement:
        return RewriteConditionalGotoStatement(
            std::dynamic_pointer_cast<BoundConditionalGotoStatement>(node));
      case BoundNodeKind::ExpressionStatement:
        return RewriteExpressionStatement(
            std::dynamic_pointer_cast<BoundExpressionStatement>(node));
      default:
        return nullptr;
        //   throw new Exception($ "Unexpected node: {node.Kind}");
    }
  }

  virtual std::shared_ptr<BoundStatement> RewriteBlockStatement(
      std::shared_ptr<BoundBlockStatement> node) {
    std::vector<BoundStatement> builder;
    for (int i = 0; i < node->statements.size(); i++) {
      auto oldStatement = node->statements[i];
      auto newStatement = RewriteStatement(oldStatement);
      if (newStatement != oldStatement) {
        if (builder.empty()) {
          for (auto j = 0; j < i; j++)
            builder.emplace_back(node->statements[j]);
        }
      }
      if (!builder.empty()) builder.emplace_back(newStatement);
    }
    if (builder.empty()) return node;
    return std::make_shared<BoundStatement>(builder);
  }

  virtual std::shared_ptr<BoundStatement> RewriteVariableDeclaration(
      std::shared_ptr<BoundVariableDeclaration> node) {
    auto initializer = RewriteExpression(node->initializer);
    if (initializer == node->initializer) return node;
    return std::make_shared<BoundVariableDeclaration>(node->variable,
                                                      initializer);
  }

  virtual std::shared_ptr<BoundStatement> RewriteIfStatement(
      std::shared_ptr<BoundIfStatement> node) {
    auto condition = RewriteExpression(node->condition);
    auto thenStatement = RewriteStatement(node->thenstatement);
    auto elseStatement = node->elsestatement == nullptr
                             ? nullptr
                             : RewriteStatement(node->elsestatement);
    if (condition == node->condition && thenStatement == node->thenstatement &&
        elseStatement == node->elsestatement)
      return node;

    return std::make_shared<BoundIfStatement>(condition, thenStatement,
                                              elseStatement);
  }

  virtual std::shared_ptr<BoundStatement> RewriteWhileStatement(
      std::shared_ptr<BoundWhileStatement> node) {
    auto condition = RewriteExpression(node->condition);
    auto body = RewriteStatement(node->statement);
    if (condition == node->condition && body == node->statement) return node;

    return std::make_shared<BoundWhileStatement>(condition, body);
  }
  virtual std::shared_ptr<BoundStatement> RewriteForStatement(
      std::shared_ptr<BoundForStatement> node) {
    auto lowerBound = RewriteExpression(node->iterbegin);
    auto upperBound = RewriteExpression(node->iterend);
    auto iterstep = RewriteExpression(node->iterstep);
    auto body = RewriteStatement(node->statement);
    if (lowerBound == node->iterbegin && upperBound == node->iterend &&
        body == node->statement && iterstep == node->iterstep)
      return node;

    return std::make_shared<BoundForStatement>(node->variable, lowerBound,
                                               upperBound, iterstep, body);
  }

  virtual std::shared_ptr<BoundStatement> RewriteLabelStatement(
      std::shared_ptr<BoundLabelStatement> node) {
    return node;
  }

  virtual std::shared_ptr<BoundStatement> RewriteGotoStatement(
      std::shared_ptr<BoundGotoStatement> node) {
    return node;
  }

  virtual std::shared_ptr<BoundStatement> RewriteConditionalGotoStatement(
      std::shared_ptr<BoundConditionalGotoStatement> node) {
    auto condition = RewriteExpression(node->condition);
    if (condition == node->condition) return node;

    return std::make_shared<BoundConditionalGotoStatement>(
        node->label, condition, node->jumpifTrue);
  }

  virtual std::shared_ptr<BoundStatement> RewriteExpressionStatement(
      std::shared_ptr<BoundExpressionStatement> node) {
    auto expression = RewriteExpression(node->expression);
    if (expression == node->expression) return node;

    return std::make_shared<BoundExpressionStatement>(expression);
  }

  virtual std::shared_ptr<BoundExpression> RewriteExpression(
      std::shared_ptr<BoundExpression> node) {
    switch (node->Kind) {
      // case BoundNodeKind::ErrorExpression:
      //   return RewriteErrorExpression((BoundErrorExpression)node);
      case BoundNodeKind::LiteralExpression:
        return RewriteLiteralExpression(
            std::dynamic_pointer_cast<BoundLiteralExpression>(node));
      case BoundNodeKind::VariableExpression:
        return RewriteVariableExpression(
            std::dynamic_pointer_cast<BoundVariableExpression>(node));
      case BoundNodeKind::AssignmentExpression:
        return RewriteAssignmentExpression(
            std::dynamic_pointer_cast<BoundAssignmentExpression>(node));
      case BoundNodeKind::UnaryExpression:
        return RewriteUnaryExpression(
            std::dynamic_pointer_cast<BoundUnaryExpression>(node));
      case BoundNodeKind::BinaryExpression:
        return RewriteBinaryExpression(
            std::dynamic_pointer_cast<BoundBinaryExpression>(node));
      case BoundNodeKind::CallExpression:
        return RewriteCallExpression(
            std::dynamic_pointer_cast<BoundCallExpression>(node));
      case BoundNodeKind::ConversionExpression:
        return RewriteConversionExpression(
            std::dynamic_pointer_cast<BoundConversionExpression>(node));
      default:
        return nullptr;
        //   throw std::make_shared<Exception>($ "Unexpected node:
        //   {node.Kind}");
    }
  }

  //   virtual BoundExpression RewriteErrorExpression(BoundErrorExpression node)
  //   {
  //     return node;
  //   }

  virtual std::shared_ptr<BoundExpression> RewriteLiteralExpression(
      std::shared_ptr<BoundLiteralExpression> node) {
    return node;
  }

  virtual std::shared_ptr<BoundExpression> RewriteVariableExpression(
      std::shared_ptr<BoundVariableExpression> node) {
    return node;
  }

  virtual std::shared_ptr<BoundExpression> RewriteAssignmentExpression(
      std::shared_ptr<BoundAssignmentExpression> node) {
    auto expression = RewriteExpression(node->expression);
    if (expression == node->expression) return node;

    return std::make_shared<BoundAssignmentExpression>(node->symbol,
                                                       expression);
  }

  virtual std::shared_ptr<BoundExpression> RewriteUnaryExpression(
      std::shared_ptr<BoundUnaryExpression> node) {
    auto operand = RewriteExpression(node->operand);
    if (operand == node->operand) return node;

    return std::make_shared<BoundUnaryExpression>(node->op, operand);
  }

  virtual std::shared_ptr<BoundExpression> RewriteBinaryExpression(
      std::shared_ptr<BoundBinaryExpression> node) {
    auto left = RewriteExpression(node->left);
    auto right = RewriteExpression(node->right);
    if (left == node->left && right == node->right) return node;

    return std::make_shared<BoundBinaryExpression>(left, node->op, right);
  }

  virtual std::shared_ptr<BoundExpression> RewriteCallExpression(
      std::shared_ptr<BoundCallExpression> node) {
    std::vector<std::shared_ptr<BoundExpression>> builder;

    for (auto i = 0; i < node->arguments.size(); i++) {
      auto oldArgument = node->arguments[i];
      auto newArgument = RewriteExpression(oldArgument);
      if (newArgument != oldArgument) {
        if (builder.empty()) {
          for (int j = 0; j < i; j++) builder.emplace_back(node->arguments[j]);
        }
      }
      if (!builder.empty()) builder.emplace_back(newArgument);
    }

    if (!builder.empty()) return node;

    return std::make_shared<BoundCallExpression>(node->function, builder);
  }

  virtual std::shared_ptr<BoundExpression> RewriteConversionExpression(
      std::shared_ptr<BoundConversionExpression> node) {
    auto expression = RewriteExpression(node->expression);
    if (expression == node->expression) return node;
    return std::make_shared<BoundConversionExpression>(node->type, expression);
  }
};
}  // namespace Compiler
