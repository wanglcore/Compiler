#pragma once
#include "Symbol.h"
#include "Type.h"
namespace Compiler {
class BoundUnaryOperator {
 public:
  BoundUnaryOperator(SyntaxKind _syntaxkind, BoundUnaryOperatorKind _kind,
                     BuildinType _operandType)
      : BoundUnaryOperator(_syntaxkind, _kind, _operandType, _operandType) {}
  BoundUnaryOperator(SyntaxKind _syntaxkind, BoundUnaryOperatorKind _kind,
                     BuildinType _operandType, BuildinType _resultType)
      : syntaxkind(_syntaxkind),
        kind(_kind),
        operandType(_operandType),
        resultType(_resultType) {}
  SyntaxKind syntaxkind;
  BoundUnaryOperatorKind kind;
  BuildinType operandType;
  BuildinType resultType;
};
class BoundBinaryOperator {
 public:
  BoundBinaryOperator(SyntaxKind _syntaxkind, BoundBinaryOperatorKind _kind,
                      BuildinType _lefttype, BuildinType _righttype,
                      BuildinType _resulttype)
      : syntaxkind(_syntaxkind),
        kind(_kind),
        lefttype(_lefttype),
        righttype(_righttype),
        resultType(_resulttype) {}
  SyntaxKind syntaxkind;
  BoundBinaryOperatorKind kind;
  BuildinType lefttype, righttype;
  BuildinType resultType;
};

}  // namespace Compiler
