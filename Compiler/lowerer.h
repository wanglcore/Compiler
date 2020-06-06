#pragma once
#include <string>
#include <vector>

#include "BoundTreeRewriter.h"
#include "Operator.h"
namespace Compiler {

class Lowerer : BoundTreeRewriter {
 public:
  int labelCount{0};
  BoundLabel GenerateLabel() {
    auto name = "Label" + std::to_string(++labelCount);
    return BoundLabel(name);
  }
  static std::shared_ptr<BoundBlockStatement> Lower(
      std::shared_ptr<BoundStatement> statement) {
    Lowerer lower;
    auto result = lower.RewriteStatement(statement);
    return Flatten(result);
  }
  static std::shared_ptr<BoundBlockStatement> Flatten(
      std::shared_ptr<BoundStatement> statement) {}

 private:
  std::shared_ptr<BoundStatement> RewriteIfStatement(
      std::shared_ptr<BoundIfStatement> node) override {
    if (node->elsestatement == nullptr) {
      auto endLabel = GenerateLabel();
      auto gotoFalse = std::make_shared<BoundConditionalGotoStatement>(
          endLabel, node->condition, false);
      auto endLabelStatement = std::make_shared<BoundLabelStatement>(endLabel);
      std::vector<std::shared_ptr<BoundStatement>> statements = {
          gotoFalse, node->thenstatement, endLabelStatement};
      auto result = std::make_shared<BoundBlockStatement>(statements);
      return RewriteStatement(result);
    } else {
      auto elseLabel = GenerateLabel();
      auto endLabel = GenerateLabel();

      auto gotoFalse = std::make_shared<BoundConditionalGotoStatement>(
          elseLabel, node->condition, false);
      auto gotoEndStatement = std::make_shared<BoundGotoStatement>(endLabel);
      auto elseLabelStatement =
          std::make_shared<BoundLabelStatement>(elseLabel);
      auto endLabelStatement = std::make_shared<BoundLabelStatement>(endLabel);
      auto result = std::make_shared<BoundBlockStatement>(
          std::vector<std::shared_ptr<BoundStatement>>(
              {gotoFalse, node->thenstatement, gotoEndStatement,
               elseLabelStatement, node->elsestatement, endLabelStatement}));
      return RewriteStatement(result);
    }
  }
  std::shared_ptr<BoundStatement> RewriteWhileStatement(
      std::shared_ptr<BoundWhileStatement> node) override {
    auto continueLabel = GenerateLabel();
    auto checkLabel = GenerateLabel();
    auto endLabel = GenerateLabel();
    auto gotoCheck = std::make_shared<BoundGotoStatement>(checkLabel);
    auto continuelabelstatement =
        std::make_shared<BoundLabelStatement>(continueLabel);
    auto checkLabelStatement =
        std::make_shared<BoundLabelStatement>(checkLabel);
    auto gotoTrue = std::make_shared<BoundConditionalGotoStatement>(
        continueLabel, node->condition);
    auto endLabelstatement = std::make_shared<BoundLabelStatement>(endLabel);
    auto result = std::make_shared<BoundBlockStatement>(
        std::vector<std::shared_ptr<BoundStatement>>(
            {gotoCheck, continuelabelstatement, node->statement,
             checkLabelStatement, gotoTrue, endLabelstatement}));
    return RewriteStatement(result);
  }
  std::shared_ptr<BoundStatement> RewriteForStatement(
      std::shared_ptr<BoundForStatement> node) override {
    auto variableDeclaration = std::make_shared<BoundVariableDeclaration>(
        node->variable, node->iterbegin);
    auto variableExpression =
        std::make_shared<BoundVariableExpression>(node->variable);
    VariableSymbol beginsymbol("iterbegin", BuildinType::Int, true);
    auto beginDeclaration = std::make_shared<BoundVariableDeclaration>(
        beginsymbol, node->iterbegin);
    auto condition = std::make_shared<BoundBinaryExpression>(
        variableExpression,
        Operators::BindBinaryOperator(SyntaxKind::LessOrEqualToken,
                                      BuildinType::Int, BuildinType::Int),
        std::make_shared<BoundVariableDeclaration>(beginsymbol));
    auto increment = std::make_shared<BoundExpressionStatement>(
        std::make_shared<BoundAssignmentExpression>(
            node->variable, std::make_shared<BoundBinaryExpression>(
                variableExpression,     Operators::BindBinaryOperator(SyntaxKind::PlusToken,BuildinType::Int,BuildinType::Int),
                std::make_shared<BoundLiteralExpression>(node->iterstep)
                )
            )
        );
    return nullptr;
  }
};
}  // namespace Compiler
