#include <iostream>
#include <cassert>

#include <Arg.h>

#include "type_check_visitor.h"
#include "error.h"
using namespace std;

LoggerPtr TypeCheckVisitor::ms_logger(Logger::getLogger("TypeCheckVisitor"));

void TypeCheckVisitor::doStmtListNode(StmtListNode* node) {}

void TypeCheckVisitor::doDeclareNode(DeclareNode* node) {
  LOG4CXX_TRACE(ms_logger, "doDeclareNode() called");
  if (NULL == node) return;

  node->getDataTypeNode()->accept(*this);

  vector<AssignNode*>& declareList = node->getDeclareList();

  for (int i = 0; i < declareList.size(); ++i) {
    declareList[i]->setVarDataTypeNode(node->getDataTypeNode()->clone());
    declareList[i]->accept(*this);
  }

  LOG4CXX_TRACE(ms_logger, "doDeclareNode() return");
}

void TypeCheckVisitor::doPrintNode(PrintNode* node) {
  LOG4CXX_TRACE(ms_logger, "doPrintNode() called");
  if (NULL == node) {
    LOG4CXX_ERROR(ms_logger, "print node is null!");
    return;
  }

  DataTypeNode* dtypeNode = node->m_exp->getDataTypeNode();

  if (!node->canPrint(dtypeNode)) {
    LOG4CXX_DEBUG(ms_logger, "expression \""
                                 << node->m_exp->toString() << "\" with type \""
                                 << node->m_exp->getDataTypeNode()->toString()
                                 << "\" can't be printed");
    NotPrintableError error(node->m_exp);
    emitError(&error);
  }

  LOG4CXX_TRACE(ms_logger, "doPrintNode() return");
}

void TypeCheckVisitor::doOpNode(OpNode* node) {
  if (NULL == node) return;

  if (node->hasLeftOpnd() && node->hasRightOpnd()) {
    DataTypeNode* leftType = node->getLeftDataTypeNode();
    DataTypeNode* rightType = node->getRightDataTypeNode();

    if (!leftType->isEqual(rightType)) {
      TypeNotEqualError error(node->m_leftOpnd, node->m_rightOpnd);
      emitError(&error);
    }
  }

  if (node->hasLeftOpnd())
    node->setDataTypeNode(node->getLeftDataTypeNode());
  else
    node->setDataTypeNode(node->getRightDataTypeNode());
}

void TypeCheckVisitor::doVarNode(VarNode* node) {
  LOG4CXX_TRACE(ms_logger, "doVarNode() called");
  if (NULL == node) return;

  VarNode* var = testVarConflict(node->m_name);
  if (var) {
    VarRedeclareError error(var);
    emitError(&error);

  } else {
    addVar(node);
  }

  LOG4CXX_TRACE(ms_logger, "doVarNode() return");
}

void TypeCheckVisitor::doVarRefNode(VarRefNode* node) {
  LOG4CXX_TRACE(ms_logger, "doVarRefNode() called");
  if (NULL == node) return;

  VarNode* var = findVar(node->m_name);
  if (NULL == var) {
    VarNotDeclareError error(node->getLineNum(), node->getName());
    emitError(&error);

    node->setVarNode(NULL);

  } else {
    node->setVarNode(var);
  }

  LOG4CXX_TRACE(ms_logger, "doVarRefNode() return");
}

void TypeCheckVisitor::doAndNode(AndNode* node) {
  LOG4CXX_TRACE(ms_logger, "doAndNode() called");

  if (NULL == node) return;

  doBoolOpNode(node);

  LOG4CXX_TRACE(ms_logger, "doAndNode() return");
}

void TypeCheckVisitor::doEqNode(EqNode* node) {
  LOG4CXX_TRACE(ms_logger, "doEqNode() called");

  doOpNode(node);
  node->setDataTypeNode(BOOL_TYPE_NODE);

  LOG4CXX_TRACE(ms_logger, "doEqNode() return");
}

