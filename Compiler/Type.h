#pragma once
#include <iostream>
#include <variant>
namespace Compiler {
using Object = std::variant<int, bool, nullptr_t>;
enum class SyntaxKind {
  DefaultToken,
  NumberToken,
  PlusToken,
  MinusToken,
  StarToken,
  SlashToken,
  OpenParenthesisToken,
  CloseParenthesisToken,
  BadToken,
  EndOfFileToken,

  BangToken,
  AmpersandAmpersandToken,
  PipePipeToken,

  SpaceToken,
  LiteralExpression,
  BinaryExpression,
  UnaryExpression,
  ParenthesizedExpression,
  IdentifierToken,
  TrueToken,
  FalseToken
};

enum class BoundNodeKind {
  DefaultBoundNodeKind,
  UnaryExpression,
  LiteralExpression,
  BinaryExpression
};
enum class Type { DefaultType, IntType ,BoolType};
enum class BoundUnaryOperatorKind { Identity, Negation, DefaultType,LogicalNegation };
enum class BoundBinaryOperatorKind {
  Addition,
  Subtraction,
  Multiplication,
  Division,
  LogicalAnd,
  LogicalOr,
  DefaultType
};
enum class NodeKind {
  SyntaxNodeNode,
  SyntaxTokenNode,
  DefaultTokenNode,
  ExpressionSyntaxNode,
  BinaryExpressionSyntaxNode,
  UnaryExpressionSyntaxNode,
  LiteralExpressionSyntaxNode,
  ParenthesizedExpressionSyntaxNode
};
static std::ostream& operator<<(std::ostream& os, const SyntaxKind& kind) {
  switch (kind) {
    case SyntaxKind::UnaryExpression:
      os << "UnaryExpression";
      break;
    case SyntaxKind::DefaultToken:
      os << "DefaultToken";
      break;
    case SyntaxKind::NumberToken:
      os << "NumberToken";
      break;
    case SyntaxKind::PlusToken:
      os << "PlusToken";
      break;
    case SyntaxKind::MinusToken:
      os << "MinusToken";
      break;
    case SyntaxKind::StarToken:
      os << "StarToken";
      break;
    case SyntaxKind::SlashToken:
      os << "SlashToken";
      break;
    case SyntaxKind::OpenParenthesisToken:
      os << "OpenParenthesisToken";
      break;
    case SyntaxKind::CloseParenthesisToken:
      os << "CloseParenthesisToken";
      break;
    case SyntaxKind::BadToken:
      os << "BadToken";
      break;
    case SyntaxKind::EndOfFileToken:
      os << "EndOfFileToken";
      break;
    case SyntaxKind::SpaceToken:
      os << "SpaceToken";
      break;
    case SyntaxKind::LiteralExpression:
      os << "NumberExpression";
      break;
    case SyntaxKind::BinaryExpression:
      os << "BinaryExpression";
      break;
    case SyntaxKind::ParenthesizedExpression:
      os << "ParenthesizedExpression";
      break;
  }
  return os;
}
}  // namespace Compiler
