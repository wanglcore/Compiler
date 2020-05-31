#include "Binder.h"
namespace Compiler {
auto Binder::BindExpression(std::shared_ptr<ExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  switch (syntax->Kind) {
    case SyntaxKind::LiteralExpression:
      return BindLiteralExpression(
          std::dynamic_pointer_cast<LiteralExpressionSyntax>(syntax));
    case SyntaxKind::BinaryExpression:
      return BindBinaryExpression(
          std::dynamic_pointer_cast<BinaryExpressionSyntax>(syntax));
    case SyntaxKind::UnaryExpression:
      return BindUnaryExpression(
          std::dynamic_pointer_cast<UnaryExpressionSyntax>(syntax));
    default:
      return nullptr;
  }
}
auto Binder::BindLiteralExpression(
    std::shared_ptr<LiteralExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  return std::make_shared<BoundLiteralExpression>(syntax->value, syntax->type);
}

auto Binder::BindBinaryExpression(
    std::shared_ptr<BinaryExpressionSyntax> syntax)
    -> std::shared_ptr<BoundExpression> {
  auto left = BindExpression(syntax->left);
  auto right = BindExpression(syntax->right);
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
  return std::make_shared<BoundUnaryExpression>(boundOperator,
                                                boundOperand);
}
//
//inline BoundUnaryOperatorKind Binder::BindUnaryOperatorKind(SyntaxKind kind,
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
//inline BoundBinaryOperatorKind Binder::BindBinaryOperatorKind(SyntaxKind kind,
//                                                              Type lefttype,
//                                                              Type righttype) {
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