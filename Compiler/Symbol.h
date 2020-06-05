#pragma once
#include <string>
#include <vector>

#include "Type.h"
namespace Compiler {
class Symbol {
 public:
  Symbol() {}
  Symbol(std::string _name, SymbolKind _kind) : name(_name), kind(_kind) {}
  std::string name;
  SymbolKind kind;
};

class TypeSymbol final : public Symbol {
 public:
  TypeSymbol(std::string _name) : Symbol(_name, SymbolKind::Type) {}
};
static bool operator!=(TypeSymbol t1, TypeSymbol t2) {
  return t1.name != t2.name;
}
static bool operator==(TypeSymbol t1, TypeSymbol t2) {
  return t1.name == t2.name;
}
namespace BaseType {
static TypeSymbol Int("int");
static TypeSymbol Bool("bool");
static TypeSymbol String("string");
static TypeSymbol Error("error");
static TypeSymbol Default("null");
static TypeSymbol Void("void");
}  // namespace BaseType
struct VariableSymbol : public Symbol {
  TypeSymbol type;
  bool isReadlyOnly{true};
  VariableSymbol(std::string _name, TypeSymbol _type)
      : Symbol(_name, SymbolKind::Variable), type(_type), isReadlyOnly(true) {}
  VariableSymbol(std::string _name, TypeSymbol _type, bool _readonly)
      : Symbol(_name, SymbolKind::Variable),
        type(_type),
        isReadlyOnly(_readonly) {}
  VariableSymbol(std::string _name, TypeSymbol _type, bool _readonly,
                 SymbolKind _kind)
      : Symbol(_name, _kind), type(_type), isReadlyOnly(_readonly) {}
  VariableSymbol()
      : Symbol("", SymbolKind::Variable),
        type(BaseType::Default),
        isReadlyOnly(true) {}
};
static bool operator<(const VariableSymbol &v1, const VariableSymbol &v2) {
  return v1.name < v2.name;
}

class ParameterSymbol final : public VariableSymbol {
 public:
  ParameterSymbol(std::string _name, TypeSymbol _type)
      : VariableSymbol(_name, _type, true, SymbolKind::Parameter),
        type(_type) {}
  TypeSymbol type;
};

class FunctionSymbol final : public Symbol {
 public:
  FunctionSymbol(std::string _name, std::vector<ParameterSymbol> _parameters,
                 TypeSymbol _type)
      : Symbol(_name, SymbolKind::Function),
        parameters(std::move(_parameters)),
        type(_type) {}
  FunctionSymbol() : FunctionSymbol("", {}, BaseType::Void) {}
  std::vector<ParameterSymbol> parameters;
  TypeSymbol type;
};

// namespace BaseType
}  // namespace Compiler
