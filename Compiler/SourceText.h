#pragma once
#include <memory>
#include <string>
#include <vector>
namespace Compiler {

class TextLine {
 public:
  TextLine(int _start, int _length, int _lengthIncludeingLineBreak)
      : start(_start),
        length(_length),
        lengthIncludeingLineBreak(_lengthIncludeingLineBreak),
        end(_start + _length) {}
  int start;
  int length;
  int lengthIncludeingLineBreak;
  int end;
};

class SourceText {
 public:
  SourceText(std::string _text) : text(_text), length(_text.length()) {
    lines = ParseLines(_text);
  }
  std::string text;
  size_t length;
  std::vector<std::shared_ptr<TextLine>> lines;
  static std::shared_ptr<SourceText> From(std::string _text) {
    return std::make_shared<SourceText>(_text);
  }
  inline char GetChar(int position)
  {
      return text[position];
  }
  std::string SubString(int start, int length)
  { return text.substr(start,length);
  }
  //inline char& operator[](int position)noexcept { return text[position]; }
  int GetLineIndex(int position) {
    int lower = 0;
    int upper = lines.size() - 1;
    while (lower <= upper) {
      auto index = lower + (upper - lower) / 2;
      auto start = lines[index]->start;
      if (position == start) {
        return index;
      }
      if (start > position) {
        upper = index - 1;
      } else {
        lower = index + 1;
      }
    }
    return lower - 1;
  }
  static std::vector<std::shared_ptr<TextLine>> ParseLines(std::string text) {
    std::vector<std::shared_ptr<TextLine>> _lines;
    int linestart = 0;
    int position = 0;
    int _length = text.length();
    while (position < _length) {
      auto linebreakwidth = GetLineBreakWidth(text, position);
      if (linebreakwidth == 0) {
        position++;
      } else {
        int linelength = position - linestart;
        int linebreaklength = linelength + linebreakwidth;
        _lines.push_back(
            std::make_shared<TextLine>(linestart, linelength, linebreaklength));
        position += linebreakwidth;
        linestart = position;
      }
      if (position >= linestart) {
        _lines.push_back(std::make_shared<TextLine>(position, linestart, 0));
      }
    }
    return _lines;
  }
  static int GetLineBreakWidth(std::string text, int i) {
    char c = text[i];
    char l = (i + 1 >= text.length()) ? '\0' : text[i + 1];
    if (c == '\r' && l == '\n') {
      return 2;
    }
    if (c == '\r' || c == '\n') {
      return 1;
    }
    return 0;
  }
};
}  // namespace Compiler