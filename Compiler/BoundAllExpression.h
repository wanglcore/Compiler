#pragma once
#include <memory>
#include <string>
#include <vector>

#include "BoundExpression.h"
#include "BoundOperator.h"
#include "Type.h"
namespace Compiler {
class BoundUnaryExpression final : public BoundExpression {
 public:
  BoundUnaryExpression(std::shared_ptr<BoundUnaryOperator> _op,
                       std::shared_ptr<BoundExpression> _operand)
      : BoundExpression(BoundNodeKind::UnaryExpression, _operand->type),
        op(_op),
        operand(_operand) {}
  std::shared_ptr<BoundUnaryOperator> op;
  std::shared_ptr<BoundExpression> operand;
  bool EqualsKind(BoundNodeKind other) override {
    return other == BoundNode::Kind;
  }
};

class BoundLiteralExpression final : public BoundExpression {
 public:
  BoundLiteralExpression(Object _value, Type _type)
      : BoundExpression(BoundNodeKind::LiteralExpression, _type),
        value(_value) {}
  Object value;
  bool EqualsKind(BoundNodeKind other) override {
    return other == BoundNode::Kind;
  }
};

class BoundBinaryExpression final : public BoundExpression {
 public:
  BoundBinaryExpression(std::shared_ptr<BoundExpression> _left,
                        std::shared_ptr<BoundBinaryOperator> _op,
                        std::shared_ptr<BoundExpression> _right)
      : BoundExpression(BoundNodeKind::BinaryExpression, _op->resultType),
        op(_op),
        left(_left),
        right(_right) {}
  std::shared_ptr<BoundBinaryOperator> op;
  std::shared_ptr<BoundExpression> left, right;
  bool EqualsKind(BoundNodeKind other) override {
    return other == BoundNode::Kind;
  }
};

class BoundVariableExpression final : public BoundExpression {
 public:
  BoundVariableExpression(VariableSymbol _symbol)
      : BoundExpression(BoundNodeKind::VariableExpression, _symbol.type),
        symbol(_symbol) {}
  VariableSymbol symbol;
};

class BoundAssignmentExpression final : public BoundExpression {
 public:
  BoundAssignmentExpression(VariableSymbol _symbol,
                            std::shared_ptr<BoundExpression> _expression)
      : BoundExpression(BoundNodeKind::AssignmentExpression, _expression->type),
        symbol(_symbol),
        expression(_expression) {}
  VariableSymbol symbol;
  std::shared_ptr<BoundExpression> expression;
};

};  // namespace Compiler