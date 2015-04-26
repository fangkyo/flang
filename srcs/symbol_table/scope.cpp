#include "scope.h"
#include "exp_node.h"
#include "func_node.h"
#include "ctrl_node.h"
#include "class_node.h"

/*********************************************
 *                   Scope
 *********************************************/
const char* Scope::getScopeTypeStr(ScopeType scopeType) {
  static const char* str[] = {"default", "global", "while", "function",
                              "class"};
  return str[scopeType];
}

string Scope::toString() {
  string typeStr = getScopeTypeStr(m_type);
  switch (m_type) {
    case SCOPE_DEFAULT:
    case SCOPE_GLOBAL:
    case SCOPE_WHILE:
      return typeStr;
    case SCOPE_FUNC:
      return typeStr.append(" ").append(m_func->getName());
    case SCOPE_CLASS:
      return typeStr.append(" ").append(m_class->getName());
  }
}

void Scope::addVar(VarNode* varNode) {
  if (NULL == varNode) return;
  m_varMap.insert(make_pair(varNode->getName(), varNode));
}

void Scope::addFunc(FuncNode* funcNode) {
  if (NULL == funcNode) return;
  m_funcMap[funcNode->getName()].push_back(funcNode);
}

void Scope::addClass(ClassNode* classNode) {
  if (NULL == classNode) return;
  m_classMap.insert(make_pair(classNode->getName(), classNode));
}

VarNode* Scope::findVar(const string& varName) { /*
   unordered_map<string,VarNode*>::iterator got = m_varMap.find( varName );
   if( got == m_varMap.end() )
       return NULL;
   else
       return got->second;*/
  return NULL;
}

// used to detect the function name conflic
FuncNode* Scope::findFunc(const string& funcName) {
  /*
  unordered_map<string, FuncNode*>::iterator got = m_funcMap.find( funcName );

  if( got == m_funcMap.end() )
      return NULL;
  else if( got->second().empty() )
      return NULL;
  else
      return got->second.front();
  */
  return NULL;
}

FuncNode* Scope::testFuncConflict(FuncNode& funcNode) { /*
   FuncMapType::iterator got = m_funcMap.find( funcNode.getName() );
   if( got == m_funcMap.end() ){
       return NULL;
   }

   FuncListType::iterator iter = got->second().begin();
   while( iter != got->second().end() ){
       if( *iter->equals( funcNode ) ){
           return *iter;
       }
       ++iter;
   }*/
  return NULL;
}

// used to search a function
FuncNode* Scope::findFunc(const string& funcName,
                          vector<DataTypeNode*>& paramsType) {
  /*
  unordered_map<string, FuncNode*>::iterator got = m_funcMap.find( funcName );

  if( got == m_funcMap.end() )
      return NULL;
  else if( got->second->matchParamsType( paramsType ) )
      return got->second;
  else */
  return NULL;
}

ClassNode* Scope::findClass(const string& className) {
  unordered_map<string, ClassNode*>::iterator got = m_classMap.find(className);
  if (got == m_classMap.end())
    return NULL;
  else
    return got->second;
}

/*********************************************
 *               ScopeManager
 *********************************************/

LoggerPtr ScopeManager::ms_logger(Logger::getLogger("ScopeManager"));

void ScopeManager::pushDefaultLevel() {
  LOG4CXX_TRACE(ms_logger, "pushDefaultLevel() called");
  m_scopeStack.push_front(Scope(SCOPE_DEFAULT));

  updateVarFloor(m_varFloor);
}

void ScopeManager::pushFuncLevel(FuncNode* funcNode) {
  LOG4CXX_TRACE(ms_logger, "pushFuncLevel() called");

  if (NULL == funcNode) return;
  LOG4CXX_DEBUG(ms_logger, "push function \"" << funcNode->getName() << "\"");
  m_scopeStack.push_front(Scope(funcNode));

  /*
  if( funcNode->isClassMember() ) {
      // 若是某个类的成员函数
      // 变量搜索下限不变，因为可能使用到所属类的成员变量
      updateVarFloor( m_varFloor );
  }else{
      // 变量搜索下限为该层的层数,
      // 很显然该函数内不可能使用外底层定义的变量（除了最底层以外）
      updateVarFloor( m_scopeStack.size() );
  }*/
}

