#ifndef FUNCTION_ENTRY_H_
#define FUNCTION_ENTRY_H_

#include <vector>
#include <string>

#include "symbol_table/data_type_entry.h"

namespace flang {

class FunctionEntry {
 public:
  FunctionEntry() {}
  std::string toString() { return ""; }

 private:
  std::string name_;
  std::string qualifier_;
  DataTypeEntry return_type_;
  std::vector<DataTypeEntry*> parameters_;
};

}  // namespace flang

#endif
