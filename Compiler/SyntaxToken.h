#pragma once
#include <string>

#include "SyntaxNode.h"
#include "Type.h"
namespace Compiler {
class SyntaxToken final : public SyntaxNode {
 public:
  SyntaxToken(SyntaxKind _kind, int _position, std::string _text)
      : SyntaxToken(_kind, _position, _text, nullptr, Type::DefaultType) {}
  SyntaxToken(SyntaxKind _kind, int _position, std::string _text,Object _value,Type _type)
      : SyntaxNode(_kind),
        position(_position),
        text(_text),
        value(_value),
        nodeKind(NodeKind::SyntaxTokenNode),type(_type) {}
  int position{0};
  std::string text;
  Object value;
  NodeKind nodeKind{NodeKind::DefaultTokenNode};
  Type type {Type::DefaultType};
  bool EqualsKind(SyntaxKind other)  override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren() const
       override {
    co_yield nullptr;
  }
  size_t GetMemberLength() const override { return 0; }

  NodeKind GetNodeKind() override { return nodeKind; }
  ~SyntaxToken() = default;
};
}  // namespace Compiler
