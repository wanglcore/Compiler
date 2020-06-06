#pragma once
#include <vector>

#include "ExpressionSyntax.h"
#include "MemberSyntax.h"
#include "Statement.h"
#include "SyntaxNode.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class CompilationUnitSyntax : public SyntaxNode {
 public:
  CompilationUnitSyntax(std::vector<std::shared_ptr<MemberSyntax>> _members,
                        std::shared_ptr<SyntaxToken> _endOfFileToken)
      : SyntaxNode(SyntaxKind::CompilationUnit),
        members(std::move(_members)),
        endOfFileToken(_endOfFileToken){}
  std::vector<std::shared_ptr<MemberSyntax>> members;
  std::shared_ptr<SyntaxToken> endOfFileToken;
  //NodeKind nodeKind{NodeKind::DefaultTokenNode};
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

}  // namespace Compiler
