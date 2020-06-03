#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "BinaryExpressionSyntax.h"
#include "ConditionStatement.h"
#include "ExpressionSyntax.h"
#include "Lexer.h"
#include "NameAndAssignmentExpressionSyntax.h"
#include "ParenthesizedExpressionSyntax.h"
#include "SyntaxFacts.h"
#include "SyntaxToken.h"
#include "Type.h"
#include "UnaryExpressionSyntax.h"
#include "VariableDeclarationSyntax.h"
namespace Compiler {
class SyntaxTree;
class Parser {
 public:
  // Parser(std::string _text);
  Parser(std::shared_ptr<SourceText> _sourcetext);
  auto Peek(int offset) -> std::shared_ptr<SyntaxToken>;
  auto ParseCompilationUnit() -> std::shared_ptr<CompilationUnitSyntax>;
  auto ParseStatement() -> std::shared_ptr<StatementSyntax>;
  auto ParseBlockStatement() -> std::shared_ptr<StatementSyntax>;
  auto ParseExpressionStatement() -> std::shared_ptr<StatementSyntax>;
  // auto ParseTerm() -> std::shared_ptr<ExpressionSyntax>;
  // auto ParseFactor() -> std::shared_ptr<ExpressionSyntax>;
  // auto ParseExpression() -> std::shared_ptr<ExpressionSyntax>;
  auto ParsePrimaryExpression() -> std::shared_ptr<ExpressionSyntax>;
  auto ParseBinaryExpression(int) -> std::shared_ptr<ExpressionSyntax>;
  auto ParseExpression() -> std::shared_ptr<ExpressionSyntax>;
  auto ParseAssignmentExpression() -> std::shared_ptr<ExpressionSyntax>;
  auto ParseVariableDeclaration() -> std::shared_ptr<StatementSyntax>;
  auto ParseIfStatement() -> std::shared_ptr<StatementSyntax>;
  auto ParseElseStatement() -> std::shared_ptr<ElseClauseSyntax>;
  inline auto MatchToken(SyntaxKind _kind) -> std::shared_ptr<SyntaxToken> {
    if (Equals(Current()->Kind, _kind)) {
      return NextToken();
    }
    return nullptr;  // error code
  }
  inline auto Current() -> std::shared_ptr<SyntaxToken> { return Peek(0); }
  inline auto NextToken() -> std::shared_ptr<SyntaxToken> {
    auto cur = Current();
    ++position;
    return cur;
  }

 private:
  inline auto Equals(SyntaxKind type1, SyntaxKind type2) -> bool {
    return type1 == type2;
  }
  std::vector<std::shared_ptr<SyntaxToken>> tokens;
  size_t tokens_length{0};
  int position{0};
};
}  // namespace Compiler
