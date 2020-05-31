#include "Operator.h"

namespace Compiler {
std::vector<std::shared_ptr<BoundUnaryOperator>> Operators::unaryOperators = {
    std::make_shared<BoundUnaryOperator>(
        SyntaxKind::BangToken, BoundUnaryOperatorKind::LogicalNegation,
        Type::BoolType),
    std::make_shared<BoundUnaryOperator>(
        SyntaxKind::PlusToken, BoundUnaryOperatorKind::Identity, Type::IntType),
    std::make_shared<BoundUnaryOperator>(SyntaxKind::MinusToken,
                                         BoundUnaryOperatorKind::Negation,
                                         Type::IntType),
};
std::vector<std::shared_ptr<BoundBinaryOperator>> Operators::binaryOperators = {
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusToken, BoundBinaryOperatorKind::Addition, Type::IntType,
        Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::MinusToken, BoundBinaryOperatorKind::Subtraction,
        Type::IntType, Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::StarToken, BoundBinaryOperatorKind::Multiplication,
        Type::IntType, Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::SlashToken, BoundBinaryOperatorKind::Subtraction,
        Type::IntType, Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(SyntaxKind::AmpersandAmpersandToken,
                                          BoundBinaryOperatorKind::LogicalAnd,
                                          Type::BoolType, Type::BoolType,
                                          Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipePipeToken, BoundBinaryOperatorKind::LogicalOr,
        Type::BoolType, Type::BoolType, Type::BoolType),
};

std::shared_ptr<BoundUnaryOperator> Operators::BindUnaryOperator(
    SyntaxKind kind, Type operandType) {
  for (auto op : unaryOperators) {
    if (op->syntaxkind == kind && op->operandType == operandType) {
      return op;
    }
  }
  return nullptr;
}
std::shared_ptr<BoundBinaryOperator> Operators::BindBinaryOperator(
    SyntaxKind kind, Type lefttype, Type righttype) {
  for (auto op : binaryOperators) {
    if (op->syntaxkind == kind && op->lefttype == lefttype &&
        op->righttype == righttype) {
      return op;
    }
  }
  return nullptr;
}
}  // namespace Compiler