void ScopeManager::pushClassLevel(ClassNode* classNode) {
  LOG4CXX_TRACE(ms_logger, "pushClassLevel() called");
  if (NULL == classNode) return;
  LOG4CXX_DEBUG(ms_logger, "push class \"" << classNode->getName() << "\"");
  m_scopeStack.push_front(Scope(classNode));

  // 变量搜索下限为该层的层数,
  // 很显然该类内不可能使用更外层定义的变量（除了最底层以外）
  updateVarFloor(m_scopeStack.size());
}

void ScopeManager::pushWhileLevel(WhileNode* whileNode) {
  LOG4CXX_TRACE(ms_logger, "pushWhileLevel() called");
  if (NULL == whileNode) return;
  LOG4CXX_DEBUG(ms_logger, "push while at line " << whileNode->getLineNum());
  m_scopeStack.push_front(Scope(whileNode));

  updateVarFloor(m_varFloor);
}

void ScopeManager::pushGlobalLevel() {
  LOG4CXX_TRACE(ms_logger, "pushGlobalLevel() called");
  m_scopeStack.push_front(Scope(SCOPE_GLOBAL));

  updateVarFloor(1);
}

void ScopeManager::popLevel() {
  LOG4CXX_TRACE(ms_logger, "popLevel() called");
  if (getSize() == 0) {
    LOG4CXX_ERROR(ms_logger, "scope stack is empty!");
    return;
  }

  LOG4CXX_DEBUG(ms_logger, "pop level \"" << m_scopeStack.front().toString()
                                          << "\"");
  m_scopeStack.pop_front();
  restoreVarFloor();
}

void ScopeManager::addVar(VarNode* varNode) {
  LOG4CXX_TRACE(ms_logger, "addVar() called");
  if (NULL == varNode) return;
  LOG4CXX_DEBUG(ms_logger, "add var \"" << varNode->getName() << "\"");
  m_scopeStack.front().addVar(varNode);
}

void ScopeManager::addFunc(FuncNode* funcNode) {
  LOG4CXX_TRACE(ms_logger, "addFunc() called");
  if (NULL == funcNode) return;
  LOG4CXX_DEBUG(ms_logger, "add function \"" << funcNode->getName() << "\"");

  m_scopeStack.front().addFunc(funcNode);
}

void ScopeManager::addClass(ClassNode* classNode) {
  LOG4CXX_TRACE(ms_logger, "addClass() called");
  if (NULL == classNode) return;
  LOG4CXX_DEBUG(ms_logger, "add class \"" << classNode->getName() << "\"");

  m_scopeStack.front().addClass(classNode);
}

VarNode* ScopeManager::findVar(const string& varName) {
  LOG4CXX_TRACE(ms_logger, "findVar( \"" << varName << "\" ) called");
  if (getSize() == 0) return NULL;

  list<Scope>::iterator iter = m_scopeStack.begin();
  VarNode* node = NULL;

  int level = m_scopeStack.size();

  while (level >= m_varFloor && iter != m_scopeStack.end()) {
    node = iter->findVar(varName);
    if (node) {
      LOG4CXX_DEBUG(ms_logger, "find var " << varName);
      return node;
    }
    ++iter;
    --level;
  }

  // find var in global scope
  if (iter != m_scopeStack.end()) {
    node = m_scopeStack.back().findVar(varName);
    if (node) {
      LOG4CXX_DEBUG(ms_logger, "find var " << varName);
      return node;
    }
  }
  LOG4CXX_DEBUG(ms_logger, "not find var " << varName);
  return NULL;
}

VarNode* ScopeManager::findVarInCurScope(const string& varName) {
  LOG4CXX_TRACE(ms_logger, "findVarInCurScope( \"" << varName << "\" ) called");

  if (getSize() == 0) return NULL;

  LOG4CXX_TRACE(ms_logger, "findVarInCurScope( \"" << varName << "\" ) return");
  return m_scopeStack.front().findVar(varName);
}

