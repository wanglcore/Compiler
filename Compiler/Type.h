#pragma once
#include <iostream>
#include <variant>
namespace Compiler {
using Object = std::variant<int, bool, std::string, nullptr_t>;
enum class SyntaxKind {
  DefaultToken,
  NumberToken,
  TypeClause,
  PlusToken,
  PlusEqualsToken,
  MinusEqualsToken,
  PlusPlusToken,
  MinusMinusToken,
  StarEqualsToken,
  SlashEqualsToken,
  MinusToken,
  StarToken,
  SlashToken,
  OpenParenthesisToken,
  CloseParenthesisToken,
  OpenBraceToken,
  CloseBraceToken,
  BadToken,
  EndOfFileToken,
  SpaceToken,
  IdentifierToken,
  LessToken,
  LessOrEqualToken,
  GreaterToken,
  GreaterOrEqualToken,
  ColonToken,
  StringToken,
  CommaToken,
  LeftArrowToken,
  DefToken,

  TrueToken,
  FalseToken,
  LetToken,
  VarToken,
  MutToken,
  ForToken,
  ElseToken,
  IfToken,
  WhileToken,
  DoToken,
  InToken,

  EqualsToken,
  BangToken,
  AmpersandAmpersandToken,
  PipePipeToken,
  EqualsEqualsToken,
  NotEqualsToken,
  PipeToken,
  AmpersandToken,
  TiledeToken,
  HatToken,

  LiteralExpression,
  BinaryExpression,
  UnaryExpression,
  ParenthesizedExpression,
  NameExpression,
  AssignmentExpression,
  CompilationUnit,
  CallExpression,

  BlockStatement,
  ExpressionStatement,
  IfStatement,
  ElseStatement,
  WhileStatement,
  DoWhileStatemnt,
  ForStatement,
  ElseClause,
  VariableDeclaration,

  GlobalStatement,
  FunctionDeclarition,
  Parameters
};
enum class SymbolKind { Variable, Type, Function, Parameter, DefaultType };
enum class BoundNodeKind {
  DefaultBoundNodeKind,
  UnaryExpression,
  LiteralExpression,
  BinaryExpression,
  VariableExpression,
  AssignmentExpression,
  BlockStatement,
  ExpressionStatement,
  VariableDeclaration,
  IfStatement,
  WhileStatement,
  DoWhileStatement,
  ForStatement,
  CallExpression,
  ConversionExpression,
  LabelStatement,
  GotoStatement,
  ConditionalGotoStatement
};
enum class BuildinType { Int, Bool, String, Void, Default };
enum class BoundUnaryOperatorKind {
  Identity,
  Negation,
  DefaultType,
  LogicalNegation,
  OnesComplememt
};
enum class BoundBinaryOperatorKind {
  Addition,
  AdditionEqual,
  Subtraction,
  SubtractionEqual,
  Multiplication,
  Division,
  LogicalAnd,
  LogicalOr,
  Equsls,
  NotEquals,
  DefaultType,
  Less,
  Greater,
  LessOrEqual,
  GreaterOrEqual,
  BitWiseAnd,
  BitWiseOr,
  BitWiseXor
};
enum class NodeKind {
  SyntaxNodeNode,
  SyntaxTokenNode,
  DefaultTokenNode,
  ExpressionSyntaxNode,
  BinaryExpressionSyntaxNode,
  UnaryExpressionSyntaxNode,
  LiteralExpressionSyntaxNode,
  ParenthesizedExpressionSyntaxNode,
  NameExpressionNode,
  AssignmentExpressionNode,
  CompilationUnitNode,
  StatementSyntaxNode,
  BlockStatementNode,
  ExpressionStatementNode
};

static std::ostream &operator<<(std::ostream &os, const SyntaxKind &kind) {
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
  case SyntaxKind::IdentifierToken:
    os << "IdentifierToken";
    break;
  case SyntaxKind::EqualsEqualsToken:
    os << "EqualsEqualsToken";
    break;
  case SyntaxKind::EqualsToken:
    os << "EqualsToken";
    break;
  case SyntaxKind::TrueToken:
    os << "TrueToken";
    break;
  case SyntaxKind::FalseToken:
    os << "FalseToken";
    break;
  case SyntaxKind::AmpersandAmpersandToken:
    os << "AmpersandAmpersandToken";
    break;
  case SyntaxKind::PipePipeToken:
    os << "PipePipeToken";
    break;
  case SyntaxKind::NotEqualsToken:
    os << "NotEqualsToken";
    break;
  case SyntaxKind::AssignmentExpression:
    os << "AssignmentExpression";
    break;
  case SyntaxKind::BangToken:
    os << "BangToken";
    break;
  case SyntaxKind::NameExpression:
    os << "NameExpression";
    break;
  }
  return os;
}
} // namespace Compiler
