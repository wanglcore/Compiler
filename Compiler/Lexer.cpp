#include "Lexer.h"
namespace Compiler {
std::shared_ptr<SyntaxToken> Lexer::NextToken() {
  if (position >= length) {
    return std::make_shared<SyntaxToken>(SyntaxKind::EndOfFileToken, position,
                                         "\0");
  } else if (std::isdigit(Current())) {
    int start = position;
    while (std::isdigit(Current())) {
      Next();
    }
    auto _text = text->SubString(start, position - start);
    // auto _text = text.substr(start, position - start);
    Object value = std::stoi(_text);
    return std::make_shared<SyntaxToken>(SyntaxKind::NumberToken, start, _text,
                                         value, BuildinType::Int);
  } else if (std::isalpha(Current())) {
    int start = position;
    while (std::isalpha(Current())) {
      Next();
    }
    // auto _text = text.substr(start, position - start);
    auto _text = text->SubString(start, position - start);
    auto keyword = SyntaxFacts::GetKeyWordKind(_text);
    return std::make_shared<SyntaxToken>(keyword, start, _text);
  } else if (std::isspace(Current()) || Current() == ' ' || Current() == '\n' ||
             Current() == '\t' || Current() == '\r') {
    int start = position;
    while (std::isspace(Current()) || Current() == ' ' || Current() == '\n' ||
           Current() == '\t' || Current() == '\r') {
      Next();
      /* code */
    }
    // auto _text = text.substr(start, position - start);
    auto _text = text->SubString(start, position - start);

    return std::make_shared<SyntaxToken>(SyntaxKind::SpaceToken, start, _text);
  } else if (Current() == '"') {
    ++position;
    int start = position;
    bool done = false;
    while (!done) {
      char curr = Current();
      switch (curr) {
      case '\0':
      case '\r':
      case '\n':
        done = true;
        break;
      case '"':
        if (LookHead() == '"') {
          position += 2;
        } else {
          position++;
          done = true;
        }
        break;
      default:
        ++position;
        break;
      }
    }
    std::string sb = text->SubString(start, position - start);
    return std::make_shared<SyntaxToken>(SyntaxKind::StringToken, start - 1, sb,
                                         sb, BuildinType::String);
  } else if (Current() == '|') {
    if (LookHead() == '|') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::PipePipeToken,
                                           position - 2, "||");
    } else {
      ++position;
      return std::make_shared<SyntaxToken>(SyntaxKind::PipeToken, position - 1,
                                           "|");
    }
  } else if (Current() == ',') {
    return std::make_shared<SyntaxToken>(SyntaxKind::CommaToken, ++position,
                                         ",");
  } else if (Current() == '&') {
    if (LookHead() == '&') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::AmpersandAmpersandToken,
                                           position - 2, "&&");
    } else {
      ++position;
      return std::make_shared<SyntaxToken>(SyntaxKind::AmpersandToken,
                                           position - 1, "&");
    }
  } else if (Current() == '=') {
    if (LookHead() == '=') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::EqualsEqualsToken,
                                           position - 2, "==");
    } else {
      ++position;
      return std::make_shared<SyntaxToken>(SyntaxKind::EqualsToken,
                                           position - 1, "=");
    }
  } else if (Current() == '>') {
    if (LookHead() == '=') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::GreaterOrEqualToken,
                                           position - 2, ">=");
    } else {
      ++position;
      return std::make_shared<SyntaxToken>(SyntaxKind::GreaterToken,
                                           position - 1, ">");
    }
  } else if (Current() == '<') {
    if (LookHead() == '=') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::LessOrEqualToken,
                                           position - 2, "<=");
    } else {
      ++position;
      return std::make_shared<SyntaxToken>(SyntaxKind::LessToken, position - 1,
                                           "<");
    }
  } else if (Current() == '!') {
    if (LookHead() == '=') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::NotEqualsToken,
                                           position - 2, "!=");
    } else {
      ++position;
      return std::make_shared<SyntaxToken>(SyntaxKind::BangToken, position - 1,
                                           "!");
    }
  } else if (Current() == '^') {
    return std::make_shared<SyntaxToken>(SyntaxKind::HatToken, ++position, "^");
  } else if (Current() == '~') {
    return std::make_shared<SyntaxToken>(SyntaxKind::TiledeToken, ++position,
                                         "~");
  } else if (Current() == ':') {
    return std::make_shared<SyntaxToken>(SyntaxKind::ColonToken, ++position,
                                         ":");
  } else if (Current() == '+') {
    if (LookHead() == '=') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::PlusEqualsToken,
                                           position - 2, "+=");
    } else if (LookHead() == '+') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::PlusPlusToken,
                                           position - 2, "++");
    }
    position++;
    return std::make_shared<SyntaxToken>(SyntaxKind::PlusToken, position - 1,
                                         "+");
  } else if (Current() == '-') {
    if (LookHead() == '=') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::MinusEqualsToken,
                                           position - 2, "-=");
    } else if (LookHead() == '-') {
      position += 2;
      return std::make_shared<SyntaxToken>(SyntaxKind::MinusMinusToken,
                                           position - 2, "--");
    }
    position++;
    return std::make_shared<SyntaxToken>(SyntaxKind::MinusToken, position - 1,
                                         "-");
  } else if (Current() == '*') {
    return std::make_shared<SyntaxToken>(SyntaxKind::StarToken, ++position,
                                         "*");
  } else if (Current() == '/') {
    return std::make_shared<SyntaxToken>(SyntaxKind::SlashToken, ++position,
                                         "/");
  } else if (Current() == '(') {
    return std::make_shared<SyntaxToken>(SyntaxKind::OpenParenthesisToken,
                                         ++position, "(");
  } else if (Current() == ')') {
    return std::make_shared<SyntaxToken>(SyntaxKind::CloseParenthesisToken,
                                         ++position, ")");
  } else if (Current() == '{') {
    return std::make_shared<SyntaxToken>(SyntaxKind::OpenBraceToken, ++position,
                                         "{");
  } else if (Current() == '}') {
    return std::make_shared<SyntaxToken>(SyntaxKind::CloseBraceToken,
                                         ++position, "}");
  }
  ++position;
  return std::make_shared<SyntaxToken>(SyntaxKind::BadToken, position - 1,
                                       text->SubString(position - 1, 1));
}
} // namespace Compiler
