#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "BinaryExpressionSyntax.h"
#include "ExpressionSyntax.h"
#include "Lexer.h"
#include "ParenthesizedExpressionSyntax.h"
#include "SyntaxFacts.h"
#include "SyntaxToken.h"
#include "Type.h"
#include "UnaryExpressionSyntax.h"
namespace Compiler {
class SyntaxTree;
class Parser {
 public:
  Parser(std::string _text);
  auto Peek(int offset) -> std::shared_ptr<SyntaxToken>;
  auto Parse() -> std::shared_ptr<SyntaxTree>;
  // auto ParseTerm() -> std::shared_ptr<ExpressionSyntax>;
  // auto ParseFactor() -> std::shared_ptr<ExpressionSyntax>;
  // auto ParseExpression() -> std::shared_ptr<ExpressionSyntax>;
  auto ParsePrimaryExpression() -> std::shared_ptr<ExpressionSyntax>;
  auto ParseExpression(int) -> std::shared_ptr<ExpressionSyntax>;
  inline auto Match(SyntaxKind _kind) -> std::shared_ptr<SyntaxToken> {
    if (Equals(Current()->Kind, _kind)) {
      return NextToken();
    }
    return nullptr;  // error code
  }
  inline auto Current() -> std::shared_ptr<SyntaxToken> { return Peek(0); }
  inline auto NextToken() -> std::shared_ptr<SyntaxToken> {
    auto cur = Current();
    ++position;
    return cur;
  }

 private:
  inline auto Equals(SyntaxKind type1, SyntaxKind type2) -> bool {
    return type1 == type2;
  }
  std::vector<std::shared_ptr<SyntaxToken>> tokens;
  size_t tokens_length{0};
  int position{0};
};
}  // namespace Compiler
