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
    std::make_shared<BoundUnaryOperator>(SyntaxKind::TiledeToken,
                                         BoundUnaryOperatorKind::OnesComplememt,
                                         Type::IntType),
};
std::vector<std::shared_ptr<BoundBinaryOperator>> Operators::binaryOperators = {
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusToken, BoundBinaryOperatorKind::Addition, Type::IntType,
        Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusEqualsToken, BoundBinaryOperatorKind::AdditionEqual, Type::IntType,
        Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::MinusEqualsToken, BoundBinaryOperatorKind::SubtractionEqual, Type::IntType,
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
    std::make_shared<BoundBinaryOperator>(SyntaxKind::AmpersandToken,
                                          BoundBinaryOperatorKind::BitWiseAnd,
                                          Type::BoolType, Type::BoolType,
                                          Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipeToken, BoundBinaryOperatorKind::BitWiseOr,
        Type::BoolType, Type::BoolType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::AmpersandToken, BoundBinaryOperatorKind::BitWiseAnd,
        Type::IntType, Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipeToken, BoundBinaryOperatorKind::BitWiseOr,
        Type::IntType, Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::HatToken, BoundBinaryOperatorKind::BitWiseXor,
        Type::IntType, Type::IntType, Type::IntType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::HatToken, BoundBinaryOperatorKind::BitWiseXor,
        Type::BoolType, Type::BoolType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::EqualsEqualsToken, BoundBinaryOperatorKind::Equsls,
        Type::IntType, Type::IntType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::EqualsEqualsToken, BoundBinaryOperatorKind::Equsls,
        Type::BoolType, Type::BoolType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::NotEqualsToken, BoundBinaryOperatorKind::NotEquals,
        Type::IntType, Type::IntType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::NotEqualsToken, BoundBinaryOperatorKind::NotEquals,
        Type::BoolType, Type::BoolType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::LessOrEqualToken, BoundBinaryOperatorKind::LessOrEqual,
        Type::IntType, Type::IntType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::LessToken, BoundBinaryOperatorKind::Less, Type::IntType,
        Type::IntType, Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::GreaterOrEqualToken,
        BoundBinaryOperatorKind::GreaterOrEqual, Type::IntType, Type::IntType,
        Type::BoolType),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::GreaterToken, BoundBinaryOperatorKind::Greater,
        Type::IntType, Type::IntType, Type::BoolType),


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