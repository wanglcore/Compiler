
#include <fstream>
#include <iostream>
#include <string>

#include "Evaluator.h"
#include "SyntaxTree.h"
#include "Type.h"
using namespace Compiler;

void Print(std::shared_ptr<SyntaxNode>, std::string, bool);
std::experimental::generator<int> Fib(int i, int j) {
  for (int k = i; k < j; k++) {
    co_yield k;
  }
}
void WriteLine(Object value) {
  switch (value.index()) {
    case 0:
      std::cout << std::get<0>(value) << std::endl;
      break;
    case 1:
      std::cout << std::boolalpha << std::get<1>(value) << std::endl;
      break;
    default:
      break;
  }
}
std::string GetCode(std::string file) {
  std::ifstream ifs(file, std::ios::in);
  std::string code;
  std::string line;
  while (std::getline(ifs, line)) {
    line = line + '\n';
    code = code + line;
  }
  std::cout << code << std::endl;
  return code;
}
std::map<VariableSymbol, Object> variables;
int main() {
  std::string line;
  std::variant<int, nullptr_t> vars;
  vars = nullptr;
  std::shared_ptr<Compilation> previous = nullptr;
  std::string filename = "Text.txt";
  std::string code = GetCode(filename);
  auto expression = SyntaxTree::Parse(code);
  auto compliation = std::make_shared<Compilation>(expression);
  auto value = compliation->Evaluate(variables);
  WriteLine(value->value);

  /*while (true) {
    std::cout << ">> ";
    std::getline(std::cin, line);
    if (line.empty()) {
      continue;
    }
    auto expression = SyntaxTree::Parse(line);
    auto compliation = previous == nullptr
                           ? std::make_shared<Compilation>(expression)
                           : previous->ContinueWith(expression);
    auto value = compliation->Evaluate(variables);
    WriteLine(value->value);
    Print(expression->root->statement, "", false);
    previous = std::move(compliation);
  }*/
  return 0;
}

void Print(std::shared_ptr<SyntaxNode> node, std::string indent = "",
           bool isLast = false) {
  std::cout << indent;
  std::cout << (isLast ? "+---" : "|---");
  std::cout << node->Kind;
  if (node->GetNodeKind() == NodeKind::SyntaxTokenNode) {
    auto syntaxToken = std::dynamic_pointer_cast<SyntaxToken>(node);
    std::cout << " " << syntaxToken->text;
  }
  std::cout << std::endl;
  std::string nextindent = indent + (isLast ? "    " : "|   ");
  int len = node->GetMemberLength() - 1;
  for (auto child : node->GetChildren()) {
    if (len >= 0) {
      Print(child, nextindent, len == 0);
      len--;
    }
  }
  /*for (int i = node->GetMemberLength()-1; i >=0; --i,++childbegin)
  {
      Print(childbegin,indent,i==1);
  }*/
}