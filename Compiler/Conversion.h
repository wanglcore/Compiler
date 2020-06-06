#pragma once
#include <string>

#include "Symbol.h"
namespace Compiler {
struct Conversion {
  Conversion(bool _exists, bool _isIdentity, bool _isImplicit)
      : existes(_exists),
        isIdentity(_isIdentity),
        isImplicit(_isImplicit),
        isEmplicit(_exists && !_isImplicit) {}
  bool existes, isIdentity, isImplicit, isEmplicit;
};
namespace Convert {
static Conversion None(false, false, false);
static Conversion Identity(true, true, true);
static Conversion Implicit(true, false, true);
static Conversion Explicit(true, false, false);
static Conversion Classify(BuildinType from, BuildinType to) {
  if (from == to) return Convert::Identity;
  if (from == BuildinType::Bool || from == BuildinType::Int) {
    if (to == BuildinType::String) return Convert::Explicit;
  }
  if (from == BuildinType::String) {
    if (to == BuildinType::Bool || to == BuildinType::Int)
      return Convert::Explicit;
  }
  return Convert::None;
}
}  // namespace Convert
// namespace Convert
}  // namespace Compiler
