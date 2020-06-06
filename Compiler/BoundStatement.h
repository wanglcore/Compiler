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
      : BoundStatement(BoundNodeKind::BlockStatement), statements(_statements) {
  }
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
class BoundVariableDeclaration final : public BoundStatement {
public:
  BoundVariableDeclaration(VariableSymbol _variable,
                           std::shared_ptr<BoundExpression> _initializer)
      : BoundStatement(BoundNodeKind::VariableDeclaration), variable(_variable),
        initializer(_initializer) {}
  VariableSymbol variable;
  std::shared_ptr<BoundExpression> initializer;
};

class BoundIfStatement final : public BoundStatement {
public:
  BoundIfStatement(std::shared_ptr<BoundExpression> _condition,
                   std::shared_ptr<BoundStatement> _thenstatement,
                   std::shared_ptr<BoundStatement> _elsestatement)
      : BoundStatement(BoundNodeKind::IfStatement),
        thenstatement(_thenstatement), elsestatement(_elsestatement),
        condition(_condition) {}
  std::shared_ptr<BoundStatement> thenstatement, elsestatement;
  std::shared_ptr<BoundExpression> condition;
};
class BoundWhileStatement final : public BoundStatement {
public:
  BoundWhileStatement(std::shared_ptr<BoundExpression> _condition,
                      std::shared_ptr<BoundStatement> _statement)
      : BoundStatement(BoundNodeKind::WhileStatement), statement(_statement),
        condition(_condition) {}
  std::shared_ptr<BoundStatement> statement;
  std::shared_ptr<BoundExpression> condition;
};
class BoundDoWhileStatement final : public BoundStatement {
 public:
  BoundDoWhileStatement(std::shared_ptr<BoundExpression> _condition,
                      std::shared_ptr<BoundStatement> _statement)
      : BoundStatement(BoundNodeKind::DoWhileStatement),
        statement(_statement),
        condition(_condition) {}
  std::shared_ptr<BoundStatement> statement;
  std::shared_ptr<BoundExpression> condition;
};
class BoundForStatement final : public BoundStatement {
public:
  BoundForStatement(VariableSymbol _variable,
                    std::shared_ptr<BoundExpression> _iterbegin,
                    std::shared_ptr<BoundExpression> _iterend,
                    std::shared_ptr<BoundExpression> _iterstep,
                    std::shared_ptr<BoundStatement> _statement)
      : BoundStatement(BoundNodeKind::ForStatement), variable(_variable),
        iterbegin(_iterbegin), iterend(_iterend), iterstep(_iterstep),
        statement(_statement) {}
  VariableSymbol variable;
  std::shared_ptr<BoundExpression> iterbegin, iterend, iterstep;
  std::shared_ptr<BoundStatement> statement;
};
class BoundLabelStatement final : public BoundStatement {
public:
  BoundLabelStatement(BoundLabel _label)
      : BoundStatement(BoundNodeKind::LabelStatement), label(_label) {}
  BoundLabel label;
};
class BoundGotoStatement final : public BoundStatement {
public:
  BoundGotoStatement(BoundLabel _label)
      : BoundStatement(BoundNodeKind::GotoStatement), label(_label) {}
  BoundLabel label;
};

class BoundConditionalGotoStatement final : public BoundStatement {
public:
  BoundConditionalGotoStatement(BoundLabel _label,
                                std::shared_ptr<BoundExpression> _condition,
                                bool _jumpifTrue = true)
      : BoundStatement(BoundNodeKind::ConditionalGotoStatement), label(_label),
        condition(_condition), jumpifTrue(_jumpifTrue) {}
  BoundLabel label;
  std::shared_ptr<BoundExpression> condition;
  bool jumpifTrue;
};
} // namespace Compiler
