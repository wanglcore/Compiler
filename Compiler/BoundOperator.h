#pragma once
#include "Type.h"

namespace Compiler {
class BoundUnaryOperator {
 public:
  BoundUnaryOperator(SyntaxKind _syntaxkind, BoundUnaryOperatorKind _kind,
                     Type _operandType)
      : BoundUnaryOperator(_syntaxkind, _kind, _operandType, _operandType) {}
  BoundUnaryOperator(SyntaxKind _syntaxkind, BoundUnaryOperatorKind _kind,
                     Type _operandType, Type _resultType)
      : syntaxkind(_syntaxkind),
        kind(_kind),
        operandType(_operandType),
        resultType(_resultType) {}
  SyntaxKind syntaxkind;
  BoundUnaryOperatorKind kind;
  Type operandType;
  Type resultType;
};
class BoundBinaryOperator {
 public:
  BoundBinaryOperator(SyntaxKind _syntaxkind, BoundBinaryOperatorKind _kind,
                      Type _lefttype, Type _righttype, Type _resulttype)
      : syntaxkind(_syntaxkind),
        kind(_kind),
        lefttype(_lefttype),
        righttype(_righttype),
        resultType(_resulttype) {}
  SyntaxKind syntaxkind;
  BoundBinaryOperatorKind kind;
  Type lefttype, righttype;
  Type resultType;
};

}  // namespace Compiler