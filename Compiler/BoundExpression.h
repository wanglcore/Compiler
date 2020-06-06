#pragma once
#include "BoundNode.h"
#include "Symbol.h"
#include "Type.h"
namespace Compiler {
class BoundExpression : public BoundNode {
public:
  BoundExpression(BoundNodeKind kind, BuildinType _type)
      : BoundNode(kind), type(_type) {}
  BuildinType type;
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
};
// bool operator==(std::shared_ptr<BoundExpression> p1,
//                 std::shared_ptr<BoundExpression> p2) {
//   return p1->type == p2->type;
// }
} // namespace Compiler
