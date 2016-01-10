#ifndef SYMBOL_TABLE_DATA_TYPE_H_
#define SYMBOL_TABLE_DATA_TYPE_H_

#include <memory>
#include <string>

#include "base/check.h"

namespace flang {

class ClassSymbol;
class Scope;

class DataType {
 public:
  enum Type {
    DATA_TYPE_INT32,
    DATA_TYPE_INT64,
    DATA_TYPE_CHAR,
    DATA_TYPE_BOOL,
    DATA_TYPE_STRING,
    DATA_TYPE_DOUBLE,
    DATA_TYPE_CLASS,
    DATA_TYPE_VOID,
    DATA_TYPE_UNBOUND,
  };
  DataType(Type type) : type_(type), scope_(nullptr) {}
  virtual bool equals (const DataType& dtype) const;
  virtual uint32_t size() const = 0;
  Type getType() const { return type_; }
  virtual bool isPrimitive() const { return true; }
  virtual std::string getName() const = 0;

  template <typename T>
  T* getImpl() {
    T* impl = dynamic_cast<T*>(this);
    CHECK(impl);
    return impl;
  }

  template <typename T>
  const T* getImpl() const {
    T* impl = dynamic_cast<const T*>(this);
    CHECK(impl);
    return impl;
  }

  void setScope(Scope* scope) {
    scope_ = scope;
  }
  Scope* getScope() const {
    return scope_;
  }

 protected:
  Type type_;
  Scope* scope_;
};

class VoidType : public DataType {
 public:
  VoidType() : DataType(DATA_TYPE_VOID) {}
  uint32_t size() const override { return 0; }
  std::string getName() const override { return "void"; }
  bool isPrimitive() const override { return false; }
  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  // static std::unique_ptr<VoidType> instance_;
  static VoidType instance_;
};

class Int32Type : public DataType {
 public:
  Int32Type() : DataType(DATA_TYPE_INT32) {}
  uint32_t size() const override { return 4; }
  std::string getName() const  override { return "int32"; }
  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  static Int32Type instance_;
};

class Int64Type : public DataType {
 public:
  Int64Type() : DataType(DATA_TYPE_INT64) {}
  uint32_t size() const override { return 8; }
  std::string getName() const override { return "int64"; }
  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  static Int64Type instance_;
};

class DoubleType : public DataType {
 public:
  DoubleType() : DataType(DATA_TYPE_DOUBLE) {}
  uint32_t size() const override { return 8; }
  std::string getName() const override { return "float"; }
  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  static DoubleType instance_;
};

class StringType : public DataType {
 public:
  StringType() : DataType(DATA_TYPE_STRING) {}
  uint32_t size() const override { return 4; }
  std::string getName() const override { return "string"; }

  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  static StringType instance_;
};

class BoolType : public DataType {
 public:
  BoolType() : DataType(DATA_TYPE_BOOL) {}
  uint32_t size() const override { return 1; }
  std::string getName() const override { return "bool"; }

  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  static BoolType instance_;
};

class CharType : public DataType {
 public:
  CharType() : DataType(DATA_TYPE_CHAR) {}
  uint32_t size() const override { return 1; }
  std::string getName() const override { return "char"; }
  /**
   * @brief Get an instance.
   */
  static DataType* getInstance() {
    return &instance_;
  }

 private:
  static CharType instance_;
};

class ClassType : public DataType {
 public:
  ClassType(ClassSymbol* class_symbol);
  ClassSymbol* getClassSymbol() const { return class_symbol_; }
  uint32_t size() const override { return 4; }
  bool isPrimitive() const override { return false; }
  std::string getName() const override;
  bool equals(const DataType& dtype) const override;

 protected:
  ClassSymbol* class_symbol_;
};

class DataTypeFactory {
 public:
  static DataType* getVoidType() {
    return VoidType::getInstance();
  }
  static DataType* getInt32Type() {
    return Int32Type::getInstance();
  }
  static DataType* getInt64Type() {
    return Int64Type::getInstance();
  }
  static DataType* getBoolType() {
    return BoolType::getInstance();
  }
  static DataType* getStringType() {
    return StringType::getInstance();
  }
  static DataType* getCharType() {
    return CharType::getInstance();
  }
  static DataType* getClassType(ClassSymbol* class_symbol);
};

// Comment ArrayType since we don't support array now.
/*
class ArrayType : public DataType {
 public:
  ArrayType() : DataType(DATA_TYPE_ARRAY) {}
  uint32_t size() const override { return 4; }
  bool isPrimitive() const override { return false; }

  std::string getName() const override;

  DataType* getDataType() const { return data_type_.get(); }
  void setDataType(DataType* dtype) {
    CHECK_NE(dtype->getType(), DATA_TYPE_ARRAY);
    data_type_.reset(dtype);
  }

  bool equals (const DataType& dtype) const override;

 private:
  std::unique_ptr<DataType> data_type_;
  uint32_t dimension_;
}; */

}  // namespace flang

#endif
