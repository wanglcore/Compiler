#pragma once
#include "BoundNode.h"
#include "Type.h"
namespace Compiler {
class BoundExpression : public BoundNode {
public:
  BoundExpression(BoundNodeKind kind, TypeSymbol _type)
      : BoundNode(kind), type(_type) {}
  TypeSymbol type;
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
};

} // namespace Compiler
