#pragma once
#include "Type.h"
namespace Compiler {
class SyntaxFacts {
 public:
  static int GetUnaryOperatorPrecedence(SyntaxKind kind) {
    switch (kind) {
      case SyntaxKind::PlusToken:
      case SyntaxKind::MinusToken:
      case SyntaxKind::BangToken:
      case SyntaxKind::TiledeToken:
        return 7;
        break;
      default:
        return 0;
        break;
    }
  }
  static int GetBinaryOperatorPrecedence(SyntaxKind kind) {
    switch (kind) {
      case SyntaxKind::PlusEqualsToken:
      case SyntaxKind::MinusEqualsToken:
          return 6;
      case Compiler::SyntaxKind::StarToken:
      case Compiler::SyntaxKind::SlashToken:
        return 5;
      case Compiler::SyntaxKind::PlusToken:
      case Compiler::SyntaxKind::MinusToken:
        return 4;
      case Compiler::SyntaxKind::NotEqualsToken:
      case Compiler::SyntaxKind::EqualsEqualsToken:
      case SyntaxKind::LessOrEqualToken:
      case SyntaxKind::LessToken:
      case SyntaxKind::GreaterOrEqualToken:
      case SyntaxKind::GreaterToken:
        return 3;
      case SyntaxKind::AmpersandAmpersandToken:
      case SyntaxKind::AmpersandToken:
        return 2;
      case SyntaxKind::PipePipeToken:
      case SyntaxKind::PipeToken:
      case SyntaxKind::HatToken:
        return 1;
      default:
        return 0;
        break;
    }
  }
  static SyntaxKind GetKeyWordKind(std::string text) {
    if (text == "true")
      return SyntaxKind::TrueToken;
    else if (text == "false")
      return SyntaxKind::FalseToken;
    else if (text == "let")
      return SyntaxKind::LetToken;
    else if (text == "var")
      return SyntaxKind::VarToken;
    else if (text == "mut")
      return SyntaxKind::MutToken;
    else if (text == "for")
      return SyntaxKind::ForToken;
    else if (text == "if")
      return SyntaxKind::IfToken;
    else if (text == "else")
      return SyntaxKind::ElseToken;
    else if (text == "while")
      return SyntaxKind::WhileToken;
    else if (text == "do")
      return SyntaxKind::DoToken;
    else
      return SyntaxKind::IdentifierToken;
  }
};
}  // namespace Compiler