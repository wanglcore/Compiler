#pragma once
#include <memory>
#include <vector>

#include "BoundExpression.h"
#include "BoundNode.h"
#include "Type.h"
namespace Compiler {
class BoundStatement : public BoundNode {
 public:
  BoundStatement(BoundNodeKind kind) : BoundNode(kind) {}
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
};

class BoundBlockStatement final : public BoundStatement {
 public:
  BoundBlockStatement(std::vector<std::shared_ptr<BoundStatement>> _statements)
      : BoundStatement(BoundNodeKind::BlockStatement),
        statements(_statements) {}
  std::vector<std::shared_ptr<BoundStatement>> statements;
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
};
class BoundExpressionStatement final : public BoundStatement {
 public:
  BoundExpressionStatement(std::shared_ptr<BoundExpression> _expression)
      : BoundStatement(BoundNodeKind::ExpressionStatement),
        expression(_expression) {}
  std::shared_ptr<BoundExpression> expression;
  virtual bool EqualsKind(BoundNodeKind other) { return other == Kind; }
};
}  // namespace Compiler