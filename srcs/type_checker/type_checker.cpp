
#include "type_checker/type_checker.h"
#include "base/check.h"

namespace flang {

log4cxx::LoggerPtr TypeChecker::logger_(
    log4cxx::Logger::getLogger("flang.TypeChecker"));


bool TypeChecker::visit(BinaryExpNode* node) {
  ExpNode* left = node->getLeftSide();
  ExpNode* right = node->getRightSide();
  if (left->getNodeType() == right->getNodeType()) {
    return true;
  } else {
    return false;
  }
}


void TypeChecker::doPrintNode(PrintNode* node) {
  //LOG4CXX_TRACE(logger_, "doPrintNode() called");
  //if (NULL == node) {
    //LOG4CXX_ERROR(logger_, "print node is null!");
    //return;
  //}

  //DataTypeNode* dtypeNode = node->m_exp->getDataTypeNode();

  //if (!node->canPrint(dtypeNode)) {
    //LOG4CXX_DEBUG(logger_, "expression \""
                                 //<< node->m_exp->toString() << "\" with type \""
                                 //<< node->m_exp->getDataTypeNode()->toString()
                                 //<< "\" can't be printed");
    //NotPrintableError error(node->m_exp);
    //emitError(&error);
  //}

  //LOG4CXX_TRACE(logger_, "doPrintNode() return");
}



void TypeChecker::doAssignNode(AssignNode* node) {
  //LOG4CXX_TRACE(logger_, "doAssignNode() called");
  //if (NULL == node) return;

  //if (NULL == node->getExpNode()) {
    //LOG4CXX_DEBUG(logger_, "right expression of expNode is null");
    //return;
  //}

  //DataTypeNode* varType = node->getVarDataTypeNode();
  //DataTypeNode* expType = node->getExpDataTypeNode();

  //if (!varType->isEqual(expType)) {
    //TypeNotEqualError error(node->m_var, node->m_exp);
    //emitError(&error);
  //}

  //node->setDataTypeNode(varType);

  //LOG4CXX_TRACE(logger_, "doAssignNode() return");
}

void TypeChecker::doIfNode(IfNode* node) {
  //LOG4CXX_TRACE(logger_, "doIfNode() called");

  //if (NULL == node) return;

  //assert(node->getTest());

  //if (node->getTest() == NULL) {
    //LOG4CXX_FATAL(logger_, "if_stmt's \"test\" is null!");
    //return;
  //}

  //node->getTest()->accept(*this);
  //DataTypeNode* testType = node->m_test->getDataTypeNode();

  //assert(testType);

  //// test part need bool type expression
  //if (!testType->isEqual(BOOL_TYPE_NODE)) {
    //TypeNotMatchError error(node->m_test, BOOL_TYPE_NODE);
    //emitError(&error);
  //}

  //if (node->m_if) {
    //pushDefaultLevel();
    //node->m_if->accept(*this);
    //popLevel();

  //} else {
    //LOG4CXX_DEBUG(logger_, "if_stmt's \"if\" part is null");
  //}

  //if (node->m_else) {
    //pushDefaultLevel();
    //node->m_else->accept(*this);
    //popLevel();

  //} else {
    //LOG4CXX_DEBUG(logger_, "if_stmt's \"else\" part is null");
  //}

  //LOG4CXX_TRACE(logger_, "doIfNode() return");
}

void TypeChecker::doWhileNode(WhileNode* node) {
  //if (NULL == node) return;

  //ExpNode* test = node->getTest();
  //assert(test);
  //if (NULL == test) {
    //LOG4CXX_FATAL(logger_, "while_stmt's \"test\" part is null!");
    //return;
  //}

  //// accept test part
  //test->accept(*this);
  //assert(test->getDataTypeNode());

  //DataTypeNode* testType = test->getDataTypeNode();
  //assert(testType);

  //// test part need bool type expression
  //if (!testType->isEqual(BOOL_TYPE_NODE)) {
    //TypeNotMatchError error(node->m_test, BOOL_TYPE_NODE);
    //emitError(&error);
  //}

  //if (node->getBody()) {
    //pushWhileLevel(node);
    //node->getBody()->accept(*this);
    //popLevel();
  //} else {
    //LOG4CXX_DEBUG(logger_, "while_stmt's \"body\" part is null");
  //}
}

void TypeChecker::doBreakNode(BreakNode* node) {
  //LOG4CXX_TRACE(logger_, "doBreakNode() called");
  //if (NULL == node) return;

  //WhileNode* whileNode = NULL;
  //int level = findWhileScope(whileNode);
  //if (NULL == whileNode) {
    //BreakWithNoWhileError error(node);
    //emitError(&error);
  //} else {
    //node->setWhileNode(whileNode);
  //}

  //LOG4CXX_TRACE(logger_, "doBreakNode() return");
}

// void TypeChecker::doGlobalFuncNode(GlobalFuncNode* funcNode) {
  //LOG4CXX_TRACE(logger_, "doGlobalFuncNode() called");

  //if (NULL == funcNode) return;

  //LOG4CXX_DEBUG(logger_, "handle function \"" << funcNode->getName()
                                                //<< "\"()");

  //FuncNode* funcTmp = findFunc(funcNode->getName());

  //if (NULL != funcTmp) {
    //LOG4CXX_DEBUG(logger_, "function \"" << funcNode->getName()
                                           //<< "\" redefined");
    //FuncRedefinedError error(funcTmp, funcNode);
    //emitError(&error);

  //} else {
    //LOG4CXX_DEBUG(logger_, "add function \"" << funcNode->getName() << "\"");
    //addFunc(funcNode);
  //}

  //doFuncNodePart(funcNode);

  //LOG4CXX_TRACE(logger_, "doGlobalFuncNode() return");
// }

void TypeChecker::doReturnNode(ReturnNode* node) {
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

void TypeChecker::doCallNode(CallNode* node) {
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

void TypeChecker::doClassNode(ClassNode* node) {
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

void TypeChecker::doNewNode(NewNode* node) {
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
}

}  // namespace flang
