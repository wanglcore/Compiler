#pragma once
#include <algorithm>
#include <memory>
#include <string>

#include "SourceText.h"
#include "SyntaxFacts.h"
#include "SyntaxToken.h"
namespace Compiler {
class Lexer {
 public:
  // Lexer(std::string _text) : text(_text) { length = text.length(); }
  Lexer(std::shared_ptr<SourceText> _text)
      : text(_text), length(_text->length) {}
  inline char Current() { return Peek(0); }
  inline char LookHead() { return Peek(1); }
  inline char Peek(int offset) {
    int index = position + offset;
    // return index >= length ? '\0' : text[index];
    return index >= length ? '\0' : text->GetChar(index);
  }
  inline void Next() { ++position; }
  std::shared_ptr<SyntaxToken> NextToken();

 private:
  // std::string text;
  std::shared_ptr<SourceText> text;
  int position{0};
  size_t length;
};
}  // namespace Compiler
