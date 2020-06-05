#pragma once
#include "ExpressionSyntax.h"
#include "Statement.h"
#include "SyntaxNode.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class CompilationUnitSyntax : public SyntaxNode {
public:
  CompilationUnitSyntax(std::shared_ptr<StatementSyntax> _statement,
                        std::shared_ptr<SyntaxToken> _endOfFileToken)
      : SyntaxNode(SyntaxKind::CompilationUnit), statement(_statement),
        endOfFileToken(_endOfFileToken),
        nodeKind(NodeKind::CompilationUnitNode) {}
  std::shared_ptr<StatementSyntax> statement;
  std::shared_ptr<SyntaxToken> endOfFileToken;
  NodeKind nodeKind{NodeKind::DefaultTokenNode};
  /*
  bool EqualsKind(SyntaxKind other) override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield statement;
  }
  size_t GetMemberLength() const override { return 0; }
  NodeKind GetNodeKind() override { return nodeKind; }
  */
};

} // namespace Compiler
