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
  stdstate thenstatement;
  std::shared_ptr<ElseClauseSyntax> elseClause;
};
class WhileStatementSyntax final : public StatementSyntax {
 public:
  WhileStatementSyntax(stdtoken _whileKeyword, stdexp _condition,
                       stdstate _statement)
      : StatementSyntax(SyntaxKind::WhileStatement),
        whilekeyword(_whileKeyword),
        // openParenthesis(_openParenthesis),
        condition(_condition),
        statement(_statement) {}
  // closeParenthesis(_closeParenthesis),
  stdtoken whilekeyword;
  // stdtoken openParenthesis;
  // stdtoken closeParenthesis;
  stdexp condition;
  stdstate statement;
};
class DoWhileStatementSyntax final : public StatementSyntax {
 public:
  DoWhileStatementSyntax(stdtoken _dokeyword, stdstate _statement,
                         stdtoken _whileKeyword, stdexp _condition)
      : StatementSyntax(SyntaxKind::DoWhileStatemnt),
        dokeyword(_dokeyword),
        statement(_statement),
        whilekeyword(_whileKeyword),
        // openParenthesis(_openParenthesis),
        condition(_condition) {}
  // closeParenthesis(_closeParenthesis),
  stdtoken whilekeyword;
  stdtoken dokeyword;
  // stdtoken openParenthesis;
  // stdtoken closeParenthesis;
  stdexp condition;
  stdstate statement;
};
class ForStatementSyntax final : public StatementSyntax {
 public:
  ForStatementSyntax(stdtoken _forKeyword, stdtoken _identifier,
                     stdtoken _inToken, stdexp _iterbegin, stdexp _iterend,
                     stdexp _iterstep, stdstate _statement)
      : StatementSyntax(SyntaxKind::ForStatement),
        forkeyword(_forKeyword),
        identifier(_identifier),
        inToken(_inToken),
        iterbegin(_iterbegin),
        iterend(_iterend),
        iterstep(_iterstep),
        // openParenthesis(_openParenthesis),
        statement(_statement) {}
  // closeParenthesis(_closeParenthesis),
  stdtoken forkeyword;
  stdtoken identifier;
  stdtoken inToken;
  stdexp iterbegin, iterend, iterstep;
  // stdtoken openParenthesis;
  // stdtoken closeParenthesis;
  stdexp condition;
  stdstate statement;
};
}  // namespace Compiler