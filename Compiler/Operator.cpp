#include "Operator.h"

namespace Compiler {
std::vector<std::shared_ptr<BoundUnaryOperator>> Operators::unaryOperators = {
    std::make_shared<BoundUnaryOperator>(
        SyntaxKind::BangToken, BoundUnaryOperatorKind::LogicalNegation,
        BuildinType::Bool),
    std::make_shared<BoundUnaryOperator>(SyntaxKind::PlusToken,
                                         BoundUnaryOperatorKind::Identity,
                                         BuildinType::Int),
    std::make_shared<BoundUnaryOperator>(SyntaxKind::MinusToken,
                                         BoundUnaryOperatorKind::Negation,
                                         BuildinType::Int),
    std::make_shared<BoundUnaryOperator>(SyntaxKind::TiledeToken,
                                         BoundUnaryOperatorKind::OnesComplememt,
                                         BuildinType::Int),
};
std::vector<std::shared_ptr<BoundBinaryOperator>> Operators::binaryOperators = {
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusToken, BoundBinaryOperatorKind::Addition,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusToken, BoundBinaryOperatorKind::Addition,
        BuildinType::String, BuildinType::String, BuildinType::String),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PlusEqualsToken, BoundBinaryOperatorKind::AdditionEqual,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::MinusEqualsToken, BoundBinaryOperatorKind::SubtractionEqual,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::MinusToken, BoundBinaryOperatorKind::Subtraction,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::StarToken, BoundBinaryOperatorKind::Multiplication,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::SlashToken, BoundBinaryOperatorKind::Subtraction,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(SyntaxKind::AmpersandAmpersandToken,
                                          BoundBinaryOperatorKind::LogicalAnd,
                                          BuildinType::Bool, BuildinType::Bool,
                                          BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipePipeToken, BoundBinaryOperatorKind::LogicalOr,
        BuildinType::Bool, BuildinType::Bool, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::AmpersandToken, BoundBinaryOperatorKind::BitWiseAnd,
        BuildinType::Bool, BuildinType::Bool, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipeToken, BoundBinaryOperatorKind::BitWiseOr,
        BuildinType::Bool, BuildinType::Bool, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::AmpersandToken, BoundBinaryOperatorKind::BitWiseAnd,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::PipeToken, BoundBinaryOperatorKind::BitWiseOr,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::HatToken, BoundBinaryOperatorKind::BitWiseXor,
        BuildinType::Int, BuildinType::Int, BuildinType::Int),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::HatToken, BoundBinaryOperatorKind::BitWiseXor,
        BuildinType::Bool, BuildinType::Bool, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::EqualsEqualsToken, BoundBinaryOperatorKind::Equsls,
        BuildinType::Int, BuildinType::Int, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::EqualsEqualsToken, BoundBinaryOperatorKind::Equsls,
        BuildinType::Bool, BuildinType::Bool, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::NotEqualsToken, BoundBinaryOperatorKind::NotEquals,
        BuildinType::Int, BuildinType::Int, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::NotEqualsToken, BoundBinaryOperatorKind::NotEquals,
        BuildinType::Bool, BuildinType::Bool, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::LessOrEqualToken, BoundBinaryOperatorKind::LessOrEqual,
        BuildinType::Int, BuildinType::Int, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::LessToken, BoundBinaryOperatorKind::Less, BuildinType::Int,
        BuildinType::Int, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::GreaterOrEqualToken,
        BoundBinaryOperatorKind::GreaterOrEqual, BuildinType::Int,
        BuildinType::Int, BuildinType::Bool),
    std::make_shared<BoundBinaryOperator>(
        SyntaxKind::GreaterToken, BoundBinaryOperatorKind::Greater,
        BuildinType::Int, BuildinType::Int, BuildinType::Bool),

};

std::shared_ptr<BoundUnaryOperator>
Operators::BindUnaryOperator(SyntaxKind kind, BuildinType operandType) {
  for (auto op : unaryOperators) {
    if (op->syntaxkind == kind && op->operandType == operandType) {
      return op;
    }
  }
  return nullptr;
}
std::shared_ptr<BoundBinaryOperator>
Operators::BindBinaryOperator(SyntaxKind kind, BuildinType lefttype,
                              BuildinType righttype) {
  for (auto op : binaryOperators) {
    if (op->syntaxkind == kind && op->lefttype == lefttype &&
        op->righttype == righttype) {
      return op;
    }
  }
  return nullptr;
}
} // namespace Compiler
