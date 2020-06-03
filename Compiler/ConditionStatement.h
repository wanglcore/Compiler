#pragma once
#include <memory>

#include "Statement.h"
#include "SyntaxToken.h"

namespace Compiler {
using stdtoken = std::shared_ptr<SyntaxToken>;
using stdexp = std::shared_ptr<ExpressionSyntax>;
using stdstate = std::shared_ptr<StatementSyntax>;

class ElseClauseSyntax final : public SyntaxNode {
 public:
  ElseClauseSyntax(stdtoken _elsekeyword, stdstate _elsestatement)
      : SyntaxNode(SyntaxKind::ElseClause),
        elsekeyword(_elsekeyword),
        elsestatement(_elsestatement) {}
  stdtoken elsekeyword;
  stdstate elsestatement;
};
class IfStatementSyntax final : public StatementSyntax {
 public:
  IfStatementSyntax(stdtoken _ifkeyword, stdexp _condition,
                    stdstate _thenstatement,
                    std::shared_ptr<ElseClauseSyntax> _elseClause)
      : StatementSyntax(SyntaxKind::IfStatement),
        ifkeyword(_ifkeyword),
        // openParenthesis(_openParenthesis),
        condition(_condition),
        // closeParenthesis(_closeParenthesis),
        thenstatement(_thenstatement),
        elseClause(_elseClause) {}
  stdtoken ifkeyword;
  // stdtoken openParenthesis;
  // stdtoken closeParenthesis;
  stdexp condition;
  std::shared_ptr<ElseClauseSyntax> elseClause;
  stdstate thenstatement;
};
}  // namespace Compiler