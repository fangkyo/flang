#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "syntax_tree.h"

#define INT_TYPE_NODE   IntTypeNode::getInstance()
#define CHAR_TYPE_NODE  CharTypeNode::getInstance()
#define STRING_TYPE_NODE   StringTypeNode::getInstance()
#define BOOL_TYPE_NODE  BoolTypeNode::getInstance()
#define UNDEF_TYPE_NODE UndefTypeNode::getInstance()
#define VOID_TYPE_NODE  VoidTypeNode::getInstance()

class ClassNode;
class Visitor;

class DataTypeNode : public SyntaxNode {

    protected:
        DataType m_dataType;

        void setDataType( DataType dataType ) { m_dataType = dataType; }

    public:
        DataType getDataType()      { return m_dataType; }

        virtual bool isSimpleType() { return true; }

        virtual bool isSingleton()    { return true; } // used for memory collection
        virtual bool isEqual( DataTypeNode* node );

        virtual DataTypeNode* clone() { return this; }

};

class IntTypeNode : public DataTypeNode {

    private:
        static IntTypeNode ms_instance;
        IntTypeNode() { setDataType( TYPE_INT );  }

    public:
        bool canCast( DataTypeNode* node );
        static IntTypeNode* getInstance() {  return &ms_instance; }
        string toString() { return "int"; }
};

class CharTypeNode : public DataTypeNode {

    private:
        static CharTypeNode ms_instance;
        CharTypeNode() { setDataType( TYPE_CHAR );}

    public:
        bool canCast( DataTypeNode* node );
        static CharTypeNode* getInstance() { return &ms_instance;}

        string toString() { return "char"; }
};

class BoolTypeNode : public DataTypeNode {
    private:
        static BoolTypeNode ms_instance;
        BoolTypeNode() { setDataType( TYPE_BOOL ); }
    public:
        static BoolTypeNode* getInstance() { return &ms_instance;}

        string toString() { return "bool"; }
};

class StringTypeNode : public DataTypeNode {

    private:
        static StringTypeNode ms_instance;
        StringTypeNode() { setDataType( TYPE_STRING ); }

    public:
        static StringTypeNode* getInstance() { return &ms_instance; } 

        string toString() { return "string"; }

};

class VoidTypeNode : public DataTypeNode {
    private:
        static VoidTypeNode ms_instance;
        VoidTypeNode() { setDataType( TYPE_VOID ); }
    public:
        static VoidTypeNode* getInstance() { return &ms_instance; }

        string toString() { return "void"; }
};


class UndefTypeNode : public DataTypeNode{
    private:
        static UndefTypeNode ms_instance;
        UndefTypeNode() { setDataType( TYPE_UNDEF ); }
    public:
        static UndefTypeNode* getInstance() { return &ms_instance; }

        string toString() { return "undefined"; }
};

class ClassTypeNode : public DataTypeNode {
    private:
        string     m_className;
        ClassNode* m_classNode;
    public:
        
        ClassTypeNode( const string& className, ClassNode* classNode = NULL ) 
        : m_className(className), m_classNode( classNode ) {

            setDataType( TYPE_CLASS );
        }
        ClassTypeNode( ClassNode* classNode ) ;

        bool isSimpleType() { return false; }

        bool isSingleton()    { return false; }

        string& getClassName() { return m_className; }
        void setClassName( string& className ) { className = m_className; }
        
        ClassNode* getClassNode() { return m_classNode; }
        void  setClassNode( ClassNode* classNode ) { m_classNode = classNode; }
        
        DataTypeNode* clone() { return new ClassTypeNode( m_className, m_classNode ); }

        void accept( Visitor& visitor );

        bool isEqual( DataTypeNode* dataType );

        string toString();

};

const char* dataTypeStr( DataTypeNode* );


#endif
