#pragma once
#include "SyntaxNode.h"
#include <vector>
namespace Compiler {
template <typename T> class SeparatedSyntaxList {
  std::vector<std::shared_ptr<SyntaxNode>> separatorAndNodes;

public:
  SeparatedSyntaxList(
      std::vector<std::shared_ptr<SyntaxNode>> _separatorAndNodes)
      : separatorAndNodes(std::move(_separatorAndNodes)) {}
};

} // namespace Compiler
