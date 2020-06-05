#pragma once
#include "Statement.h"
#include "SyntaxNode.h"
#include <memory>
namespace Compiler {
class MemberSyntax : public SyntaxNode {
public:
  MemberSyntax(SyntaxKind kind) : SyntaxNode(kind) {}
  virtual ~MemberSyntax() {}
};
class GlobalStatementSyntax final : public MemberSyntax {
public:
  GlobalStatementSyntax(std::shared_ptr<StatementSyntax> _statement)
      : MemberSyntax(SyntaxKind::GlobalStatement), statement(_statement) {}
  std::shared_ptr<StatementSyntax> statement;
};
class FunctionDeclaritionSyntax final : public MemberSyntax {
public:
  FunctionDeclaritionSyntax(
      std::shared_ptr<SyntaxToken> _defkeyword,
      std::shared_ptr<SyntaxToken> _identifier,
      std::shared_ptr<SyntaxToken> _openbrace,
      std::vector<std::shared_ptr<ExpressionSyntax>> _arguments,
      std::shared_ptr<SyntaxToken> _closebrace)
      : MemberSyntax(SyntaxKind::FunctionDeclarition), defkeyword(_defkeyword),
        identifier(_identifier), openbrace(_openbrace),
        arguments(std::move(_arguments)), closebrace(_closebrace) {}
  std::shared_ptr<SyntaxToken> defkeyword;
  std::shared_ptr<SyntaxToken> identifier;
  std::shared_ptr<SyntaxToken> openbrace;
  std::shared_ptr<SyntaxToken> closebrace;
  std::vector<std::shared_ptr<ExpressionSyntax>> arguments;
};
} // namespace Compiler
