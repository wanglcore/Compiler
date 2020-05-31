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
        return 5;
        break;
      default:
        return 0;
        break;
    }
  }
  static int GetBinaryOperatorPrecedence(SyntaxKind kind) {
    switch (kind) {
      case Compiler::SyntaxKind::StarToken:
      case Compiler::SyntaxKind::SlashToken:
        return 4;
      case Compiler::SyntaxKind::PlusToken:
      case Compiler::SyntaxKind::MinusToken:
        return 3;

      case SyntaxKind::AmpersandAmpersandToken:
        return 2;
      case SyntaxKind::PipePipeToken:
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
    else
      return SyntaxKind::IdentifierToken;
  }
};
}  // namespace Compiler