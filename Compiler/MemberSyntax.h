#pragma once
#include <memory>

#include "SyntaxNode.h"
#include "SyntaxToken.h"
#include "Statement.h"
namespace Compiler {
class MemberSyntax : public SyntaxNode {
 public:
  MemberSyntax(SyntaxKind kind) : SyntaxNode(kind) {}
  virtual ~MemberSyntax() {}
};
// class TypeClauseSyntax final : public SyntaxNode {
// public:
//   TypeClauseSyntax(std::shared_ptr<SyntaxToken> _colonToken,
//                    std::shared_ptr<SyntaxToken> _identifier)
//       : SyntaxNode(SyntaxKind::TypeClause), colonToken(_colonToken),
//         identifier(_identifier) {}
//   std::shared_ptr<SyntaxToken> colonToken;
//   std::shared_ptr<SyntaxToken> identifier;
// };
class GlobalStatementSyntax final : public MemberSyntax {
 public:
  GlobalStatementSyntax(std::shared_ptr<StatementSyntax> _statement)
      : MemberSyntax(SyntaxKind::GlobalStatement), statement(_statement) {}
  std::shared_ptr<StatementSyntax> statement;
};
class ParameterSyntax final : public SyntaxNode {
 public:
  ParameterSyntax(std::shared_ptr<SyntaxToken> _identifier,
                  std::shared_ptr<SyntaxToken> _type)
      : SyntaxNode(SyntaxKind::Parameters),
        identifier(_identifier),
        type(_type) {}
  std::shared_ptr<SyntaxToken> identifier;
  std::shared_ptr<SyntaxToken> type;
};
class FunctionDeclaritionSyntax final : public MemberSyntax {
 public:
  FunctionDeclaritionSyntax(
      std::shared_ptr<SyntaxToken> _defkeyword,
      std::shared_ptr<SyntaxToken> _identifier,
      std::shared_ptr<SyntaxToken> _openbrace,
      std::vector<std::shared_ptr<ParameterSyntax>> _parameters,
      std::shared_ptr<SyntaxToken> _closebrace,
      std::shared_ptr<SyntaxToken> _type,
      std::shared_ptr<StatementSyntax> _statement)
      : MemberSyntax(SyntaxKind::FunctionDeclarition),
        defkeyword(_defkeyword),
        identifier(_identifier),
        openbrace(_openbrace),
        parameters(std::move(_parameters)),
        closebrace(_closebrace),
        type(_type),
        statement(_statement) {}
  std::shared_ptr<SyntaxToken> defkeyword;
  std::shared_ptr<SyntaxToken> identifier;
  std::shared_ptr<SyntaxToken> openbrace;
  std::shared_ptr<SyntaxToken> closebrace;
  std::vector<std::shared_ptr<ParameterSyntax>> parameters;
  std::shared_ptr<SyntaxToken> type;
  std::shared_ptr<StatementSyntax> statement;
};
}  // namespace Compiler
