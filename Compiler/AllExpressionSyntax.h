#pragma once

#include "ExpressionSyntax.h"
#include "Symbol.h"
#include "SyntaxToken.h"
#include "Type.h"
#include <memory>
#include <vector>
namespace Compiler {
class BinaryExpressionSyntax final : public ExpressionSyntax {
public:
  BinaryExpressionSyntax(std::shared_ptr<ExpressionSyntax> _left,
                         std::shared_ptr<SyntaxToken> _op,
                         std::shared_ptr<ExpressionSyntax> _right)
      : ExpressionSyntax(SyntaxKind::BinaryExpression), left(_left),
        right(_right), op(_op) {}
  std::shared_ptr<ExpressionSyntax> left, right;
  std::shared_ptr<SyntaxToken> op; //²Ù×÷·û
  /*
    bool EqualsKind(SyntaxKind other) override {
      return ExpressionSyntax::Kind == other;
    }
     size_t GetMemberLength() const override { return 3; }

    std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()const
        override {
      co_yield left;
      co_yield op;
      co_yield right;
    }
    NodeKind GetNodeKind() override {
      return NodeKind::BinaryExpressionSyntaxNode;
    }
    */
};

class CallExpressionSyntax final : public ExpressionSyntax {
public:
  CallExpressionSyntax(
      std::shared_ptr<SyntaxToken> _identifier,
      std::shared_ptr<SyntaxToken> _openbrace,
      std::vector<std::shared_ptr<ExpressionSyntax>> _arguments,
      std::shared_ptr<SyntaxToken> _closebrace)
      : ExpressionSyntax(SyntaxKind::CallExpression), identifier(_identifier),
        openbrace(_openbrace), arguments(std::move(_arguments)),
        closebrace(_closebrace) {}
  std::shared_ptr<SyntaxToken> identifier;
  std::shared_ptr<SyntaxToken> openbrace;
  std::shared_ptr<SyntaxToken> closebrace;
  std::vector<std::shared_ptr<ExpressionSyntax>> arguments;
};

class LiteralExpressionSyntax final : public ExpressionSyntax {
public:
  LiteralExpressionSyntax(std::shared_ptr<SyntaxToken> _literalToken,
                          Object _value, TypeSymbol _type)
      : ExpressionSyntax(SyntaxKind::LiteralExpression),
        literalToken(_literalToken), value(_value), type(_type) {}
  LiteralExpressionSyntax(std::shared_ptr<SyntaxToken> _literalToken)
      : LiteralExpressionSyntax(_literalToken, _literalToken->value,
                                _literalToken->type) {}
  std::shared_ptr<SyntaxToken> literalToken;
  Object value;
  TypeSymbol type;

  /*
  bool EqualsKind(SyntaxKind other) override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield literalToken;
  }
  size_t GetMemberLength() const override { return 1; }

  NodeKind GetNodeKind() override {
    return NodeKind::LiteralExpressionSyntaxNode;
  }
  */
};

class NameExpressionSyntax final : public ExpressionSyntax {
public:
  NameExpressionSyntax(std::shared_ptr<SyntaxToken> _identifierToken)
      : ExpressionSyntax(SyntaxKind::NameExpression),
        identifierToken(_identifierToken) {}
  std::shared_ptr<SyntaxToken> identifierToken;
  /*
  bool EqualsKind(SyntaxKind other) override {
    return SyntaxNode::Kind == other;
  }
  std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
      const override {
    co_yield identifierToken;
  }
  size_t GetMemberLength() const override { return 1; }

  NodeKind GetNodeKind() override { return NodeKind::NameExpressionNode; }
  */
};

class AssignmentExpressionSyntax final : public ExpressionSyntax {
public:
  AssignmentExpressionSyntax(std::shared_ptr<SyntaxToken> _identifierToken,
                             std::shared_ptr<SyntaxToken> _equalsToken,
                             std::shared_ptr<ExpressionSyntax> _expression)
      : ExpressionSyntax(SyntaxKind::AssignmentExpression),
        identifierToken(_identifierToken), equalsToken(_equalsToken),
        expression(_expression) {}
  std::shared_ptr<SyntaxToken> identifierToken;
  std::shared_ptr<SyntaxToken> equalsToken;
  std::shared_ptr<ExpressionSyntax> expression;
  /*
    bool EqualsKind(SyntaxKind other) override {
      return SyntaxNode::Kind == other;
    }
    std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
        const override {
      co_yield identifierToken;
      co_yield equalsToken;
      co_yield expression;
    }
    size_t GetMemberLength() const override { return 3; }

    NodeKind GetNodeKind() override { return NodeKind::AssignmentExpressionNode;
    }
    */
};

class ParenthesizedExpressionSyntax final : public ExpressionSyntax {
public:
  ParenthesizedExpressionSyntax(
      std::shared_ptr<SyntaxToken> _openParenthesisToken,
      std::shared_ptr<ExpressionSyntax> _expression,
      std::shared_ptr<SyntaxToken> _closeParenthesisToken)
      : ExpressionSyntax(SyntaxKind::ParenthesizedExpression),
        openParenthesisToken(_openParenthesisToken),
        closeParenthesisToken(_closeParenthesisToken), expression(_expression) {
  }
  std::shared_ptr<SyntaxToken> openParenthesisToken, closeParenthesisToken;
  std::shared_ptr<ExpressionSyntax> expression;
  /*
    bool EqualsKind(SyntaxKind other)  override {
      return ExpressionSyntax::Kind == other;
    }
    std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()const
         override {
      co_yield openParenthesisToken;
      co_yield expression;
      co_yield closeParenthesisToken;
    }
    size_t GetMemberLength() const override { return 3; }

    NodeKind GetNodeKind()  override {
      return NodeKind::ParenthesizedExpressionSyntaxNode;
    }
    */
};
class UnaryExpressionSyntax final : public ExpressionSyntax {
public:
  UnaryExpressionSyntax(std::shared_ptr<SyntaxToken> _op,
                        std::shared_ptr<ExpressionSyntax> _operand)
      : ExpressionSyntax(SyntaxKind::UnaryExpression), op(_op),
        operand(_operand) {}
  std::shared_ptr<SyntaxToken> op;           //²Ù×÷·û
  std::shared_ptr<ExpressionSyntax> operand; //²Ù×÷Êý
  /*
    bool EqualsKind(SyntaxKind other) override {
      return ExpressionSyntax::Kind == other;
    }
    size_t GetMemberLength() const override { return 3; }

    std::experimental::generator<std::shared_ptr<SyntaxNode>> GetChildren()
        const override {
      co_yield op;
      co_yield operand;
    }
    NodeKind GetNodeKind() override {
      return NodeKind::BinaryExpressionSyntaxNode;
    }
    */
};
} // namespace Compiler
