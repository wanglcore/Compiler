#pragma once
#include "Type.h"
namespace Compiler {
class BoundNode {
public:
  BoundNode(BoundNodeKind kind) : Kind(kind) {}
  BoundNodeKind Kind{BoundNodeKind::DefaultBoundNodeKind};
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
  virtual ~BoundNode() {}
};
class BoundLabel {
public:
  BoundLabel(std::string _name) : name(_name) {}
  std::string name;
};
} // namespace Compiler
