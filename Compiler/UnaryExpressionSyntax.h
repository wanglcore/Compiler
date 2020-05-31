#pragma once
#include <memory>

#include "ExpressionSyntax.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class UnaryExpressionSyntax final : public ExpressionSyntax {
 public:
  UnaryExpressionSyntax(std::shared_ptr<SyntaxToken> _op,
                        std::shared_ptr<ExpressionSyntax> _operand)
      : ExpressionSyntax(SyntaxKind::UnaryExpression),
        op(_op),
        operand(_operand) {}
  std::shared_ptr<SyntaxToken> op;//²Ù×÷·û
  std::shared_ptr<ExpressionSyntax> operand;//²Ù×÷Êý

  bool EqualsKind(SyntaxKind other) override {
    return ExpressionSyntax::Kind == other;
  }
  size_t GetMemberLength() const override { return 3; }

  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield op;
    co_yield operand;
  }
  NodeKind GetNodeKind() override {
    return NodeKind::BinaryExpressionSyntaxNode;
  }
};
}  // namespace Compiler
