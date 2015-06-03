#include "boost/format.hpp"

#include "base/check.h"
#include "exception/error.h"
#include "symbol_table/symbol_info.h"

namespace flang {

RedefineSymbolError::RedefineSymbolError(
    SymbolInfo* existing_symbol, SymbolInfo* redefined_symbol) :
    existing_symbol_(existing_symbol),
    redefined_symbol_(redefined_symbol) {
  CHECK(existing_symbol);
  CHECK(redefined_symbol);
  message_ = boost::str(
      boost::format("Symbol %s has been defined.")
      % existing_symbol_->getName());
}

}  // namespace flang

