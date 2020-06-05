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
  } else if (Current()->Kind == SyntaxKind::VarToken ||
             Current()->Kind == SyntaxKind::LetToken) {
    return ParseVariableDeclaration();
  } else if (Current()->Kind == SyntaxKind::IfToken) {
    return ParseIfStatement();
  } else if (Current()->Kind == SyntaxKind::WhileToken) {
    return ParseWhileStatement();
  } else if (Current()->Kind == SyntaxKind::ForToken) {
    return ParseForStatement();
  }
  return ParseExpressionStatement();
}

auto Compiler::Parser::ParseBlockStatement()
    -> std::shared_ptr<StatementSyntax> {
  std::vector<std::shared_ptr<StatementSyntax>> _statements;
  auto openBraceToken = MatchToken(SyntaxKind::OpenBraceToken);
  while (Current()->Kind != SyntaxKind::EndOfFileToken &&
         Current()->Kind != SyntaxKind::CloseBraceToken) {
    auto startToken = Current();
    auto _statement = ParseStatement();
    _statements.push_back(_statement);
    if (Current() == startToken) {
      NextToken();
    }
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
  auto temp = Current()->Kind;
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
  } else if (Equals(Current()->Kind, SyntaxKind::StringToken)) {
    auto stringToken = NextToken();
    return std::make_shared<LiteralExpressionSyntax>(stringToken);
  } else if (Equals(Current()->Kind, SyntaxKind::NumberToken)) {
    auto numberToken = MatchToken(SyntaxKind::NumberToken);
    return std::make_shared<LiteralExpressionSyntax>(std::move(numberToken));
  } else {
    if (Peek(0)->Kind == SyntaxKind::IdentifierToken &&
        Peek(1)->Kind == SyntaxKind::OpenParenthesisToken) {
      auto identifier = MatchToken(SyntaxKind::IdentifierToken);
      auto openbrace = MatchToken(SyntaxKind::OpenParenthesisToken);
      auto arguments = ParseArguments();
      auto closebrace = MatchToken(SyntaxKind::CloseParenthesisToken);
      return std::make_shared<CallExpressionSyntax>(identifier, openbrace,
                                                    arguments, closebrace);
    }
    auto identifier = NextToken();
    return std::make_shared<NameExpressionSyntax>(identifier);
  }
}
auto Compiler::Parser::ParseArguments()
    -> std::vector<std::shared_ptr<ExpressionSyntax>> {
  std::vector<std::shared_ptr<ExpressionSyntax>> arguments;
  auto curr = Current();
  while (curr->Kind != SyntaxKind::CloseParenthesisToken &&
         curr->Kind != SyntaxKind::EndOfFileToken) {
    auto argument = ParseExpression();
    arguments.emplace_back(argument);
    if (curr->Kind != SyntaxKind::CloseParenthesisToken) {
      auto comma = MatchToken(SyntaxKind::CommaToken);
    }
  }
  return std::move(arguments);
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
    if (precedence == 0 || precedence <= parentprecedence)
      break;
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
  auto tag = Peek(1)->Kind == SyntaxKind::EqualsToken;
  if (Peek(0)->Kind == SyntaxKind::IdentifierToken && tag) {
    auto identifierToken = NextToken();
    auto equalToken = NextToken();
    auto expression = ParseAssignmentExpression();
    return std::make_shared<AssignmentExpressionSyntax>(identifierToken,
                                                        equalToken, expression);
  }
  return ParseBinaryExpression(0);
}

auto Compiler::Parser::ParseVariableDeclaration()
    -> std::shared_ptr<StatementSyntax> {
  auto keyword = NextToken();
  auto mutkeyword =
      (Current()->Kind == SyntaxKind::MutToken) ? NextToken() : nullptr;
  auto identifier = NextToken();
  auto equalsToken = NextToken();
  auto initializer = ParseExpression();
  return std::make_shared<VariableDeclarationSyntax>(
      keyword, mutkeyword, identifier, equalsToken, initializer);
}

auto Compiler::Parser::ParseIfStatement() -> std::shared_ptr<StatementSyntax> {
  auto ifkeyword = NextToken();
  auto condition = ParseExpression();
  auto statement = ParseStatement();
  auto elseclause = ParseElseStatement();
  return std::make_shared<IfStatementSyntax>(ifkeyword, condition, statement,
                                             elseclause);
}

auto Compiler::Parser::ParseWhileStatement()
    -> std::shared_ptr<StatementSyntax> {
  auto whilekeyword = NextToken();
  auto condition = ParseExpression();
  auto statement = ParseStatement();
  return std::make_shared<WhileStatementSyntax>(whilekeyword, condition,
                                                statement);
}

auto Compiler::Parser::ParseForStatement() -> std::shared_ptr<StatementSyntax> {
  auto forkeyword = NextToken();
  auto identifier = NextToken();
  auto inkeyword = NextToken();
  auto iterbegin = ParseExpression();
  auto colontoken1 = NextToken();
  auto iterend = ParseExpression();
  std::shared_ptr<ExpressionSyntax> iterstep = nullptr;
  if (Current()->Kind == SyntaxKind::ColonToken) {
    auto colontoken2 = NextToken();
    iterstep = ParseExpression();
  }
  auto statement = ParseStatement();
  return std::make_shared<ForStatementSyntax>(forkeyword, identifier, inkeyword,
                                              iterbegin, iterend, iterstep,
                                              statement);
}

auto Compiler::Parser::ParseElseStatement()
    -> std::shared_ptr<ElseClauseSyntax> {
  if (Current()->Kind == SyntaxKind::ElseToken) {
    auto elsekeyword = NextToken();
    auto elsestatement = ParseStatement();
    return std::make_shared<ElseClauseSyntax>(elsekeyword, elsestatement);
  }
  return nullptr;
}
