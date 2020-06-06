#pragma once
#include <string>
#include <vector>

#include "MemberSyntax.h"
#include "Type.h"
namespace Compiler {
class Symbol {
 public:
  Symbol() {}
  Symbol(std::string _name, SymbolKind _kind) : name(_name), kind(_kind) {}
  std::string name;
  SymbolKind kind;
};

// class TypeSymbol final : public Symbol {
//  public:
//   TypeSymbol(std::string _name) : Symbol(_name, SymbolKind::Type) {}
// };
// static bool operator!=(TypeSymbol t1, TypeSymbol t2) {
//   return t1.name != t2.name;
// }
// static bool operator==(TypeSymbol t1, TypeSymbol t2) {
//   return t1.name == t2.name;
// }
// namespace BaseType {
// static std::shared_ptr<TypeSymbol> Int("int");
// static std::shared_ptr<TypeSymbol> Bool("bool");
// static std::shared_ptr<TypeSymbol> String("string");
// static std::shared_ptr<TypeSymbol> Error("error");
// static std::shared_ptr<TypeSymbol> Default("null");
// static std::shared_ptr<TypeSymbol> Void("void");
// }  // namespace BaseType
struct VariableSymbol : public Symbol {
  BuildinType type;
  bool isReadlyOnly{true};
  VariableSymbol(std::string _name, BuildinType _type)
      : Symbol(_name, SymbolKind::Variable), type(_type), isReadlyOnly(true) {}
  VariableSymbol(std::string _name, BuildinType _type, bool _readonly)
      : Symbol(_name, SymbolKind::Variable),
        type(_type),
        isReadlyOnly(_readonly) {}
  VariableSymbol(std::string _name, BuildinType _type, bool _readonly,
                 SymbolKind _kind)
      : Symbol(_name, _kind), type(_type), isReadlyOnly(_readonly) {}
  VariableSymbol()
      : Symbol("", SymbolKind::Variable),
        type(BuildinType::Default),
        isReadlyOnly(true) {}
};
static bool operator<(const VariableSymbol &v1, const VariableSymbol &v2) {
  return v1.name < v2.name;
}

class ParameterSymbol final : public VariableSymbol {
 public:
  ParameterSymbol(std::string _name, BuildinType _type)
      : VariableSymbol(_name, _type, true, SymbolKind::Parameter),
        type(_type) {}
  BuildinType type;
};

class FunctionSymbol final : public Symbol {
 public:
  FunctionSymbol(std::string _name, std::vector<ParameterSymbol> _parameters,
                 BuildinType _type,
                 std::shared_ptr<FunctionDeclaritionSyntax> _declaration)
      : Symbol(_name, SymbolKind::Function),
        parameters(std::move(_parameters)),
        type(_type),
        declaration(_declaration) {}
  FunctionSymbol() : FunctionSymbol("", {}, BuildinType::Void, nullptr) {}
  std::vector<ParameterSymbol> parameters;
  BuildinType type;
  std::shared_ptr<FunctionDeclaritionSyntax> declaration;
};
static bool operator<(const FunctionSymbol &v1, const FunctionSymbol &v2) {
  return v1.name < v2.name;
}
// namespace BaseType
}  // namespace Compiler
