#pragma once
#include <memory>
#include <variant>

#include "ExpressionSyntax.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class LiteralExpressionSyntax final : public ExpressionSyntax {
 public:
  LiteralExpressionSyntax(std::shared_ptr<SyntaxToken> _literalToken,
                          Object _value, Type _type)
      : ExpressionSyntax(SyntaxKind::LiteralExpression),
        literalToken(_literalToken),
        value(_value),
        type(_type) {}
  LiteralExpressionSyntax(std::shared_ptr<SyntaxToken> _literalToken)
      : LiteralExpressionSyntax(_literalToken, _literalToken->value,
                                _literalToken->type) {}
  std::shared_ptr<SyntaxToken> literalToken;
  Object value;
  Type type;
  bool EqualsKind(SyntaxKind other) override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield literalToken;
  }
  size_t GetMemberLength() const override { return 1; }

  NodeKind GetNodeKind() override {
    return NodeKind::LiteralExpressionSyntaxNode;
  }
};
}  // namespace Compiler
