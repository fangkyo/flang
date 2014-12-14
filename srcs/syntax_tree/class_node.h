#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include <cassert>
#include <string>
#include <vector>
#include <string>

#include "func_node.h"
#include "declare_node.h"
#include "scope.h"

using namespace std;

class ErrorEngine;
class ClassNode : public SyntaxNode{

    private:
        string m_name;                    // class name
        string m_parentName;              // parent class name
        vector<DeclareNode*>  m_varList;  // 注意 : 一个declare可能声明多个成员变量，
                                          // 因此这个varList不能简单的看作成员变量列表
        vector<ClassFuncNode*>     m_funcList; // function members list

        ClassNode* m_parent;

    public:
        ClassNode() : m_parent(NULL) {  }
        ~ClassNode();

        void setName( const string& name ) {  m_name = name; }
        const string& getName() {  return m_name; }

        void setParentName( const string& name ) { m_parentName = name; }
        const string& getParentName() { return m_parentName; }

        void setParent( ClassNode* parent );
        ClassNode* getParent() { return m_parent; }
        int getVarsNum() { return m_varList.size(); }
        int getFuncsNum() { return m_funcList.size(); }

        bool hasParent() {  return m_parentName.length() > 0; }

        void addVarDeclare( DeclareNode* declare );

        void addFuncion( ClassFuncNode* func );
        void accept( Visitor& visitor );

        void acceptVars( Visitor& visitor );

        void acceptFuncs(Visitor& visitor, ScopeManager& scopeManager, ErrorEngine& errorEngine);

        string toString() {
            string str( "class " );
            str.append( m_name );
            return str;
        }

        ClassFuncNode* findMemberFunc( const string& funcName,
                                       vector<DataTypeNode*>& paramsType );

        ClassFuncNode* findMemberFunc( const string& funcName );

        VarNode*  findMemberVar( const string& varName );

        ClassNode* getClassNode() { return this; }
};

#endif
