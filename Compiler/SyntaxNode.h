#pragma once
#include <experimental/generator>

#include "Type.h"
namespace Compiler {
class SyntaxNode {
 public:
  SyntaxNode(SyntaxKind kind) : Kind(kind){};
  SyntaxKind Kind{SyntaxKind::DefaultToken};
  virtual bool EqualsKind(SyntaxKind other)  {return other==Kind;}
  virtual NodeKind GetNodeKind()  {return NodeKind::SyntaxNodeNode;}
  virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
  GetChildren() const {co_yield nullptr;};
  virtual size_t GetMemberLength()const{return 0;}
  virtual ~SyntaxNode() {}
};
}  // namespace Compiler