void TypeCheckVisitor::doLtNode(LtNode* node) {
  LOG4CXX_TRACE(ms_logger, "doLtNode() called");

  doOpNode(node);
  node->setDataTypeNode(BOOL_TYPE_NODE);

  LOG4CXX_TRACE(ms_logger, "doLtNode() return");
}

void TypeCheckVisitor::doAddNode(AddNode* node) {
  LOG4CXX_TRACE(ms_logger, "doAddNode() called");

  doIntOpNode(node);

  LOG4CXX_TRACE(ms_logger, "doAddNode() return");
}

void TypeCheckVisitor::doSubNode(SubNode* node) {
  LOG4CXX_TRACE(ms_logger, "doSubNode() called");

  doIntOpNode(node);

  LOG4CXX_TRACE(ms_logger, "doSubNode() return");
}

void TypeCheckVisitor::doMulNode(MulNode* node) {
  LOG4CXX_TRACE(ms_logger, "doMulNode() called");

  doIntOpNode(node);

  LOG4CXX_TRACE(ms_logger, "doMulNode() return");
}

void TypeCheckVisitor::doDivNode(DivNode* node) {
  LOG4CXX_TRACE(ms_logger, "doDivNode() called");

  doIntOpNode(node);

  LOG4CXX_TRACE(ms_logger, "doDivNode() return");
}

void TypeCheckVisitor::doBoolOpNode(OpNode* node) {
  LOG4CXX_TRACE(ms_logger, "doBoolOpNode() called");
  assert(node);

  char error[ERROR_STR_LEN];

  if (node->m_leftOpnd) {
    DataTypeNode* leftType = node->m_leftOpnd->getDataTypeNode();
    assert(leftType);

    if (!leftType->isEqual(BOOL_TYPE_NODE)) {
      TypeNotMatchError error(node->m_leftOpnd, BOOL_TYPE_NODE);
      emitError(&error);
    }
  }

  if (node->m_rightOpnd) {
    DataTypeNode* rightType = node->m_rightOpnd->getDataTypeNode();
    assert(rightType);
    if (!rightType->isEqual(BOOL_TYPE_NODE)) {
      TypeNotMatchError error(node->m_rightOpnd, BOOL_TYPE_NODE);
      emitError(&error);
    }
  }

  node->setDataTypeNode(BOOL_TYPE_NODE);

  LOG4CXX_TRACE(ms_logger, "doBoolOpNode() return");
}

void TypeCheckVisitor::doIntOpNode(OpNode* node) {
  LOG4CXX_TRACE(ms_logger, "doIntOpNode() called");

  assert(node->hasLeftOpnd());
  DataTypeNode* leftType = node->getLeftDataTypeNode();
  assert(leftType);

  if (!leftType->isEqual(INT_TYPE_NODE)) {
    TypeNotMatchError error(node->m_leftOpnd, INT_TYPE_NODE);
    emitError(&error);
  }

  assert(node->hasRightOpnd());
  DataTypeNode* rightType = node->getRightDataTypeNode();
  assert(rightType);

  if (!rightType->isEqual(INT_TYPE_NODE)) {
    TypeNotMatchError error(node->m_rightOpnd, INT_TYPE_NODE);
    emitError(&error);
  }
  node->setDataTypeNode(INT_TYPE_NODE);

  LOG4CXX_TRACE(ms_logger, "doIntOpNode() return");
}

void TypeCheckVisitor::doAssignNode(AssignNode* node) {
  LOG4CXX_TRACE(ms_logger, "doAssignNode() called");
  if (NULL == node) return;

  if (NULL == node->getExpNode()) {
    LOG4CXX_DEBUG(ms_logger, "right expression of expNode is null");
    return;
  }

  DataTypeNode* varType = node->getVarDataTypeNode();
  DataTypeNode* expType = node->getExpDataTypeNode();

  if (!varType->isEqual(expType)) {
    TypeNotEqualError error(node->m_var, node->m_exp);
    emitError(&error);
  }

  node->setDataTypeNode(varType);

  LOG4CXX_TRACE(ms_logger, "doAssignNode() return");
}

