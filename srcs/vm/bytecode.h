#ifndef VM_CODE_H_
#define VM_CODE_H_

#include <cstdint>
#include <string>

class ByteCode {
 public:
  /**
   * @brief Run the instruction.
   */
  virtual void Run() = 0;
  /**
   * @brief Deserialize from buffer.
   */
  virtual bool Deserialize(const char* data, uint32_t len);

  /**
   * @brief Serialize to a buffer.
   */
  virtual bool Serialize(char* data);

  /**
   * @brief Get the size of the instruction after serialization.
   */
  virtual size_t Size();
};

#endif
