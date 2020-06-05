#include "Operator.h"

namespace Compiler {
std::vector<std::shared_ptr<BoundUnaryOperator>> Operators::unaryOperators = {
    std::make_shared<BoundUnaryOperator>(
        SyntaxKind::BangToken, BoundUnaryOperatorKind::LogicalNegation,
        BaseType::Bool),
    std::make_shared<BoundUnaryOperator>(
        SyntaxKind::PlusToken, BoundUnaryOperatorKind::Identity, BaseType::Int),
    std::make_shared<BoundUnaryOperator>(SyntaxKind::MinusToken,
                                         BoundUnaryOperatorKind::Negation,
                                         BaseType::Int),
    std::make_shared<BoundUnaryOperator>(SyntaxKind::TiledeToken,
                                         BoundUnaryOperatorKind::OnesComplememt,
                                         BaseType::Int),
};
std::vector<std::shared_ptr<BoundBinaryOperator>> Operators::binaryOperators = {
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusToken, BoundBinaryOperatorKind::Addition, BaseType::Int,
        BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusToken, BoundBinaryOperatorKind::Addition,
        BaseType::String, BaseType::String, BaseType::String),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusEqualsToken, BoundBinaryOperatorKind::AdditionEqual,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::MinusEqualsToken, BoundBinaryOperatorKind::SubtractionEqual,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::MinusToken, BoundBinaryOperatorKind::Subtraction,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::StarToken, BoundBinaryOperatorKind::Multiplication,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::SlashToken, BoundBinaryOperatorKind::Subtraction,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(SyntaxKind::AmpersandAmpersandToken,
                                          BoundBinaryOperatorKind::LogicalAnd,
                                          BaseType::Bool, BaseType::Bool,
                                          BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipePipeToken, BoundBinaryOperatorKind::LogicalOr,
        BaseType::Bool, BaseType::Bool, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::AmpersandToken, BoundBinaryOperatorKind::BitWiseAnd,
        BaseType::Bool, BaseType::Bool, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipeToken, BoundBinaryOperatorKind::BitWiseOr,
        BaseType::Bool, BaseType::Bool, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::AmpersandToken, BoundBinaryOperatorKind::BitWiseAnd,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipeToken, BoundBinaryOperatorKind::BitWiseOr,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::HatToken, BoundBinaryOperatorKind::BitWiseXor,
        BaseType::Int, BaseType::Int, BaseType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::HatToken, BoundBinaryOperatorKind::BitWiseXor,
        BaseType::Bool, BaseType::Bool, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::EqualsEqualsToken, BoundBinaryOperatorKind::Equsls,
        BaseType::Int, BaseType::Int, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::EqualsEqualsToken, BoundBinaryOperatorKind::Equsls,
        BaseType::Bool, BaseType::Bool, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::NotEqualsToken, BoundBinaryOperatorKind::NotEquals,
        BaseType::Int, BaseType::Int, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::NotEqualsToken, BoundBinaryOperatorKind::NotEquals,
        BaseType::Bool, BaseType::Bool, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::LessOrEqualToken, BoundBinaryOperatorKind::LessOrEqual,
        BaseType::Int, BaseType::Int, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::LessToken, BoundBinaryOperatorKind::Less, BaseType::Int,
        BaseType::Int, BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::GreaterOrEqualToken,
        BoundBinaryOperatorKind::GreaterOrEqual, BaseType::Int, BaseType::Int,
        BaseType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::GreaterToken, BoundBinaryOperatorKind::Greater,
        BaseType::Int, BaseType::Int, BaseType::Bool),

};

std::shared_ptr<BoundUnaryOperator>
Operators::BindUnaryOperator(SyntaxKind kind, TypeSymbol operandType) {
  for (auto op : unaryOperators) {
    if (op->syntaxkind == kind && op->operandType == operandType) {
      return op;
    }
  }
  return nullptr;
}
std::shared_ptr<BoundBinaryOperator>
Operators::BindBinaryOperator(SyntaxKind kind, TypeSymbol lefttype, TypeSymbol righttype) {
  for (auto op : binaryOperators) {
    if (op->syntaxkind == kind && op->lefttype == lefttype &&
        op->righttype == righttype) {
      return op;
    }
  }
  return nullptr;
}
} // namespace Compiler
