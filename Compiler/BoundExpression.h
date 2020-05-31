#pragma once
#include "BoundNode.h"
#include "Type.h"
namespace Compiler {
class BoundExpression : public BoundNode {
 public:
  BoundExpression(BoundNodeKind kind, Type _type)
      : BoundNode(kind), type(_type) {}
  Type type{Type::DefaultType};
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
};

}  // namespace Compiler