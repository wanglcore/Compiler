#pragma once
#include "BinaryExpressionSyntax.h"
#include "BoundAllExpression.h"
#include "BoundExpression.h"
#include "ExpressionSyntax.h"
#include"Operator.h"
#include "LiteralExpressionSyntax.h"
#include "UnaryExpressionSyntax.h"
namespace Compiler {
class Binder {
 public:
  auto BindExpression(std::shared_ptr<ExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindLiteralExpression(std::shared_ptr<LiteralExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindBinaryExpression(std::shared_ptr<BinaryExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;
  auto BindUnaryExpression(std::shared_ptr<UnaryExpressionSyntax> syntax)
      -> std::shared_ptr<BoundExpression>;

 private:
  //BoundUnaryOperatorKind BindUnaryOperatorKind(SyntaxKind kind, Type type);
  //BoundBinaryOperatorKind BindBinaryOperatorKind(SyntaxKind kind, Type lefttype,
  //                                               Type righttype);
};
}  // namespace Compiler