void TypeCheckVisitor::doIfNode(IfNode* node) {
  LOG4CXX_TRACE(ms_logger, "doIfNode() called");

  if (NULL == node) return;

  assert(node->getTest());

  if (node->getTest() == NULL) {
    LOG4CXX_FATAL(ms_logger, "if_stmt's \"test\" is null!");
    return;
  }

  node->getTest()->accept(*this);
  DataTypeNode* testType = node->m_test->getDataTypeNode();

  assert(testType);

  // test part need bool type expression
  if (!testType->isEqual(BOOL_TYPE_NODE)) {
    TypeNotMatchError error(node->m_test, BOOL_TYPE_NODE);
    emitError(&error);
  }

  if (node->m_if) {
    pushDefaultLevel();
    node->m_if->accept(*this);
    popLevel();

  } else {
    LOG4CXX_DEBUG(ms_logger, "if_stmt's \"if\" part is null");
  }

  if (node->m_else) {
    pushDefaultLevel();
    node->m_else->accept(*this);
    popLevel();

  } else {
    LOG4CXX_DEBUG(ms_logger, "if_stmt's \"else\" part is null");
  }

  LOG4CXX_TRACE(ms_logger, "doIfNode() return");
}

void TypeCheckVisitor::doWhileNode(WhileNode* node) {
  if (NULL == node) return;

  ExpNode* test = node->getTest();
  assert(test);
  if (NULL == test) {
    LOG4CXX_FATAL(ms_logger, "while_stmt's \"test\" part is null!");
    return;
  }

  // accept test part
  test->accept(*this);
  assert(test->getDataTypeNode());

  DataTypeNode* testType = test->getDataTypeNode();
  assert(testType);

  // test part need bool type expression
  if (!testType->isEqual(BOOL_TYPE_NODE)) {
    TypeNotMatchError error(node->m_test, BOOL_TYPE_NODE);
    emitError(&error);
  }

  if (node->getBody()) {
    pushWhileLevel(node);
    node->getBody()->accept(*this);
    popLevel();
  } else {
    LOG4CXX_DEBUG(ms_logger, "while_stmt's \"body\" part is null");
  }
}

void TypeCheckVisitor::doBreakNode(BreakNode* node) {
  LOG4CXX_TRACE(ms_logger, "doBreakNode() called");
  if (NULL == node) return;

  WhileNode* whileNode = NULL;
  int level = findWhileScope(whileNode);
  if (NULL == whileNode) {
    BreakWithNoWhileError error(node);
    emitError(&error);
  } else {
    node->setWhileNode(whileNode);
  }

  LOG4CXX_TRACE(ms_logger, "doBreakNode() return");
}

void TypeCheckVisitor::doGlobalFuncNode(GlobalFuncNode* funcNode) {
  LOG4CXX_TRACE(ms_logger, "doGlobalFuncNode() called");

  if (NULL == funcNode) return;

  LOG4CXX_DEBUG(ms_logger, "handle function \"" << funcNode->getName()
                                                << "\"()");

  FuncNode* funcTmp = findFunc(funcNode->getName());

  if (NULL != funcTmp) {
    LOG4CXX_DEBUG(ms_logger, "function \"" << funcNode->getName()
                                           << "\" redefined");
    FuncRedefinedError error(funcTmp, funcNode);
    emitError(&error);

  } else {
    LOG4CXX_DEBUG(ms_logger, "add function \"" << funcNode->getName() << "\"");
    addFunc(funcNode);
  }

  doFuncNodePart(funcNode);

  LOG4CXX_TRACE(ms_logger, "doGlobalFuncNode() return");
}

