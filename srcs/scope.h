#ifndef SCOPE_H
#define SCOPE_H

#include <cstdint>
#include <cassert>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

#include <log4cxx/logger.h>

using namespace std;
using namespace log4cxx;

enum ScopeType {
    SCOPE_DEFAULT,
    SCOPE_GLOBAL,
    SCOPE_WHILE,
    SCOPE_FUNC,
    SCOPE_CLASS,
    SCOPE_CLASS_FUNC
};

class VarNode;
class WhileNode;
class FuncNode;
class ClassNode;
class ClassFuncNode;
class DataTypeNode;

class Scope{

    private:
        ScopeType m_type;
        
        union {
            WhileNode* m_while;
            FuncNode* m_func;
            ClassNode* m_class;
        };

        typedef unordered_map< string, VarNode* > VarMapType;
        typedef list<FuncNode*> FuncListType;
        typedef unordered_map< string, FuncListType > FuncMapType;
        typedef unordered_map< string, ClassNode* > ClassMapType;

        VarMapType   m_varMap;
        FuncMapType  m_funcMap;
        ClassMapType m_classMap;

    public:
        Scope( ScopeType scopeType ) : m_type ( scopeType ), m_while(NULL) {} 
        Scope( WhileNode* whileNode ) : m_type( SCOPE_WHILE ), m_while( whileNode ) {}
        Scope( FuncNode* funcNode ) : m_type( SCOPE_FUNC ), m_func( funcNode ) {}
        Scope( ClassNode* classNode ) : m_type( SCOPE_CLASS ), m_class( classNode ) {}
        
        ScopeType getScopeType() { return m_type; }
        
        static const char* getScopeTypeStr( ScopeType scopeType);
        string toString();
        void addVar(VarNode*);
        void addFunc(FuncNode*);
        void addClass(ClassNode*);

        VarNode* findVar( const string& );
        FuncNode* findFunc( const string& );
        FuncNode* findFunc( const string&, vector<DataTypeNode*>& );
        ClassNode* findClass( const string& );
        FuncNode* testFuncConflict( FuncNode& funcNode );

        WhileNode* getWhileNode() { assert( SCOPE_WHILE == m_type ); return m_while; }
        FuncNode*  getFuncNode()  { assert( SCOPE_FUNC == m_type );  return m_func; }
        ClassNode* getClassNode() { assert( SCOPE_CLASS == m_type ); return m_class; }

};

class ScopeManager{

    protected:
        static LoggerPtr ms_logger;

        // 变量搜索的下限层数，用于控制嵌套的函数和类定义中变量的类型检查
        int m_varFloor; 

        list<Scope> m_scopeStack;
        vector<int>  m_varFloorStack;

        void pushGlobalLevel();

    public:
        ScopeManager() { reset();  }
        void pushDefaultLevel();
        void pushFuncLevel( FuncNode* funcNode );
        void pushClassLevel( ClassNode* classNode );
        void pushWhileLevel( WhileNode* whileNode );

        void popLevel();

        void addVar(VarNode*);
        void addFunc( FuncNode*);
        void addClass(ClassNode*);


        VarNode* findVar( const string& );
        VarNode* findVarInCurScope( const string& ); // used by var declaration

        VarNode* testVarConflict( const string& varName );
        // FuncNode* testFuncConflict( const string& funcName );
    
        /**
         * 测试当前符号表内函数是否重复定义(允许函数重载)
         * @funcNode 待测试的函数节点
         * @return 查找到的函数节点，若不存在冲突，则返回NULL
         */
        FuncNode* testFuncConflict( const FuncNode& funcNode );

        FuncNode* findFunc( const string& );
        FuncNode* findFunc( const string&, vector<DataTypeNode*>& );
        
        ClassFuncNode* findClassFunc( ClassFuncNode* classFunc );

        FuncNode* findMemberFunc(const string&, std::vector<DataTypeNode*>&);
        ClassNode* findClass( const string& );

        int getSize() { return m_scopeStack.size();  }
        void reset()  { 
            m_varFloor = 0;
            m_scopeStack.clear(); 
            m_varFloorStack.clear();
            pushGlobalLevel(); 
        }

        ScopeType getCurLevelType() { return m_scopeStack.front().getScopeType(); }
        const Scope& getCurScope() {  return m_scopeStack.front(); }
        
        int findWhileScope( WhileNode* &whileNode );
        int findFuncScope( FuncNode* &funcNode );
        int findClassScope(ClassNode*&);
        
    protected:
        void updateVarFloor( int varFloor );
        void restoreVarFloor();
};


#endif 
