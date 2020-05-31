#pragma once

#include <memory>

#include "ExpressionSyntax.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class BinaryExpressionSyntax final : public ExpressionSyntax {
 public:
  BinaryExpressionSyntax(std::shared_ptr<ExpressionSyntax> _left,
                         std::shared_ptr<SyntaxToken> _op,
                         std::shared_ptr<ExpressionSyntax> _right)
      : ExpressionSyntax(SyntaxKind::BinaryExpression),
        left(_left),
        right(_right),
        op(_op) {}
  std::shared_ptr<ExpressionSyntax> left, right;
  std::shared_ptr<SyntaxToken> op;//²Ù×÷·û

  bool EqualsKind(SyntaxKind other) override {
    return ExpressionSyntax::Kind == other;
  }
   size_t GetMemberLength() const override { return 3; }

  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()const
      override {
    co_yield left;
    co_yield op;
    co_yield right;
  }
  NodeKind GetNodeKind() override {
    return NodeKind::BinaryExpressionSyntaxNode;
  }
};
}  // namespace Compiler
