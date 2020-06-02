#include "LiteralExpressionSyntax.h"
#include "SyntaxTree.h"
// Compiler::Parser::Parser(std::string _text) {
//  auto lexer = std::make_unique<Lexer>(_text);
//  std::vector<std::shared_ptr<SyntaxToken>> _tokens;
//  for (auto token = lexer->NextToken();
//       !Equals(token->Kind, SyntaxKind::EndOfFileToken);
//       token = lexer->NextToken()) {
//    if (!Equals(token->Kind, SyntaxKind::SpaceToken) &&
//        !Equals(token->Kind, SyntaxKind::BadToken)) {
//      _tokens.emplace_back(token);
//    }
//  }
//  tokens = std::move(_tokens);
//  tokens_length = tokens.size();
//}
Compiler::Parser::Parser(std::shared_ptr<SourceText> _sourcetext) {
  Lexer lexer(_sourcetext);
  // auto lexer = std::make_unique<Lexer>(_sourcetext);
  std::vector<std::shared_ptr<SyntaxToken>> _tokens;
  for (auto token = lexer.NextToken();
       !Equals(token->Kind, SyntaxKind::EndOfFileToken);
       token = lexer.NextToken()) {
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
auto Compiler::Parser::ParseCompilationUnit()
    -> std::shared_ptr<CompilationUnitSyntax> {
  auto _statement = ParseStatement();
  auto endOfFileToken = MatchToken(SyntaxKind::EndOfFileToken);
  return std::make_shared<CompilationUnitSyntax>(_statement, endOfFileToken);
}

auto Compiler::Parser::ParseStatement() -> std::shared_ptr<StatementSyntax> {
  if (Current()->Kind == SyntaxKind::OpenBraceToken) {
    return ParseBlockStatement();
  }
  return ParseExpressionStatement();
}

auto Compiler::Parser::ParseBlockStatement()
    -> std::shared_ptr<StatementSyntax> {
  std::vector<std::shared_ptr<StatementSyntax>> _statements;
  auto openBraceToken = MatchToken(SyntaxKind::OpenBraceToken);
  while (Current()->Kind != SyntaxKind::EndOfFileToken &&
         Current()->Kind != SyntaxKind::CloseBraceToken) {
    auto _statement = ParseStatement();
    _statements.push_back(_statement);
  }
  auto closeBraceToken = MatchToken(SyntaxKind::CloseBraceToken);
  return std::make_shared<BlockStatementSyntax>(openBraceToken, _statements,
                                                closeBraceToken);
}

auto Compiler::Parser::ParseExpressionStatement()
    -> std::shared_ptr<StatementSyntax> {
  auto expression = ParseExpression();
  return std::make_shared<ExpressionStatementSyntax>(expression);
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
    auto expression = ParseBinaryExpression(0);
    auto right = MatchToken(SyntaxKind::CloseParenthesisToken);
    return std::make_shared<ParenthesizedExpressionSyntax>(
        std::move(left), std::move(expression), std::move(right));
  } else if (Equals(Current()->Kind, SyntaxKind::TrueToken) ||
             Equals(Current()->Kind, SyntaxKind::FalseToken)) {
    // auto isTrue = Current()->Kind == SyntaxKind::TrueToken;
    auto keyword = NextToken();
    auto _value = keyword->Kind == SyntaxKind::TrueToken;
    return std::make_shared<LiteralExpressionSyntax>(keyword, _value,
                                                     Type::BoolType);
  } else if (Equals(Current()->Kind, SyntaxKind::IdentifierToken)) {
    auto identifier = NextToken();
    return std::make_shared<NameExpressionSyntax>(identifier);
  }
  auto numberToken = MatchToken(SyntaxKind::NumberToken);
  return std::make_shared<LiteralExpressionSyntax>(std::move(numberToken));
}

auto Compiler::Parser::ParseBinaryExpression(int parentprecedence)
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
    auto operand = ParseBinaryExpression(unaryprecedence);
    left = std::make_shared<UnaryExpressionSyntax>(op, operand);
  } else {
    left = ParsePrimaryExpression();
  }
  while (true) {
    auto precedence = SyntaxFacts::GetBinaryOperatorPrecedence(Current()->Kind);
    if (precedence == 0 || precedence <= parentprecedence) break;
    auto op = NextToken();
    auto right = ParseBinaryExpression(precedence);
    left = std::make_shared<BinaryExpressionSyntax>(left, op, right);
  }
  return left;
}

auto Compiler::Parser::ParseExpression() -> std::shared_ptr<ExpressionSyntax> {
  return ParseAssignmentExpression();
}

auto Compiler::Parser::ParseAssignmentExpression()
    -> std::shared_ptr<ExpressionSyntax> {
  if (Peek(0)->Kind == SyntaxKind::IdentifierToken &&
      Peek(1)->Kind == SyntaxKind::EqualsToken) {
    auto identifierToken = NextToken();
    auto equalToken = NextToken();
    auto expression = ParseAssignmentExpression();
    return std::make_shared<AssignmentExpressionSyntax>(identifierToken,
                                                        equalToken, expression);
  }
  return ParseBinaryExpression(0);
}