VarNode* ScopeManager::testVarConflict(const string& varName) {
  LOG4CXX_TRACE(ms_logger, "testVarConflict( \"" << varName << "\" ) called");

  if (getSize() == 0) return NULL;
  VarNode* varNode = m_scopeStack.front().findVar(varName);

  if (varNode) {
    LOG4CXX_DEBUG(ms_logger, "testVarConflict : var \"" << varName
                                                        << "\" conflicted");
  } else {
    LOG4CXX_DEBUG(ms_logger, "testVarConflict : var \"" << varName
                                                        << "\" not conflicted");
  }

  LOG4CXX_TRACE(ms_logger, "testVarConflict( \"" << varName << "\" ) return");
  return varNode;
}
/*
FuncNode* ScopeManager::testFuncConflict( const string& funcName ){

    LOG4CXX_TRACE( ms_logger, "testFuncConflict( \""<< funcName << "\" ) called"
);

    if( getSize() == 0 )
        return NULL;

    FuncNode* funcNode = NULL;

    list<Scope>::iterator iter = m_scopeStack.begin();
    while( iter != m_scopeStack.end() ) {

        funcNode = iter->findFunc( funcName );
        if( funcNode )
            return funcNode;
        ++iter;
    }

    LOG4CXX_TRACE( ms_logger, "testFuncConflict( \""<< funcName << "\" ) return"
);
    return NULL;
}*/

FuncNode* ScopeManager::testFuncConflict(const FuncNode& funcNode) {
  /*
  LOG4CXX_TRACE( ms_logger, "testFuncConflict( \"" << funcNode.getName() << "\"
  called )" );

  if( getSize() == 0 )
      return NULL;

  FuncNode* result = NULL;
  Scope& scope = m_scopeStack.back();
  result = scope.testFuncConflict( funcNode );

  if( result != NULL )
      LOG4CXX_DEBUG( ms_logger, "function \"" <<  funcNode.getName() << "\" not
  conflicted" );

  return result; */
  return NULL;
}

FuncNode* ScopeManager::findFunc(const string& funcName) {
  if (getSize() == 0) return NULL;

  list<Scope>::iterator iter = m_scopeStack.begin();
  FuncNode* node = NULL;
  while (iter != m_scopeStack.end()) {
    node = iter->findFunc(funcName);
    if (node) return node;
    ++iter;
  }
  return NULL;
}

FuncNode* ScopeManager::findFunc(const string& funcName,
                                 vector<DataTypeNode*>& paramsType) {
  if (getSize() == 0) return NULL;

  list<Scope>::iterator iter = m_scopeStack.begin();

  FuncNode* funcNode = NULL;
  bool first = true;

  while (iter != m_scopeStack.end()) {
    // 搜索每一层scope的函数
    funcNode = iter->findFunc(funcName, paramsType);
    if (funcNode) return funcNode;

    if (first && iter->getScopeType() == SCOPE_FUNC) {
      // 寻找最上层的函数scope，判断该函数是否为一个类的成员函数
      // 搜索该函数所在类的成员函数（成员函数不会被加入到scope中）
      first = false;
      funcNode = iter->getFuncNode();
      assert(funcNode);
      /*
      if( funcNode->isClassMember() ){

         assert( funcNode->getClass() );
         funcNode = funcNode->getClass()->findMemberFunc( funcName, paramsType
      );
         if( funcNode ) {
              return funcNode;
         }
      }*/
    }

    ++iter;
  }

  return NULL;
}

