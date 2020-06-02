#pragma once
#include <memory>
#include <vector>

#include "ExpressionSyntax.h"
#include "SyntaxNode.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class StatementSyntax : public SyntaxNode {
 public:
  StatementSyntax(SyntaxKind kind) : SyntaxNode(kind) {}
  virtual bool EqualsKind(SyntaxKind other) {
    return SyntaxNode::Kind == other;
  }
  virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
  GetChildren() const {
    co_yield nullptr;
  };
  virtual NodeKind GetNodeKind() { return NodeKind::ExpressionSyntaxNode; }
  virtual size_t GetMemberLength() const { return 0; }

  virtual ~StatementSyntax() {}
};

class BlockStatementSyntax final : public StatementSyntax {
 public:
  BlockStatementSyntax(std::shared_ptr<SyntaxToken> _openBraceToken,
                       std::vector<std::shared_ptr<StatementSyntax>> _statements,
                       std::shared_ptr<SyntaxToken> _closeBraceToken)
      : StatementSyntax(SyntaxKind::BlockStatement),
        openBraceToken(_openBraceToken),
        statements(_statements),
        closeBraceToken(_closeBraceToken) {}

  std::shared_ptr<SyntaxToken> openBraceToken;
  std::vector<std::shared_ptr<StatementSyntax>> statements;
  std::shared_ptr<SyntaxToken> closeBraceToken;

  virtual bool EqualsKind(SyntaxKind other) {
    return SyntaxNode::Kind == other;
  }
  virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
  GetChildren() const {
    co_yield nullptr;
  };
  virtual NodeKind GetNodeKind() { return NodeKind::BlockStatementNode; }
  virtual size_t GetMemberLength() const { return 0; }
};
class ExpressionStatementSyntax final : public StatementSyntax {
 public:
  ExpressionStatementSyntax(std::shared_ptr<ExpressionSyntax> _expression)
      : StatementSyntax(SyntaxKind::ExpressionStatement),
        expression(_expression) {}

  std::shared_ptr<ExpressionSyntax> expression;

  virtual bool EqualsKind(SyntaxKind other) {
    return SyntaxNode::Kind == other;
  }
  virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
  GetChildren() const {
    co_yield nullptr;
  };
  virtual NodeKind GetNodeKind() { return NodeKind::ExpressionStatementNode; }
  virtual size_t GetMemberLength() const { return 0; }
};

}  // namespace Compiler