#ifndef ERROR_H
#define ERROR_H

#include <cassert>
#include <iostream>
#include <list>
#include <string>

#include "syntax_tree/syntax_tree.h"
#include "syntax_tree/data_type.h"
#include "syntax_tree/exp_node.h"
#include "syntax_tree/ctrl_node.h"
#include "syntax_tree/func_node.h"
#include "syntax_tree/class_node.h"

#define ERROR_STR_LEN 256


class Error {

    public:
        virtual string toString() { return string(""); }
};

class ErrorEngine {

    private:
        list<string> m_errorList;
    public:
        virtual void emitError( Error* error );
        virtual bool hasError() { return m_errorList.size() > 0;  }
        virtual void printError();
};

class TypeNotMatchError : public Error {
    private:
        ExpNode* m_expNode;
        DataTypeNode* m_expectedType;
    public:
        TypeNotMatchError( ExpNode* exp, DataTypeNode* type )
        : m_expNode(exp), m_expectedType(type) {
            assert( m_expNode );
            assert( m_expectedType );
        }

        string toString();
};

class NotPrintableError  : public Error {
    private:
        ExpNode* m_expNode;

    public:
        NotPrintableError( ExpNode* expNode ) : m_expNode( expNode ) { assert(expNode);}
        string toString();
};

class VarRedeclareError  : public Error {
    private:
        VarNode* m_varNode;
    public:
        VarRedeclareError(VarNode* varNode) : m_varNode(varNode) { assert(m_varNode);}
        string toString();
};


class VarNotDeclareError : public Error {
    private:
        int m_lineNum;
        string m_varName;
    public:
        VarNotDeclareError( int lineNum, const string& varName) 
        : m_lineNum(lineNum), m_varName(varName) {}
        string toString();


};

class TypeNotEqualError : public Error  {
    private:
        ExpNode* m_expNode[2];
    public:
        TypeNotEqualError( ExpNode* expNode1, ExpNode* expNode2 ){ 
            m_expNode[0] = expNode1;
            assert(m_expNode[0] );
            m_expNode[1] = expNode2;
            assert(m_expNode[1] );
        }

        string toString();

};

class BreakWithNoWhileError : public Error {
    private:
        BreakNode* m_breakNode;
    public:
        BreakWithNoWhileError( BreakNode* breakNode ) 
        : m_breakNode( breakNode ) { assert(m_breakNode );}
        string toString();
};

class FuncRedefinedError : public Error {
    private:
        FuncNode* m_orgFunc;
        FuncNode* m_newFunc;
    public:
        FuncRedefinedError( FuncNode* orgFunc, FuncNode* newFunc )
        : m_orgFunc( orgFunc ), m_newFunc( newFunc ) 
        { 
            assert( m_orgFunc );
            assert( m_newFunc );
        }

        string toString();

};

class FuncNotDefineError : public Error {
    private:
        string m_funcName;
        int m_lineNum;
    public:
        FuncNotDefineError( const string& funcName, int lineNum )
        : m_funcName( funcName ), m_lineNum(lineNum) {}

        string toString();
};

class ReturnTypeError : public Error {
    private:
        FuncNode*   m_func;
        ReturnNode* m_ret;

    public:
        ReturnTypeError( FuncNode* func, ReturnNode* ret )
        : m_func( func ), m_ret( ret ) {
            assert( m_func );
            assert( m_ret );
        }

        string toString();

};

class SingleReturnError : public Error {
    private:
        ReturnNode* m_ret;
    public:
        SingleReturnError( ReturnNode* ret ) : m_ret( ret ) {
            assert( m_ret );
        }

        string toString();
};

class LackReturnError : public Error {
    private:
        FuncNode* m_func;
    public:
        LackReturnError( FuncNode* func ) : m_func( func ) {}
        string toString();
};

class InheritSelfError : public Error {
    private:
        ClassNode* m_class;
    public:
        InheritSelfError( ClassNode* clazz ) : m_class ( clazz ){ 
            assert( m_class );  
        }

        string toString();
};

class ClassRedefinedError : public Error {
    private:
        ClassNode* m_orgClass;
        ClassNode* m_newClass;
    public:
        ClassRedefinedError( ClassNode* orgClass, ClassNode* newClass )
        : m_orgClass( orgClass ), m_newClass( newClass ) {
            assert( m_orgClass );
            assert( m_newClass );
        }

        string toString();

};

class ClassNotDefineError : public Error{
    private:
        string m_className;
        int m_lineNum;

    public:
        ClassNotDefineError( const string& className, int lineNum ) 
        : m_className( className ), m_lineNum( lineNum ) {}

        string toString();

};


class NotClassError : public Error {
    private:
        string m_varName;
        int m_lineNum;

    public:
        NotClassError( const string& varName, int lineNum ) 
        : m_varName( varName ), m_lineNum( lineNum ) {}
        string toString();

};





#endif
