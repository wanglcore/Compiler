#pragma once

#include "ExpressionSyntax.h"
#include "Parser.h"
#include "SyntaxToken.h"
#include <memory>
#include <string>
namespace Compiler {
class SyntaxTree {
public:
  SyntaxTree(std::shared_ptr<ExpressionSyntax> _root,
             std::shared_ptr<SyntaxToken> _endOfToken)
      : root(_root), endOfToken(_endOfToken) {}
  std::shared_ptr<ExpressionSyntax> root;
  std::shared_ptr<SyntaxToken> endOfToken;

  static std::shared_ptr<SyntaxTree> Parse(std::string _text) {
    auto parser = std::make_shared<Parser>(_text);
    return parser->Parse();
  }
};
} // namespace Compiler
