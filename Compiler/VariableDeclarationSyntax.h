#pragma once
#include "Statement.h"
namespace Compiler {
class VariableDeclarationSyntax final : public StatementSyntax {
 public:
  VariableDeclarationSyntax(std::shared_ptr<SyntaxToken> _keyword,
                            std::shared_ptr<SyntaxToken> _identifier,
                            std::shared_ptr<SyntaxToken> _equalsToken,
                            std::shared_ptr<ExpressionSyntax> _initializer)
      : VariableDeclarationSyntax(_keyword, nullptr, _identifier, _equalsToken,
                                  _initializer) {}
  VariableDeclarationSyntax(std::shared_ptr<SyntaxToken> _keyword,
                            std::shared_ptr<SyntaxToken> _mutkeyword,
                            std::shared_ptr<SyntaxToken> _identifier,
                            std::shared_ptr<SyntaxToken> _equalsToken,
                            std::shared_ptr<ExpressionSyntax> _initializer)
      : StatementSyntax(SyntaxKind::VariableDeclaration),
        keyword(_keyword),
        mutkeyword(_mutkeyword),
        identifier(_identifier),
        equalsToken(_equalsToken),
        initializer(_initializer) {}
  std::shared_ptr<SyntaxToken> keyword;
  std::shared_ptr<SyntaxToken> identifier;
  std::shared_ptr<SyntaxToken> equalsToken;
  std::shared_ptr<ExpressionSyntax> initializer;
  std::shared_ptr<SyntaxToken> mutkeyword;
};
}  // namespace Compiler