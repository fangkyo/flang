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

  void setReturnType(DataTypeEntry* return_type) {
    return_type_ = return_type;
  }
  DataTypeEntry* getReturnType() { return return_type_; }

  void addParameter(DataTypeEntry* param) { parameters_.push_back(param); }
  const std::vector<DataTypeEntry*>& getParameters() const {
    return parameters_;
  }

 private:
  std::string name_;
  std::string qualifier_;
  DataTypeEntry* return_type_;
  std::vector<DataTypeEntry*> parameters_;
};

}  // namespace flang

#endif
