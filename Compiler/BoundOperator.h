#pragma once
#include "Symbol.h"
#include "Type.h"
namespace Compiler {
class BoundUnaryOperator {
 public:
  BoundUnaryOperator(SyntaxKind _syntaxkind, BoundUnaryOperatorKind _kind,
                     TypeSymbol _operandType)
      : BoundUnaryOperator(_syntaxkind, _kind, _operandType, _operandType) {}
  BoundUnaryOperator(SyntaxKind _syntaxkind, BoundUnaryOperatorKind _kind,
                     TypeSymbol _operandType, TypeSymbol _resultType)
      : syntaxkind(_syntaxkind),
        kind(_kind),
        operandType(_operandType),
        resultType(_resultType) {}
  SyntaxKind syntaxkind;
  BoundUnaryOperatorKind kind;
  TypeSymbol operandType;
  TypeSymbol resultType;
};
class BoundBinaryOperator {
 public:
  BoundBinaryOperator(SyntaxKind _syntaxkind, BoundBinaryOperatorKind _kind,
                      TypeSymbol _lefttype, TypeSymbol _righttype,
                      TypeSymbol _resulttype)
      : syntaxkind(_syntaxkind),
        kind(_kind),
        lefttype(_lefttype),
        righttype(_righttype),
        resultType(_resulttype) {}
  SyntaxKind syntaxkind;
  BoundBinaryOperatorKind kind;
  TypeSymbol lefttype, righttype;
  TypeSymbol resultType;
};

}  // namespace Compiler
