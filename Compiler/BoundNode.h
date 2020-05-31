#pragma once
#include "Type.h"
namespace Compiler {
class BoundNode {
 public:
  BoundNode(BoundNodeKind kind) : Kind(kind) {}
  BoundNodeKind Kind{BoundNodeKind::DefaultBoundNodeKind};
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
  virtual ~BoundNode(){}
};
}  // namespace Compiler