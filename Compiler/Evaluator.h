#pragma once
#include <memory>
#include <string>

#include "BinaryExpressionSyntax.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
#include "ParenthesizedExpressionSyntax.h"
#include "Type.h"
#include "UnaryExpressionSyntax.h"
namespace Compiler {
class Evaluator {
 public:
  Evaluator(std::shared_ptr<BoundExpression> _root) : root(_root) {}
  Object Evaluate();
  Object EvaluateExpression(std::shared_ptr<BoundExpression> _root);
  std::shared_ptr<BoundExpression> root;
  template <typename T>
  bool Equals(T T1, T T2) {
    return T1 == T2;
  }
};

}  // namespace Compiler