#ifndef ERROR_H
#define ERROR_H

#include "exception/exception.h"

namespace flang {

class SymbolInfo;

class RedefineSymbolError : public Error {
 public:
  RedefineSymbolError(
      SymbolInfo* existing_symbol, SymbolInfo* redefined_symbol);

 private:
  SymbolInfo* existing_symbol_;
  SymbolInfo* redefined_symbol_;
};

}  // namespace flang

#endif
