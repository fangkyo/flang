#ifndef VM_VM_H_
#define VM_VM_H_

#include <string>
#include <vector>

#include "vm/bytecode.h"

namespace flang {

class VM {
 public:
  VM(const std::string& filename);
  virtual ~VM();
  void Run();
 protected:
  void Deserialize();
  std::vector<ByteCode> code_section_;
  std::string data_section_;
  std::string stack_section_;
};

}


#endif

