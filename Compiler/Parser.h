#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "AllExpressionSyntax.h"
#include "ConditionStatement.h"
#include "ExpressionSyntax.h"
#include "Lexer.h"
#include "SyntaxFacts.h"
#include "SyntaxToken.h"
#include "Type.h"
namespace Compiler {
class SyntaxTree;
class Parser {
 public:
  // Parser(std::string _text);
  Parser(std::shared_ptr<SourceText> _sourcetext);
  inline auto Peek(int offset) -> std::shared_ptr<SyntaxToken>;
  auto ParseCompilationUnit() -> std::shared_ptr<CompilationUnitSyntax>;
  auto ParseStatement() -> std::shared_ptr<StatementSyntax>;
  auto ParseMember() -> std::shared_ptr<MemberSyntax>;
  auto ParseFunctionDeclaration() -> std::shared_ptr<FunctionDeclaritionSyntax>;
  auto ParseParameters() -> std::vector<std::shared_ptr<ParameterSyntax>>;
  auto ParseParameter() -> std::shared_ptr<ParameterSyntax>;
  auto ParseGlobalStatement() -> std::shared_ptr<GlobalStatementSyntax>;
  auto ParseMembers() -> std::vector<std::shared_ptr<MemberSyntax>>;
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
  auto ParseWhileStatement() -> std::shared_ptr<StatementSyntax>;
  auto ParseForStatement() -> std::shared_ptr<StatementSyntax>;
  auto ParseElseStatement() -> std::shared_ptr<ElseClauseSyntax>;
  auto ParseArguments() -> std::vector<std::shared_ptr<ExpressionSyntax>>;
  auto ParseTypeClause() -> std::shared_ptr<SyntaxToken>;
  auto ParseDoWhileStatement() -> std::shared_ptr<StatementSyntax>;
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