void TypeCheckVisitor::doClassFuncNode(ClassFuncNode* node) {
  /*
  LOG4CXX_TRACE( ms_logger, "doClassFuncNode() called" );
  if( NULL == node )
      return;
  FuncNode* funcTmp = NULL;
  if( funcTmp = testFuncConflict( node ) ){

      FuncRedefinedError error( funcTmp, node );
      emit( &error );

  }else{
      addFunc( funcNode );
  }

  // doFuncNodePart( node );

  LOG4CXX_TRACE( ms_logger, "doClassFuncNode() return" );
  */
}

void TypeCheckVisitor::doFuncNodePart(FuncNode* node) {
  LOG4CXX_TRACE(ms_logger, "doFuncNodePart() called");

  if (NULL == node) return;

  /*
      // check return type
      assert( node->getRetType() );
      node->getRetType()->accept( *this );

      // check body node
      pushFuncLevel( node );

      vector<VarNode>& paramList = node->getParamList();
      LOG4CXX_DEBUG( ms_logger,"add function \"" <<
                                node->getName()
                                << "\" parameters" );
      for( int i=0; i< paramList.size(); ++i ) {

          paramList[i].getDataTypeNode()->accept( *this );
          addVar( &paramList[i] );
      }

      if( NULL != node->getBody() )
          node->getBody()->accept( *this );

      popLevel();

      // check the return stmt exists
      if( ! node->getRetType()->isEqual( VOID_TYPE_NODE )
          && ! node->hasReturn() ) {
          LackReturnError error( node );
          emitError( &error );
      }*/

  LOG4CXX_TRACE(ms_logger, "doFuncNodePart() return");
}

void TypeCheckVisitor::doReturnNode(ReturnNode* node) {
  LOG4CXX_TRACE(ms_logger, "doReturnNode() called");
  if (NULL == node) return;

  FuncNode* funcNode = NULL;
  findFuncScope(funcNode);
  if (NULL == funcNode) {
    LOG4CXX_DEBUG(ms_logger, "return not in function");
    SingleReturnError error(node);
    emitError(&error);
  } else {
    if (!funcNode->getRetType()->isEqual(node->getRetType())) {
      LOG4CXX_DEBUG(ms_logger, "return type not match function return type");
      ReturnTypeError error(funcNode, node);
      emitError(&error);
    }
  }
  funcNode->setReturn(true);

  LOG4CXX_TRACE(ms_logger, "doReturnNode() return");
}

void TypeCheckVisitor::doCallNode(CallNode* node) {
  LOG4CXX_TRACE(ms_logger, "doCallNode() called");

  if (NULL == node) return;

  vector<DataTypeNode*> paramsType;
  node->getParamsType(paramsType);

  FuncNode* func = NULL;

  // 由语法分析显示指出该调用是成员函数调用
  if (node->getMemberFuncHint()) {
    LOG4CXX_DEBUG(ms_logger, "hint function \"" << node->getFuncName()
                                                << "\" is a member function");
    if (node->getCallerName().size() == 0) {
      // this call
      LOG4CXX_DEBUG(ms_logger, "hint function referenced by THIS key word");
      func = findMemberFunc(node->getFuncName(), paramsType);

    } else {
      // var call
      LOG4CXX_DEBUG(ms_logger, "hint function referenced by caller \""
                                   << node->getCallerName() << "\"");
      VarNode* caller = findVar(node->getCallerName());
      node->setCaller(caller);

      if (NULL == caller) {
        VarNotDeclareError error(node->getLineNum(), node->getCallerName());
        emitError(&error);
      } else if (caller->getDataTypeNode()->isSimpleType()) {
        NotClassError error(node->getCallerName(), node->getLineNum());
        emitError(&error);
      } else {
        ClassTypeNode* classType = (ClassTypeNode*)caller->getDataTypeNode();
        assert(classType);
        ClassNode* classNode = classType->getClassNode();
        if (NULL == classNode) {
          ClassNotDefineError error(classType->getClassName(),
                                    node->getLineNum());
        } else {
          func = classNode->findMemberFunc(node->getFuncName(), paramsType);
        }
      }
    }
  } else {
    func = findFunc(node->getFuncName(), paramsType);
  }

  if (NULL == func) {
    LOG4CXX_DEBUG(ms_logger, "not find function " << node->getFuncName());
    FuncNotDefineError error(node->getFuncName(), node->getLineNum());
    emitError(&error);

  } else {
    LOG4CXX_DEBUG(ms_logger, "find function " << node->getFuncName());
    assert(func->getRetType());
    node->setDataTypeNode(func->getRetType());
  }

  LOG4CXX_TRACE(ms_logger, "doCallNode() return");
}

