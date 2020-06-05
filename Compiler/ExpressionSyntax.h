#pragma once
#include "SyntaxNode.h"
#include "Type.h"
namespace Compiler {
class ExpressionSyntax : public SyntaxNode {
public:
  ExpressionSyntax(SyntaxKind kind) : SyntaxNode(kind) {}
  /*
  virtual bool EqualsKind(SyntaxKind other) { return SyntaxNode::Kind == other;
  } virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
  GetChildren() const {co_yield nullptr;};
  virtual NodeKind GetNodeKind() { return NodeKind::ExpressionSyntaxNode; }
  virtual size_t GetMemberLength() const { return 0; }
  */
  virtual ~ExpressionSyntax() {}
};

} // namespace Compiler
