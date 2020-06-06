#include "Evaluator.h"
namespace Compiler {
Object Compiler::Evaluator::Evaluate() {
  EvaluateStatement(program->statement->statement);
  return lastValue;
}

void Evaluator::EvaluateStatement(std::shared_ptr<BoundStatement> statement) {
  switch (statement->Kind) {
    case BoundNodeKind::BlockStatement:
      EvaluateBlockStatement(
          std::dynamic_pointer_cast<BoundBlockStatement>(statement));
      break;
    case BoundNodeKind::VariableDeclaration:
      EvaluateVariableDeclaration(
          std::dynamic_pointer_cast<BoundVariableDeclaration>(statement));
      break;
    case BoundNodeKind::IfStatement:
      EvaluateIfStatement(
          std::dynamic_pointer_cast<BoundIfStatement>(statement));
      break;
    case BoundNodeKind::ExpressionStatement:
      EvaluateExpressionStatement(
          std::dynamic_pointer_cast<BoundExpressionStatement>(statement));
      break;
    case BoundNodeKind::WhileStatement:
      EvaluateWhileStatement(
          std::dynamic_pointer_cast<BoundWhileStatement>(statement));
      break;
    case BoundNodeKind::DoWhileStatement:
      EvaluateDoWhileStatement(
          std::dynamic_pointer_cast<BoundDoWhileStatement>(statement));
    case BoundNodeKind::ForStatement:
      EvaluateForStatement(
          std::dynamic_pointer_cast<BoundForStatement>(statement));
      break;
    default:
      break;
  }
}

void Evaluator::EvaluateBlockStatement(
    std::shared_ptr<BoundBlockStatement> statement) {
  for (auto u : statement->statements) {
    EvaluateStatement(u);
  }
}

void Evaluator::EvaluateIfStatement(
    std::shared_ptr<BoundIfStatement> statement) {
  auto value = EvaluateExpression(statement->condition);
  auto condition = std::get<bool>(value);
  if (condition) {
    EvaluateStatement(statement->thenstatement);
  } else if (statement->elsestatement != nullptr) {
    EvaluateStatement(statement->elsestatement);
  }
}

void Evaluator::EvaluateWhileStatement(
    std::shared_ptr<BoundWhileStatement> statement) {
  while (std::get<bool>(EvaluateExpression(statement->condition))) {
    EvaluateStatement(statement->statement);
  }
}

void Evaluator::EvaluateDoWhileStatement(
    std::shared_ptr<BoundDoWhileStatement> statement) {
  do {
    EvaluateStatement(statement->statement);
  } while (std::get<bool>(EvaluateExpression(statement->condition)));
}

void Evaluator::EvaluateForStatement(
    std::shared_ptr<BoundForStatement> statement) {
  auto iterbegin = std::get<int>(EvaluateExpression(statement->iterbegin));
  auto iterend = std::get<int>(EvaluateExpression(statement->iterend));
  auto iterstep = std::get<int>(EvaluateExpression(statement->iterstep));
  if (iterstep == 0) {
    if (iterbegin < iterend) {
      iterstep = 1;
    } else {
      iterstep = -1;
    }
  }
  if (iterbegin < iterend) {
    for (int i = iterbegin; i < iterend; i += iterstep) {
      variables[statement->variable] = i;
      EvaluateStatement(statement->statement);
    }
  } else {
    for (int i = iterbegin; i > iterend; i += iterstep) {
      variables[statement->variable] = i;
      EvaluateStatement(statement->statement);
    }
  }
}
Object Evaluator::EvaluateCallExpression(
    std::shared_ptr<BoundCallExpression> statement) {
  std::map<VariableSymbol, Object> _locals;
  for (int i = 0; i < statement->arguments.size(); ++i) {
    auto parameter = statement->function.parameters[i];
    auto value = EvaluateExpression(statement->arguments[i]);
    _locals[parameter] = value;
  }
  locals.push(_locals);
  auto _statement = functionBodys[statement->function];
  EvaluateStatement(_statement);
  return lastValue;
}

void Evaluator::EvaluateVariableDeclaration(
    std::shared_ptr<BoundVariableDeclaration> statement) {
  auto value = EvaluateExpression(statement->initializer);
  variables[statement->variable] = value;
  lastValue = value;
}

void Evaluator::EvaluateExpressionStatement(
    std::shared_ptr<BoundExpressionStatement> statement) {
  lastValue = EvaluateExpression(statement->expression);
}

Object Compiler::Evaluator::EvaluateExpression(
    std::shared_ptr<BoundExpression> _root) {
  if (_root == nullptr) {  //当对象为空时返回0值
    return 0;
  }
  if (_root->EqualsKind(BoundNodeKind::LiteralExpression)) {
    auto literalExpressionSyntax =
        std::dynamic_pointer_cast<BoundLiteralExpression>(_root);
    return literalExpressionSyntax->value;
  }
  if (_root->EqualsKind(BoundNodeKind::UnaryExpression)) {
    auto unaryExpressionSyntax =
        std::dynamic_pointer_cast<BoundUnaryExpression>(_root);
    auto val = EvaluateExpression(unaryExpressionSyntax->operand);
    switch (unaryExpressionSyntax->op->kind) {
      case BoundUnaryOperatorKind::Identity:
        return -std::get<0>(val);
      case BoundUnaryOperatorKind::Negation:
        return std::get<0>(val);
      case BoundUnaryOperatorKind::LogicalNegation:
        return !std::get<1>(val);
      case BoundUnaryOperatorKind::OnesComplememt:
        return ~std::get<int>(val);
      default:
        return 0;
    }
  }
  // if(_root->EqualsKind(BoundNodeKind::))
  if (_root->EqualsKind(BoundNodeKind::VariableExpression)) {
    auto variable = std::dynamic_pointer_cast<BoundVariableExpression>(_root);
    // if (!locals.empty()) {
    //   auto _locals = locals.top();
    //   if (auto value = _locals.find(variable->symbol); value !=
    //   _locals.end()) {
    //     return value->second;
    //   }
    // }
    return variables[variable->symbol];
  } else if (_root->EqualsKind(BoundNodeKind::AssignmentExpression)) {
    auto assignment =
        std::dynamic_pointer_cast<BoundAssignmentExpression>(_root);
    auto value = EvaluateExpression(assignment->expression);

    variables[assignment->symbol] = value;
    // variables[assignment] = {value, static_cast<Type>(value.index())};
    return value;
  } else if (_root->EqualsKind(BoundNodeKind::BinaryExpression)) {
    auto binaryExpressionSyntax =
        std::dynamic_pointer_cast<BoundBinaryExpression>(_root);
    auto left = EvaluateExpression(binaryExpressionSyntax->left);
    auto right = EvaluateExpression(binaryExpressionSyntax->right);
    switch (binaryExpressionSyntax->op->kind) {
      case BoundBinaryOperatorKind::Addition:
        if (left.index() == 2 && right.index() == 2) {
          return std::get<std::string>(left) + std::get<std::string>(right);
        }
        return std::get<0>(left) + std::get<0>(right);
      case BoundBinaryOperatorKind::Subtraction:
        return std::get<0>(left) - std::get<0>(right);
      case BoundBinaryOperatorKind::Multiplication:
        return std::get<0>(left) * std::get<0>(right);
      case BoundBinaryOperatorKind::Division:
        return std::get<0>(left) / std::get<0>(right);
      case BoundBinaryOperatorKind::Less:
        return std::get<0>(left) < std::get<0>(right);
      case BoundBinaryOperatorKind::LessOrEqual:
        return std::get<0>(left) <= std::get<0>(right);
      case BoundBinaryOperatorKind::Greater:
        return std::get<0>(left) > std::get<0>(right);
      case BoundBinaryOperatorKind::GreaterOrEqual:
        return std::get<0>(left) >= std::get<0>(right);
      case BoundBinaryOperatorKind::LogicalAnd:
        return std::get<1>(left) && std::get<1>(right);
      case BoundBinaryOperatorKind::LogicalOr:
        return std::get<1>(left) || std::get<1>(right);
      case BoundBinaryOperatorKind::Equsls:
        return left == right;
      case BoundBinaryOperatorKind::NotEquals:
        return left != right;
      case BoundBinaryOperatorKind::BitWiseAnd:
        if (left.index() == 1 && right.index() == 1) {
          return std::get<1>(left) & std::get<1>(right);
        } else {
          return std::get<0>(left) & std::get<0>(right);
        }
      case BoundBinaryOperatorKind::BitWiseOr:
        if (left.index() == 1 && right.index() == 1) {
          return std::get<1>(left) | std::get<1>(right);
        } else {
          return std::get<0>(left) | std::get<0>(right);
        }
      case BoundBinaryOperatorKind::BitWiseXor:
        if (left.index() == 1 && right.index() == 1) {
          return std::get<1>(left) ^ std::get<1>(right);
        } else {
          return std::get<0>(left) ^ std::get<0>(right);
        }
    }
    if (binaryExpressionSyntax->op->kind ==
        BoundBinaryOperatorKind::AdditionEqual) {
      auto variable = std::dynamic_pointer_cast<BoundVariableExpression>(
          binaryExpressionSyntax->left);
      auto iter = variables.find(variable->symbol);
      iter->second = (std::get<int>(iter->second) + std::get<int>(right));
      return iter->second;
    }
    if (binaryExpressionSyntax->op->kind ==
        BoundBinaryOperatorKind::SubtractionEqual) {
      auto variable = std::dynamic_pointer_cast<BoundVariableExpression>(
          binaryExpressionSyntax->left);
      auto iter = variables.find(variable->symbol);
      iter->second = (std::get<int>(iter->second) - std::get<int>(right));
      return iter->second;
    }
  } else if (_root->EqualsKind(BoundNodeKind::CallExpression)) {
    return EvaluateCallExpression(
        std::dynamic_pointer_cast<BoundCallExpression>(_root));
  } else if (_root->EqualsKind(BoundNodeKind::ConversionExpression)) {
    return EvaluateConversionExpression(
        std::dynamic_pointer_cast<BoundConversionExpression>(_root));
  }
  /* if (Equals(_root->Kind, BoundNodeKind::UnaryExpression)) {
     auto parenthesizedExpression =
         std::dynamic_pointer_cast<ParenthesizedExpressionSyntax>(_root);
     return EvaluateExpression(parenthesizedExpression->expression);
   }*/
  return 0;
}
}  // namespace Compiler
