#pragma once
#include <memory>
#include <vector>

#include "SyntaxNode.h"
#include "SyntaxToken.h"
#include "ExpressionSyntax.h"
#include "Type.h"
namespace Compiler {
class StatementSyntax : public SyntaxNode {
 public:
  StatementSyntax(SyntaxKind kind) : SyntaxNode(kind) {}
  /*
  virtual bool EqualsKind(SyntaxKind other) {
    return SyntaxNode::Kind == other;
  }
  virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
  GetChildren() const {
    co_yield nullptr;
  };
  virtual NodeKind GetNodeKind() { return NodeKind::ExpressionSyntaxNode; }
  virtual size_t GetMemberLength() const { return 0; }
*/
  virtual ~StatementSyntax() {}
};

class BlockStatementSyntax final : public StatementSyntax {
 public:
  BlockStatementSyntax(
      std::shared_ptr<SyntaxToken> _openBraceToken,
      std::vector<std::shared_ptr<StatementSyntax>> _statements,
      std::shared_ptr<SyntaxToken> _closeBraceToken)
      : StatementSyntax(SyntaxKind::BlockStatement),
        openBraceToken(_openBraceToken),
        statements(_statements),
        closeBraceToken(_closeBraceToken) {}

  std::shared_ptr<SyntaxToken> openBraceToken;
  std::vector<std::shared_ptr<StatementSyntax>> statements;
  std::shared_ptr<SyntaxToken> closeBraceToken;
  /*
    virtual bool EqualsKind(SyntaxKind other) {
      return SyntaxNode::Kind == other;
    }
    virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
    GetChildren() const {
      co_yield nullptr;
    };
    virtual NodeKind GetNodeKind() { return NodeKind::BlockStatementNode; }
    virtual size_t GetMemberLength() const { return 0; }
    */
};
class ExpressionStatementSyntax final : public StatementSyntax {
 public:
  ExpressionStatementSyntax(std::shared_ptr<ExpressionSyntax> _expression)
      : StatementSyntax(SyntaxKind::ExpressionStatement),
        expression(_expression) {}

  std::shared_ptr<ExpressionSyntax> expression;
  /*
    virtual bool EqualsKind(SyntaxKind other) {
      return SyntaxNode::Kind == other;
    }
    virtual std::experimental::generator<std::shared_ptr<SyntaxNode>>
    GetChildren() const {
      co_yield nullptr;
    };
    virtual NodeKind GetNodeKind() { return NodeKind::ExpressionStatementNode; }
    virtual size_t GetMemberLength() const { return 0; }
    */
};
class VariableDeclarationSyntax final : public StatementSyntax {
 public:
  VariableDeclarationSyntax(std::shared_ptr<SyntaxToken> _keyword,
                            std::shared_ptr<SyntaxToken> _mutkeyword,
                            std::shared_ptr<SyntaxToken> _identifier,
                            std::shared_ptr<SyntaxToken> _type,
                            std::shared_ptr<SyntaxToken> _equalsToken,
                            std::shared_ptr<ExpressionSyntax> _initializer)
      : StatementSyntax(SyntaxKind::VariableDeclaration),
        keyword(_keyword),
        mutkeyword(_mutkeyword),
        identifier(_identifier),
        type(_type),
        equalsToken(_equalsToken),
        initializer(_initializer) {}
  // VariableDeclarationSyntax(std::shared_ptr<SyntaxToken> _keyword,
  //                          std::shared_ptr<SyntaxToken> _identifier,
  //                          std::shared_ptr<SyntaxToken> _type,
  //                          std::shared_ptr<SyntaxToken> _equalsToken,
  //                          std::shared_ptr<ExpressionSyntax> _initializer)
  //    : VariableDeclarationSyntax(_keyword, nullptr, _identifier, _type,
  //                                _equalsToken, _initializer) {}
  // VariableDeclarationSyntax(std::shared_ptr<SyntaxToken> _keyword,
  //                          std::shared_ptr<SyntaxToken> _mutkeyword,
  //                          std::shared_ptr<SyntaxToken> _identifier,
  //                          std::shared_ptr<SyntaxToken> _equalsToken,
  //                          std::shared_ptr<ExpressionSyntax> _initializer)
  //    : VariableDeclarationSyntax(_keyword, _mutkeyword, _identifier, nullptr,
  //                                _equalsToken, _initializer) {}
  // VariableDeclarationSyntax(std::shared_ptr<SyntaxToken> _keyword,
  //                          std::shared_ptr<SyntaxToken> _identifier,
  //                          std::shared_ptr<SyntaxToken> _equalsToken,
  //                          std::shared_ptr<ExpressionSyntax> _initializer)
  //    : VariableDeclarationSyntax(_keyword, nullptr, _identifier, nullptr,
  //                                _equalsToken, _initializer) {}

  std::shared_ptr<SyntaxToken> keyword;
  std::shared_ptr<SyntaxToken> mutkeyword;
  std::shared_ptr<SyntaxToken> identifier;
  std::shared_ptr<SyntaxToken> type;
  std::shared_ptr<SyntaxToken> equalsToken;
  std::shared_ptr<ExpressionSyntax> initializer;
};
}  // namespace Compiler
