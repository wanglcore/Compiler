#pragma once

#include <memory>
#include <string>

#include "CompilationUnitSyntax.h"
#include "ExpressionSyntax.h"
#include "Parser.h"
#include "SourceText.h"
#include "SyntaxToken.h"
namespace Compiler {
class SyntaxTree {
 public:
  SyntaxTree(std::shared_ptr<SourceText> _sourcetext)
      : sourceText(_sourcetext) {
    auto parser = std::make_shared<Parser>(_sourcetext);
    root = parser->ParseCompilationUnit();
  }
  std::shared_ptr<SourceText> sourceText;
  SyntaxTree(std::shared_ptr<CompilationUnitSyntax> _compilationUnitSyntax)
      : root(_compilationUnitSyntax) {}
  std::shared_ptr<CompilationUnitSyntax> root;
  // SyntaxTree(std::shared_ptr<ExpressionSyntax> _root,
  //           std::shared_ptr<SyntaxToken> _endOfToken)
  //    : root(_root), endOfToken(_endOfToken) {}
  // std::shared_ptr<ExpressionSyntax> root;
  // std::shared_ptr<SyntaxToken> endOfToken;

  static std::shared_ptr<SyntaxTree> Parse(std::string _text) {
    auto sourcetext = SourceText::From(_text);
    return Parse(sourcetext);
  }
  static std::shared_ptr<SyntaxTree> Parse(
      std::shared_ptr<SourceText> _sourcetext) {
    /*auto parser = std::make_shared<Parser>(_sourcetext);
    return parser->Parse();*/
    return std::make_shared<SyntaxTree>(_sourcetext);
  }
};
}  // namespace Compiler