FuncNode* ScopeManager::findMemberFunc(const string& funcName,
                                       vector<DataTypeNode*>& paramsType) {
  if (getSize() == 0) return NULL;

  list<Scope>::iterator iter = m_scopeStack.begin();

  FuncNode* funcNode = NULL;

  while (iter != m_scopeStack.end()) {
    if (iter->getScopeType() == SCOPE_FUNC) {
      // 寻找最上层的函数scope，判断该函数是否为一个类的成员函数
      // 搜索该函数所在类的成员函数（成员函数不会被加入到scope中）
      funcNode = iter->getFuncNode();
      assert(funcNode);
      /*
      if( funcNode->isClassMember() ){

         assert( funcNode->getClass() );
         return funcNode->getClass()->findMemberFunc( funcName, paramsType );

      }else{

          return NULL;
      }*/
    }
    ++iter;
  }

  return NULL;
}

ClassNode* ScopeManager::findClass(const string& className) {
  if (getSize() == 0) return NULL;
  list<Scope>::iterator iter = m_scopeStack.begin();
  ClassNode* node;
  while (iter != m_scopeStack.end()) {
    node = iter->findClass(className);
    if (node) return node;
    ++iter;
  }
  return NULL;
}

int ScopeManager::findWhileScope(WhileNode*& whileNode) {
  LOG4CXX_TRACE(ms_logger, "findWhileScope() called");

  whileNode = NULL;
  if (getSize() == 0) {
    LOG4CXX_DEBUG(
        ms_logger,
        "can't find while scope, for the reason that scope stack is empty");
    return 0;
  }

  int level = getSize();
  list<Scope>::iterator iter = m_scopeStack.begin();

  while (iter != m_scopeStack.end()) {
    if (iter->getScopeType() == SCOPE_FUNC) {
      return 0;
    } else if (iter->getScopeType() == SCOPE_WHILE) {
      LOG4CXX_DEBUG(ms_logger, "find while node in scope stack");
      whileNode = iter->getWhileNode();
      return level;
    }
    ++level;
    ++iter;
  }

  LOG4CXX_DEBUG(ms_logger, "can't find while scope in scope stack");
  return 0;
}

int ScopeManager::findFuncScope(FuncNode*& funcNode) {
  LOG4CXX_TRACE(ms_logger, "findFuncScope() called");

  funcNode = NULL;
  if (getSize() == 0) {
    LOG4CXX_DEBUG(
        ms_logger,
        "can't find function scope, for the reason that scope stack is empty");
    return 0;
  }

  int level = getSize();
  list<Scope>::iterator iter = m_scopeStack.begin();

  while (iter != m_scopeStack.end()) {
    if (iter->getScopeType() == SCOPE_FUNC) {
      LOG4CXX_DEBUG(ms_logger, "find function scope in scope stack at level "
                                   << level);
      funcNode = iter->getFuncNode();
      return level;
    }
    ++level;
    ++iter;
  }

  LOG4CXX_DEBUG(ms_logger, "can't find function scope in scope stack");
  return 0;
}

int ScopeManager::findClassScope(ClassNode*& classNode) {
  LOG4CXX_TRACE(ms_logger, "findClassScope() called");

  classNode = NULL;
  if (getSize() == 0) {
    LOG4CXX_DEBUG(
        ms_logger,
        "can't find class scope, for the reason that scope stack is empty");
    return 0;
  }

  int level = getSize();
  list<Scope>::iterator iter = m_scopeStack.begin();

  while (iter != m_scopeStack.end()) {
    if (iter->getScopeType() == SCOPE_CLASS) {
      LOG4CXX_DEBUG(ms_logger, "find class scope in scope stack at level "
                                   << level);
      classNode = iter->getClassNode();
      return level;
    }
    ++level;
    ++iter;
  }

  LOG4CXX_DEBUG(ms_logger, "can't find class scope in scope stack");
  return 0;
}

void ScopeManager::updateVarFloor(int varFloor) {
  if (varFloor <= 0 || varFloor > m_scopeStack.size()) {
    LOG4CXX_ERROR(ms_logger, "invalid parameter varFloor " << varFloor);
    m_varFloorStack.push_back(m_varFloor);
    return;
  }

  m_varFloorStack.push_back(m_varFloor);
  m_varFloor = varFloor;
}

void ScopeManager::restoreVarFloor() {
  m_varFloor = m_varFloorStack.back();
  m_varFloorStack.pop_back();
}
