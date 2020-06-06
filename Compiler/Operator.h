#pragma once
#include <memory>
#include <vector>

#include "BoundAllExpression.h"

namespace Compiler {
class Operators {
public:
  static std::vector<std::shared_ptr<BoundUnaryOperator>> unaryOperators;
  static std::shared_ptr<BoundUnaryOperator>
  BindUnaryOperator(SyntaxKind kind, BuildinType operandType);
  static std::vector<std::shared_ptr<BoundBinaryOperator>> binaryOperators;
  static std::shared_ptr<BoundBinaryOperator>
  BindBinaryOperator(SyntaxKind kind, BuildinType lefttype,
                     BuildinType righttype);
};
} // namespace Compiler