void TypeCheckVisitor::doClassNode(ClassNode* node) {
  LOG4CXX_TRACE(ms_logger, "doClassNode() called");

  if (NULL == node) return;

  if (node->getParentName() == node->getName()) {
    InheritSelfError error(node);
    emitError(&error);
  }

  // 如果该类有父类，则查找并设置其父类
  if (node->hasParent()) {
    ClassNode* parent = findClass(node->getParentName());
    if (NULL == parent) {
      ClassNotDefineError error(node->getParentName(), node->getLineNum());
      emitError(&error);
    }
    node->setParent(parent);
  }

  ClassNode* clazz = findClass(node->getName());
  if (NULL != clazz) {
    LOG4CXX_DEBUG(ms_logger, "class \"" << node->getName() << "\" redefined");
    ClassRedefinedError error(clazz, node);
    emitError(&error);
  } else {
    addClass(node);
  }

  pushClassLevel(node);

  // first accept vars and then functions
  // for that function will use var in their scope
  node->acceptVars(*this);
  node->acceptFuncs(*this, *this, *this);

  popLevel();

  LOG4CXX_TRACE(ms_logger, "doClassNode() return");
}

void TypeCheckVisitor::doNewNode(NewNode* node) {
  LOG4CXX_TRACE(ms_logger, "doNewNode() called");
  if (NULL == node) return;

  ClassNode* classNode = findClass(node->getClassName());

  if (NULL == classNode) {
    ClassNotDefineError error(node->getClassName(), node->getLineNum());
    emitError(&error);
  } else {
    node->setClassNode(classNode);
    node->setDataTypeNode(new ClassTypeNode(classNode->getName(), classNode));
  }

  LOG4CXX_TRACE(ms_logger, "doNewNode() return");
}

void TypeCheckVisitor::doClassTypeNode(ClassTypeNode* node) {
  LOG4CXX_TRACE(ms_logger, "doClassTypeNode() called");

  if (NULL == node) return;

  ClassNode* classNode = findClass(node->getClassName());
  if (NULL == classNode) {
    ClassNotDefineError error(node->getClassName(), node->getLineNum());
    emitError(&error);

  } else {
    node->setClassNode(classNode);
  }

  LOG4CXX_TRACE(ms_logger, "doClassTypeNode() return");
}

/*
void TypeCheckVisitor::doOrNode( OrNode* node ){
        doBoolOpNode( node );
}

void TypeCheckVisitor::doNotNode( NotNode* node ){
        doBoolOpNode( node );
}
void TypeCheckVisitor::doNeNode( NeNode* node ){
        doOpNode( node );
        node->setDataTypeNode( TYPE_BOOL );
}

void TypeCheckVisitor::doGtNode( GtNode* node ){
        doOpNode( node );
        node->setDataTypeNode( TYPE_BOOL );
}

void TypeCheckVisitor::doGeNode( GeNode* node ){
        doOpNode( node );
        node->setDataTypeNode( TYPE_BOOL );
}


void TypeCheckVisitor::doLeNode( LeNode* node ){
        doOpNode( node );
        node->setDataTypeNode( TYPE_BOOL );
}
*/
