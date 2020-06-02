#pragma once
namespace Compiler {
class TextSpan {
 public:
  TextSpan(int _start, int _length)
      : start(_start), length(_length), end(_start + _length) {}
  int start{0};
  int length{0};
  int end{0};
};
}  // namespace Compiler