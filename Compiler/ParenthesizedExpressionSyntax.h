#pragma once
#include <memory>

#include "ExpressionSyntax.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class ParenthesizedExpressionSyntax final : public ExpressionSyntax {
 public:
  ParenthesizedExpressionSyntax(
      std::shared_ptr<SyntaxToken> _openParenthesisToken,
      std::shared_ptr<ExpressionSyntax> _expression,
      std::shared_ptr<SyntaxToken> _closeParenthesisToken)
      : ExpressionSyntax(SyntaxKind::ParenthesizedExpression),
        openParenthesisToken(_openParenthesisToken),
        closeParenthesisToken(_closeParenthesisToken),
        expression(_expression) {}
  std::shared_ptr<SyntaxToken> openParenthesisToken, closeParenthesisToken;
  std::shared_ptr<ExpressionSyntax> expression;

  bool EqualsKind(SyntaxKind other)  override {
    return ExpressionSyntax::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()const
       override {
    co_yield openParenthesisToken;
    co_yield expression;
    co_yield closeParenthesisToken;
  }
  size_t GetMemberLength() const override { return 3; }

  NodeKind GetNodeKind()  override {
    return NodeKind::ParenthesizedExpressionSyntaxNode;
  }
};
}  // namespace Compiler
