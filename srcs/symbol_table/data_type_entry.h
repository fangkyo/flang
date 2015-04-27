#ifndef DATA_TYPE_ENTRY_H_
#define DATA_TYPE_ENTRY_H_

#include <vector>

#include "symbol_table/data_type.pb.h"

namespace flang {

class FunctionEntry;

// A DataTypeEntry is an entry in symbol table.
// It indicates the data type of a variable.
class DataTypeEntry {
 public:
  virtual ~DataTypeEntry() {}
  void setType(data_type::DataType type) { type_ = type; }
  data_type::DataType getType() const { return type_; }
  virtual bool operator == (const DataTypeEntry& data_type) const {
    return data_type.getType() == this->type_;
  }

 protected:
  DataTypeEntry(data_type::DataType type) : type_(type) {}

 private:
  data_type::DataType type_;
};

class Int32TypeEntry : public DataTypeEntry {
 public:
  Int32TypeEntry() : DataTypeEntry(data_type::INT32) {}
  ~Int32TypeEntry() override {}
};

class CharTypeEntry : public DataTypeEntry {
 public:
  CharTypeEntry() : DataTypeEntry(data_type::CHAR) {}
  ~CharTypeEntry() override {}
};

class BoolTypeEntry : public DataTypeEntry {
 public:
  BoolTypeEntry() : DataTypeEntry(data_type::BOOL) {}
  ~BoolTypeEntry() override {}
};

class StringTypeEntry : public DataTypeEntry {
 public:
  StringTypeEntry() : DataTypeEntry(data_type::STRING) {}
  ~StringTypeEntry() override {}
};

class ClassTypeEntry : public DataTypeEntry {
 public:
  ClassTypeEntry() : DataTypeEntry(data_type::CLASS) {}
  ~ClassTypeEntry() override {}

  void addFunctionEntry(FunctionEntry* function_entry) {
    function_entries_.push_back(function_entry);
  }

  std::vector<FunctionEntry*> getFunctionEntries() {
    return function_entries_;
  }

 private:
  std::vector<FunctionEntry*> function_entries_;
};

}  // namespace flang

#endif
