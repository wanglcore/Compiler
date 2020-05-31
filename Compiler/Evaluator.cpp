#include "Evaluator.h"
namespace Compiler {
Object Compiler::Evaluator::Evaluate() { return EvaluateExpression(root); }

Object Compiler::Evaluator::EvaluateExpression(
    std::shared_ptr<BoundExpression> _root) {
  if (_root->EqualsKind(BoundNodeKind::LiteralExpression)) {
    auto literalExpressionSyntax =
        std::dynamic_pointer_cast<BoundLiteralExpression>(_root);
    return literalExpressionSyntax->value;
  }
  if (_root->EqualsKind(BoundNodeKind::UnaryExpression)) {
    auto unaryExpressionSyntax =
        std::dynamic_pointer_cast<BoundUnaryExpression>(_root);
    auto val = EvaluateExpression(unaryExpressionSyntax->operand);
    switch (unaryExpressionSyntax->op->kind) {
      case BoundUnaryOperatorKind::Identity:
        return -std::get<0>(val);
      case BoundUnaryOperatorKind::Negation:
        return std::get<0>(val);
      case BoundUnaryOperatorKind::LogicalNegation:
        return !std::get<1>(val);
    }
  }
  if (_root->EqualsKind(BoundNodeKind::BinaryExpression)) {
    auto binaryExpressionSyntax =
        std::dynamic_pointer_cast<BoundBinaryExpression>(_root);
    auto left = EvaluateExpression(binaryExpressionSyntax->left);
    auto right = EvaluateExpression(binaryExpressionSyntax->right);
    switch (binaryExpressionSyntax->op->kind) {
      case BoundBinaryOperatorKind::Addition:
        return std::get<0>(left) + std::get<0>(right);
      case BoundBinaryOperatorKind::Subtraction:
        return std::get<0>(left) - std::get<0>(right);
      case BoundBinaryOperatorKind::Multiplication:
        return std::get<0>(left) * std::get<0>(right);
      case BoundBinaryOperatorKind::Division:
        return std::get<0>(left) / std::get<0>(right);
      case BoundBinaryOperatorKind::LogicalAnd:
        return std::get<1>(left) && std::get<1>(right);
      case BoundBinaryOperatorKind::LogicalOr:
        return std::get<1>(left) || std::get<1>(right);
      default:
        break;
    }
  }
  /* if (Equals(_root->Kind, BoundNodeKind::UnaryExpression)) {
     auto parenthesizedExpression =
         std::dynamic_pointer_cast<ParenthesizedExpressionSyntax>(_root);
     return EvaluateExpression(parenthesizedExpression->expression);
   }*/
  return 0;
}
}  // namespace Compiler
