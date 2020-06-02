#pragma once
#include "ExpressionSyntax.h"
#include "SyntaxToken.h"
namespace Compiler {

class NameExpressionSyntax final : public ExpressionSyntax {
 public:
  NameExpressionSyntax(std::shared_ptr<SyntaxToken> _identifierToken)
      : ExpressionSyntax(SyntaxKind::NameExpression),
        identifierToken(_identifierToken) {}
  std::shared_ptr<SyntaxToken> identifierToken;

  bool EqualsKind(SyntaxKind other) override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield identifierToken;
  }
  size_t GetMemberLength() const override { return 1; }

  NodeKind GetNodeKind() override { return NodeKind::NameExpressionNode; }
};

class AssignmentExpressionSyntax final : public ExpressionSyntax {
 public:
  AssignmentExpressionSyntax(std::shared_ptr<SyntaxToken> _identifierToken,
                             std::shared_ptr<SyntaxToken> _equalsToken,
                             std::shared_ptr<ExpressionSyntax> _expression)
      : ExpressionSyntax(SyntaxKind::AssignmentExpression),
        identifierToken(_identifierToken),
        equalsToken(_equalsToken),
        expression(_expression) {}
  std::shared_ptr<SyntaxToken> identifierToken;
  std::shared_ptr<SyntaxToken> equalsToken;
  std::shared_ptr<ExpressionSyntax> expression;

  bool EqualsKind(SyntaxKind other) override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield identifierToken;
    co_yield equalsToken;
    co_yield expression;
  }
  size_t GetMemberLength() const override { return 3; }

  NodeKind GetNodeKind() override { return NodeKind::AssignmentExpressionNode; }
};

}  // namespace Compiler