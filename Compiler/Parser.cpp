#include "LiteralExpressionSyntax.h"
#include "SyntaxTree.h"
Compiler::Parser::Parser(std::string _text) {
  auto lexer = std::make_unique<Lexer>(_text);
  std::vector<std::shared_ptr<SyntaxToken>> _tokens;
  for (auto token = lexer->NextToken();
       !Equals(token->Kind, SyntaxKind::EndOfFileToken);
       token = lexer->NextToken()) {
    if (!Equals(token->Kind, SyntaxKind::SpaceToken) &&
        !Equals(token->Kind, SyntaxKind::BadToken)) {
      _tokens.emplace_back(token);
    }
  }
  tokens = std::move(_tokens);
  tokens_length = tokens.size();
}
auto Compiler::Parser::Peek(int offset) -> std::shared_ptr<SyntaxToken> {
  int _index = position + offset;
  return _index >= tokens_length ? tokens.back() : tokens[_index];
}
auto Compiler::Parser::Parse() -> std::shared_ptr<SyntaxTree> {
  auto expression = ParseExpression(0);
  auto endOfFileToken = Match(SyntaxKind::EndOfFileToken);
  return std::make_shared<SyntaxTree>(expression, endOfFileToken);
}

// auto Compiler::Parser::ParseTerm() -> std::shared_ptr<ExpressionSyntax> {
//  auto left = ParseFactor();
//  while (Equals(Current()->Kind, SyntaxKind::PlusToken) ||
//         Equals(Current()->Kind, SyntaxKind::MinusToken)) {
//    auto op = NextToken();
//    auto right = ParseFactor();
//    left = std::make_shared<BinaryExpressionSyntax>(
//        std::move(left), std::move(op), std::move(right));
//  }
//  return left;
//}
//
// auto Compiler::Parser::ParseFactor() -> std::shared_ptr<ExpressionSyntax> {
//  auto left = ParsePrimaryExpression();
//  while (Equals(Current()->Kind, SyntaxKind::StarToken) ||
//         Equals(Current()->Kind, SyntaxKind::SlashToken)) {
//    auto op = NextToken();
//    auto right = ParsePrimaryExpression();
//    left = std::make_shared<BinaryExpressionSyntax>(
//        std::move(left), std::move(op), std::move(right));
//  }
//  return left;
//}
//
// auto Compiler::Parser::ParseExpression() -> std::shared_ptr<ExpressionSyntax>
// {
//  return ParseTerm();
//}

auto Compiler::Parser::ParsePrimaryExpression()
    -> std::shared_ptr<ExpressionSyntax> {
  if (Equals(Current()->Kind, SyntaxKind::OpenParenthesisToken)) {
    auto left = NextToken();
    auto expression = ParseExpression(0);
    auto right = Match(SyntaxKind::CloseParenthesisToken);
    return std::make_shared<ParenthesizedExpressionSyntax>(
        std::move(left), std::move(expression), std::move(right));
  } else if (Equals(Current()->Kind, SyntaxKind::TrueToken) ||
             Equals(Current()->Kind, SyntaxKind::FalseToken)) {
    auto keyword = NextToken();
    auto _value = keyword->Kind == SyntaxKind::TrueToken;
    return std::make_shared<LiteralExpressionSyntax>(keyword, _value,
                                                     Type::BoolType);
  }
  auto numberToken = Match(SyntaxKind::NumberToken);
  return std::make_shared<LiteralExpressionSyntax>(std::move(numberToken));
}

auto Compiler::Parser::ParseExpression(int parentprecedence)
    -> std::shared_ptr<ExpressionSyntax> {
  std::shared_ptr<ExpressionSyntax> left;
  auto unaryprecedence =
      SyntaxFacts::GetUnaryOperatorPrecedence(Current()->Kind);
  /*
  if (unaryprecedence != 0 && unaryprecedence > parentprecedence) {
    auto op = NextToken();
    auto operand = ParseExpression(0);
    left = std::make_shared<UnaryExpressionSyntax>(op, operand);
  } else {
    left = ParsePrimaryExpression();
  }
  */
  if (unaryprecedence != 0 && unaryprecedence >= parentprecedence) {
    auto op = NextToken();
    auto operand = ParseExpression(unaryprecedence);
    left = std::make_shared<UnaryExpressionSyntax>(op, operand);
  } else {
    left = ParsePrimaryExpression();
  }
  while (true) {
    auto precedence = SyntaxFacts::GetBinaryOperatorPrecedence(Current()->Kind);
    if (precedence == 0 || precedence <= parentprecedence) break;
    auto op = NextToken();
    auto right = ParseExpression(precedence);
    left = std::make_shared<BinaryExpressionSyntax>(left, op, right);
  }
  return left;
}
