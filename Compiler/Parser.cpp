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
  std::shared_ptr<SyntaxToken> token;
  for (token = lexer.NextToken();
       !Equals(token->Kind, SyntaxKind::EndOfFileToken);
       token = lexer.NextToken()) {
    if (!Equals(token->Kind, SyntaxKind::SpaceToken) &&
        !Equals(token->Kind, SyntaxKind::BadToken)) {
      _tokens.emplace_back(token);
    }
  }
  _tokens.emplace_back(token);
  tokens = std::move(_tokens);
  tokens_length = tokens.size();
}
auto Compiler::Parser::Peek(int offset) -> std::shared_ptr<SyntaxToken> {
  int _index = position + offset;
  return _index >= tokens_length ? tokens.back() : tokens[_index];
}
auto Compiler::Parser::ParseCompilationUnit()
    -> std::shared_ptr<CompilationUnitSyntax> {
  auto _members = ParseMembers();
  auto endOfFileToken = MatchToken(SyntaxKind::EndOfFileToken);
  return std::make_shared<CompilationUnitSyntax>(_members, endOfFileToken);
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
  } else if (Current()->Kind == SyntaxKind::DoToken) {
    return ParseDoWhileStatement();
  }
  return ParseExpressionStatement();
}

auto Compiler::Parser::ParseMember() -> std::shared_ptr<MemberSyntax> {
  if (Current()->Kind == SyntaxKind::DefToken) {
    return ParseFunctionDeclaration();
  }
  return ParseGlobalStatement();
}

auto Compiler::Parser::ParseFunctionDeclaration()
    -> std::shared_ptr<FunctionDeclaritionSyntax> {
  auto deftoken = MatchToken(SyntaxKind::DefToken);
  auto identifier = MatchToken(SyntaxKind::IdentifierToken);
  auto leftOpen = MatchToken(SyntaxKind::OpenParenthesisToken);
  auto parameters = ParseParameters();
  auto rightClose = MatchToken(SyntaxKind::CloseParenthesisToken);
  std::shared_ptr<SyntaxToken> type;
  if (Current()->Kind == SyntaxKind::ColonToken) {
    auto colonToken = NextToken();
    type = NextToken();
  }
  auto body = ParseBlockStatement();
  return std::make_shared<FunctionDeclaritionSyntax>(
      deftoken, identifier, leftOpen, parameters, rightClose, type, body);
}

auto Compiler::Parser::ParseParameters()
    -> std::vector<std::shared_ptr<ParameterSyntax>> {
  std::vector<std::shared_ptr<ParameterSyntax>> parameters;
  for (auto curr = Current(); curr->Kind != SyntaxKind::CloseParenthesisToken &&
                              curr->Kind != SyntaxKind::EndOfFileToken;
       curr = Current()) {
    auto parameter = ParseParameter();
    parameters.emplace_back(parameter);
    if (Current()->Kind != SyntaxKind::CloseParenthesisToken) {
      auto comma = MatchToken(SyntaxKind::CommaToken);
    }
  }
  return std::move(parameters);
}

auto Compiler::Parser::ParseParameter() -> std::shared_ptr<ParameterSyntax> {
  auto identifier = MatchToken(SyntaxKind::IdentifierToken);
  auto colon = MatchToken(SyntaxKind::ColonToken);
  auto type = NextToken();
  return std::make_shared<ParameterSyntax>(identifier, type);
}

auto Compiler::Parser::ParseGlobalStatement()
    -> std::shared_ptr<GlobalStatementSyntax> {
  auto statement = ParseStatement();
  return std::make_shared<GlobalStatementSyntax>(statement);
}

auto Compiler::Parser::ParseMembers()
    -> std::vector<std::shared_ptr<MemberSyntax>> {
  std::vector<std::shared_ptr<MemberSyntax>> _members;
  while (Current()->Kind != SyntaxKind::EndOfFileToken &&
         Current()->Kind != SyntaxKind::CloseBraceToken) {
    auto startToken = Current();
    auto _member = ParseMember();
    _members.emplace_back(_member);
    if (Current() == startToken) {
      NextToken();
    }
  }
  return std::move(_members);
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
auto Compiler::Parser::ParsePrimaryExpression()
    -> std::shared_ptr<ExpressionSyntax> {
  auto temp = Current()->Kind;
  if (Equals(Current()->Kind, SyntaxKind::OpenParenthesisToken)) {
    auto left = NextToken();
    auto expression = ParseBinaryExpression(0);
    auto right = MatchToken(SyntaxKind::CloseParenthesisToken);
    return std::make_shared<ParenthesizedExpressionSyntax>(left, expression,
                                                           right);
  } else if (Equals(Current()->Kind, SyntaxKind::TrueToken) ||
             Equals(Current()->Kind, SyntaxKind::FalseToken)) {
    // auto isTrue = Current()->Kind == SyntaxKind::TrueToken;
    auto keyword = NextToken();
    auto _value = keyword->Kind == SyntaxKind::TrueToken;
    return std::make_shared<LiteralExpressionSyntax>(keyword, _value,
                                                     BuildinType::Bool);
  } else if (Equals(Current()->Kind, SyntaxKind::StringToken)) {
    auto stringToken = NextToken();
    return std::make_shared<LiteralExpressionSyntax>(stringToken);
  } else if (Equals(Current()->Kind, SyntaxKind::NumberToken)) {
    auto numberToken = MatchToken(SyntaxKind::NumberToken);
    return std::make_shared<LiteralExpressionSyntax>(numberToken);
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
  for (auto curr = Current(); curr->Kind != SyntaxKind::CloseParenthesisToken &&
                              curr->Kind != SyntaxKind::EndOfFileToken;
       curr = Current()) {
    auto argument = ParseExpression();
    arguments.emplace_back(argument);
    if (Current()->Kind != SyntaxKind::CloseParenthesisToken) {
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
auto Compiler::Parser::ParseTypeClause() -> std::shared_ptr<SyntaxToken> {
  if (Current()->Kind != SyntaxKind::ColonToken) {
    return nullptr;
  }
  auto colonToken = MatchToken(SyntaxKind::ColonToken);
  auto identifier = MatchToken(SyntaxKind::IdentifierToken);
  return identifier;
}
auto Compiler::Parser::ParseVariableDeclaration()
    -> std::shared_ptr<StatementSyntax> {
  auto keyword = NextToken();
  auto mutkeyword =
      (Current()->Kind == SyntaxKind::MutToken) ? NextToken() : nullptr;
  auto identifier = NextToken();
  auto type = ParseTypeClause();
  auto equalsToken = NextToken();
  auto initializer = ParseExpression();
  return std::make_shared<VariableDeclarationSyntax>(
      keyword, mutkeyword, identifier, type, equalsToken, initializer);
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
auto Compiler::Parser::ParseDoWhileStatement()
    -> std::shared_ptr<StatementSyntax> {
  auto dokeyword = MatchToken(SyntaxKind::DoToken);
  auto statement = ParseStatement();
  auto whilekeyword = NextToken();
  // auto openp = MatchToken(SyntaxKind::OpenParenthesisToken);
  auto condition = ParseExpression();
  // auto closep = MatchToken(SyntaxKind::CloseParenthesisToken);
  return std::make_shared<DoWhileStatementSyntax>(dokeyword, statement,
                                                  whilekeyword, condition);
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
