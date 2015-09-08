#include "base/check.h"
#include "symbol_table/symbol.h"
#include "syntax_tree/syntax_tree.h"
#include "type_checker/type_checker.h"
#include "type_checker/exception.h"

namespace flang {

log4cxx::LoggerPtr TypeChecker::logger_(
    log4cxx::Logger::getLogger("flang.TypeChecker"));

void TypeChecker::endVisit(BinaryExpNode* node) {
  ExpNode* left = node->getLeftSide();
  ExpNode* right = node->getRightSide();
  CHECK(left->getSymbol());
  CHECK(right->getSymbol());
  DataType* left_type = left->getSymbol()->getDataType();
  DataType* right_type = right->getSymbol()->getDataType();
  if (left_type->equals(right_type)) {
    if (node->getOperator() != BinaryExpNode::OP_EQ) {
      if (left_type->getType() == DataType::DATA_TYPE_CLASS) {
        Error* error = new IncompatibleOpError(
            "", left_type, right_type, node->getLocation());
        emitException(error);
      }
    VariableSymbol* symbol = new VariableSymbol("");
    node->setSymbol(symbol);
  } else {
    Error* error = new IncompatibleOpError(
        "", left_type, right_type, node->getLocation());
    emitException(error);
  }
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
