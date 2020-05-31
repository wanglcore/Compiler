#include "Lexer.h"
namespace Compiler {
std::shared_ptr<SyntaxToken> Lexer::NextToken() {
  if (position >= length) {
    return std::make_shared<SyntaxToken>(SyntaxKind::EndOfFileToken, position,
                                         "\0");
  }
  if (std::isdigit(Current())) {
    int start = position;
    while (std::isdigit(Current())) {
      Next();
    }
    auto _text = text.substr(start, position - start);
    Object value = std::stoi(_text);
    return std::make_shared<SyntaxToken>(SyntaxKind::NumberToken, start, _text,
                                         value, Type::IntType);
  }
  if (std::islower(Current())) {
    int start = position;
    while (std::islower(Current())) {
      Next();
    }
    auto _text = text.substr(start, position - start);
    auto keyword = SyntaxFacts::GetKeyWordKind(_text);
    return std::make_shared<SyntaxToken>(keyword, start, _text);
  }
  if (std::isspace(Current())) {
    int start = position;
    while (std::isspace(Current())) {
      Next();
      /* code */
    }
    auto _text = text.substr(start, position - start);
    return std::make_shared<SyntaxToken>(SyntaxKind::SpaceToken, start, _text);
  }
  if (Current() == '|') {
    if (LookHead() == '|') {
      position++;
      return std::make_shared<SyntaxToken>(SyntaxKind::PipePipeToken,
                                           position - 1, "||");
    }
  }
  if (Current() == '&') {
    if (LookHead() == '&') {
      position++;
      return std::make_shared<SyntaxToken>(SyntaxKind::AmpersandAmpersandToken,
                                           position - 1, "&&");
    }
  }

  if (Current() == '!') {
    return std::make_shared<SyntaxToken>(SyntaxKind::BangToken, ++position,
                                         "!");
  }
  if (Current() == '+') {
    return std::make_shared<SyntaxToken>(SyntaxKind::PlusToken, ++position,
                                         "+");
  }
  if (Current() == '-') {
    return std::make_shared<SyntaxToken>(SyntaxKind::MinusToken, ++position,
                                         "-");
  }
  if (Current() == '*') {
    return std::make_shared<SyntaxToken>(SyntaxKind::StarToken, ++position,
                                         "*");
  }
  if (Current() == '/') {
    return std::make_shared<SyntaxToken>(SyntaxKind::SlashToken, ++position,
                                         "/");
  }
  if (Current() == '(') {
    return std::make_shared<SyntaxToken>(SyntaxKind::OpenParenthesisToken,
                                         ++position, "(");
  }
  if (Current() == ')') {
    return std::make_shared<SyntaxToken>(SyntaxKind::CloseParenthesisToken,
                                         ++position, ")");
  }
  ++position;
  return std::make_shared<SyntaxToken>(SyntaxKind::BadToken, position - 1,
                                       text.substr(position - 1, 1));
}
}  // namespace Compiler
