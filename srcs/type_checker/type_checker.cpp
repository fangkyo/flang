#include "base/check.h"
#include "symbol_table/symbol.h"
#include "symbol_table/symbol_table.h"
#include "syntax_tree/ast_node_all.h"
#include "type_checker/type_checker.h"
#include "type_checker/exception.h"
#include "exception/exception_manager.h"

namespace flang {

log4cxx::LoggerPtr TypeChecker::logger_(
    log4cxx::Logger::getLogger("flang.TypeChecker"));

TypeChecker::TypeChecker(
    SymbolTable* symbol_table, ExceptionManager* except_manager):
    symbol_table_(symbol_table), except_manager_(except_manager) {
  CHECK(symbol_table_);
  CHECK(except_manager_);
}

void TypeChecker::addException(Exception* e) {
  CHECK(e);
  except_manager_->addException(e);
}

bool TypeChecker::visit(IntValNode* node) {
  auto& attr = node->getAttr();
  attr.value.set_int_val(node->getValue());
  attr.data_type = DataTypeFactory::getInt64Type();
  return true;
}

bool TypeChecker::visit(BoolValNode* node) {
  auto& attr = node->getAttr();
  attr.value.set_bool_val(node->getValue());
  attr.data_type = DataTypeFactory::getBoolType();
  return true;
}

bool TypeChecker::visit(StringValNode* node) {
  auto& attr = node->getAttr();
  attr.value.set_str_val(node->getValue());
  attr.data_type = DataTypeFactory::getStringType();
  return true;
}

bool TypeChecker::visit(DoubleValNode* node) {
  auto& attr = node->getAttr();
  attr.value.set_double_val(node->getValue());
  attr.data_type = DataTypeFactory::getDoubleType();
  return true;
}

bool TypeChecker::visit(CharValNode* node) {
  auto& attr = node->getAttr();
  attr.value.set_double_val(node->getValue());
  attr.data_type = DataTypeFactory::getCharType();
  return true;
}

bool TypeChecker::endVisit(IfNode* node) {
  ExpNode* test_part = node->getTestPart();
  auto* data_type = test_part->getAttr().data_type;
  CHECK(data_type);
  // Check whether the data type of test part is bool.
  if (data_type->getType() != DataType::DATA_TYPE_BOOL) {
    addException(new IncorrectTypeError(
        *(DataTypeFactory::getBoolType()), *data_type, node->getLocation()));
    return false;
  }
  return true;
}

bool TypeChecker::endVisit(BinaryExpNode* node) {
  ExpNode* left = node->getLeftSide();
  ExpNode* right = node->getRightSide();
  DataType* left_type = left->getDataType();
  DataType* right_type = right->getDataType();
  if (left_type == right_type) {
    // If the type of left side equals to right side, set the type of binary
    // experssion as the left one.
    node->setDataType(left_type);
  } else {
    addException(nullptr);
    return false;
  }
  return true;
}

bool TypeChecker::endVisit(FieldAccessNode* node) {
  auto* expr = node->getExpression();
  auto* field = node->getFieldName();
  CHECK(field);
  std::string field_name = field->toString();
  // field_access : expr '.' simple_name
  if (expr) {
    auto* expr_type = expr->getDataType();
    CHECK(expr_type);
    auto* expr_type_scope = expr_type->getScope();
    if (expr_type_scope) {
      auto* field_symbol = expr_type_scope->lookup(field_name);
      if (!field_symbol) {
        addException(new NoSuchFieldError(
            expr_type->getName(), field_name,
            field->getLocation()));
        return false;
      }
    } else {
      addException(new NoSuchFieldError(
          expr_type->getName(), field_name,
          field->getLocation()));
      return false;
    }
  } else {
    // field_access : simple_name
    auto* symbol = symbol_table_->lookup(field_name);
    if (nullptr == symbol) {
      addException(
          new UndeclaredIdentifierError(field_name, field->getLocation()));
      return false;
    } else {
       // TODO(congfang): In the future a function can be a variable.
       // Theoritcally we shouldn't get a function reference by using a name in the
       // program.
       class FieldSymbolHandler : public SymbolHandler {
        public:
         FieldSymbolHandler(
             TypeChecker* type_checker, FieldAccessNode* field_access) :
             type_checker_(type_checker), field_access_(field_access) {}
  
         bool handle(VariableSymbol* symbol) override {
           // Set the field access node's data type to the data type of variable symbol.
           CHECK(symbol->getDataType());
           field_access_->setDataType(symbol->getDataType());
           return true;
         }

         bool handle(PackageSymbol* symbol) override {
           field_access_->setSymbol(symbol);
           return true;
         }

        private:
         TypeChecker* type_checker_;
         FieldAccessNode* field_access_;
       };
       FieldSymbolHandler handler(this, node);
       return symbol->execute(&handler);
    }
  }
  return true;
}

/*
void TypeChecker::endVisit(PrintNode* node) {
  ExpNode* exp_node = node->getExpNode();
  CHECK_MSG(exp_node, "PrintNode doesn't have expression node to print.");
  CHECK(exp_node->getType());
  if (exp_node->getType()->getType() == DATA_TYPE_VOID) {
    addException(new DataTypeNotPrintableError(
        *(exp_node->getType()), node->getLineNum()));
  }
}

void TypeChecker::finishBase(AssignNode* node) {
  ExpNode* left = node->getLeftSide();
  CHECK(left);
  ExpNode* right = node->getRightSide();
  CHECK(right);
  CHECK(left->getType());
  CHECK(right->getType());
  if (!left->getType()->equals(*(right->getType()))) {
    addException(new NotAssignableError(
        *left, *right, node->getLineNum()));
  }
}

void TypeChecker::finishBase(IfNode* node) {
  auto* test_node = node->getTestNode();
  CHECK_MSG(test_node, "If node's test node is null.");
  if (test_node->getType()->getType() != DATA_TYPE_BOOL) {
    addException(new IncorrectTypeError(
        BoolType(), *test_node->getType(), node->getLineNum()));
  }
}

void TypeChecker::finishBase(WhileNode* node) {
  auto* test_node = node->getTestNode();
  CHECK_MSG(test_node, "While node's test node is null.");
  if (test_node->getType()->getType() != DATA_TYPE_BOOL) {
    addException(new IncorrectTypeError(
        BoolType(), *test_node->getType(), node->getLineNum()));
  }
}

void TypeChecker::finishBase(BreakNode* node) {
  for (auto* parent = node->getParent();
       parent != nullptr;
       parent = parent->getParent()) {
    if (parent->getNodeType() == ASTNode::WHILE_NODE) {
      return;
    }
    if (parent->getNodeType() == ASTNode::FUNC_NODE) {
      break;
    }
  }
  addException(new BreakError(*node));
}

void TypeChecker::finishBase(ReturnNode* node) {
  ExpNode* exp_node = node->getExpression();
  if (exp_node) {
    CHECK(exp_node->getType());
    if (exp_node->getType()->equals());
  }
  //LOG4CXX_TRACE(logger_, "doReturnNode() called");
  //if (NULL == node) return;

  //FuncNode* funcNode = NULL;
  //findFuncScope(funcNode);
  //if (NULL == funcNode) {
    //LOG4CXX_DEBUG(logger_, "return not in function");
    //SingleReturnError error(node);
    //emitError(&error);
  //} else {
    //if (!funcNode->getRetType()->isEqual(node->getRetType())) {
      //LOG4CXX_DEBUG(logger_, "return type not match function return type");
      //ReturnTypeError error(funcNode, node);
      //emitError(&error);
    //}
  //}
  //funcNode->setReturn(true);

  //LOG4CXX_TRACE(logger_, "doReturnNode() return");
}

void TypeChecker::finishBase(CallNode* node) {
  //LOG4CXX_TRACE(logger_, "doCallNode() called");

  //if (NULL == node) return;

  //vector<DataTypeNode*> paramsType;
  //node->getParamsType(paramsType);

  //FuncNode* func = NULL;

  //if (node->getMemberFuncHint()) {
    //LOG4CXX_DEBUG(logger_, "hint function \"" << node->getFuncName()
                                                //<< "\" is a member function");
    //if (node->getCallerName().size() == 0) {
      //// this call
      //LOG4CXX_DEBUG(logger_, "hint function referenced by THIS key word");
      //func = findMemberFunc(node->getFuncName(), paramsType);

    //} else {
      //// var call
      //LOG4CXX_DEBUG(logger_, "hint function referenced by caller \""
                                   //<< node->getCallerName() << "\"");
      //VarNode* caller = findVar(node->getCallerName());
      //node->setCaller(caller);

      //if (NULL == caller) {
        //VarNotDeclareError error(node->getLineNum(), node->getCallerName());
        //emitError(&error);
      //} else if (caller->getDataTypeNode()->isSimpleType()) {
        //NotClassError error(node->getCallerName(), node->getLineNum());
        //emitError(&error);
      //} else {
        //ClassTypeNode* classType = (ClassTypeNode*)caller->getDataTypeNode();
        //assert(classType);
        //ClassNode* classNode = classType->getClassNode();
        //if (NULL == classNode) {
          //ClassNotDefineError error(classType->getClassName(),
                                    //node->getLineNum());
        //} else {
          //func = classNode->findMemberFunc(node->getFuncName(), paramsType);
        //}
      //}
    //}
  //} else {
    //func = findFunc(node->getFuncName(), paramsType);
  //}

  //if (NULL == func) {
    //LOG4CXX_DEBUG(logger_, "not find function " << node->getFuncName());
    //FuncNotDefineError error(node->getFuncName(), node->getLineNum());
    //emitError(&error);

  //} else {
    //LOG4CXX_DEBUG(logger_, "find function " << node->getFuncName());
    //assert(func->getRetType());
    //node->setDataTypeNode(func->getRetType());
  //}

  //LOG4CXX_TRACE(logger_, "doCallNode() return");
}

void TypeChecker::startBase(ClassNode* node) {
  symbol_table_->pushScope(new Scope());
  NameNode* base_class_name = node->getBaseClass();
  if (base_class_name) {
    std::vector<std::string*> qualifiers;
    base_class_name->getQualifiers(&qualifiers);
    SymbolInfo* symbol_info =
        symbol_table_->lookup(qualifiers, base_class_name->getName());
    if (nullptr == symbol_info) {
      addException();
      return;
    }
    if (symbol_info->getSymbolType() != SYMBOL_CLASS) {
      addException();
    }
  }
}

void TypeChecker::finishBase(ClassNode* node) {
  symbol_table_->popScope();
  //LOG4CXX_TRACE(logger_, "doClassNode() called");

  //if (NULL == node) return;

  //if (node->getParentName() == node->getName()) {
    //InheritSelfError error(node);
    //emitError(&error);
  //}

  //if (node->hasParent()) {
    //ClassNode* parent = findClass(node->getParentName());
    //if (NULL == parent) {
      //ClassNotDefineError error(node->getParentName(), node->getLineNum());
      //emitError(&error);
    //}
    //node->setParent(parent);
  //}

  //ClassNode* clazz = findClass(node->getName());
  //if (NULL != clazz) {
    //LOG4CXX_DEBUG(logger_, "class \"" << node->getName() << "\" redefined");
    //ClassRedefinedError error(clazz, node);
    //emitError(&error);
  //} else {
    //addClass(node);
  //}

  //pushClassLevel(node);

  //// first accept vars and then functions
  //// for that function will use var in their scope
  //node->acceptVars(*this);
  //node->acceptFuncs(*this, *this, *this);

  //popLevel();

  //LOG4CXX_TRACE(logger_, "doClassNode() return");
}

void TypeChecker::finishBase(NewNode* node) {
  //LOG4CXX_TRACE(logger_, "doNewNode() called");
  //if (NULL == node) return;

  //ClassNode* classNode = findClass(node->getClassName());

  //if (NULL == classNode) {
    //ClassNotDefineError error(node->getClassName(), node->getLineNum());
    //emitError(&error);
  //} else {
    //node->setClassNode(classNode);
    //node->setDataTypeNode(new ClassTypeNode(classNode->getName(), classNode));
  //}

  //LOG4CXX_TRACE(logger_, "doNewNode() return");
}*/

}  // namespace flang
