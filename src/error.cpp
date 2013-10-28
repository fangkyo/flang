#include <cstring>

#include "error.h"


void fmtMisTypeError( char* msg,  int lineNum,DataTypeNode* dtype1, DataTypeNode* dtype2 ){
	
	sprintf( msg, 
	         "error at line %d : left type \"%s\" can't match right type \"%s\"", 
	         lineNum, 
			 dataTypeStr(dtype1->getDataType()), 
			 dataTypeStr( dtype2->getDataType() )
		   );

}

void fmtNonPrintError( char* msg, int lineNum, DataTypeNode* dtype ){

	sprintf( msg,
	         "error at line %d : type \"%s\" can't be printed.", 
			 lineNum,
			 dataTypeStr(dtype->getDataType()) );
}

void fmtVarRedecError( char* msg, int lineNum,const char* var ){

	sprintf( msg, "error at line %d : \"%s\" has been declared.", lineNum, var);
}


void fmtVarNotDecError( char* msg, int lineNum, const char* var ){

	sprintf( msg, "error at line %d : \"%s\" is not declared.", lineNum, var );
}


void fmtNotBoolError( char* msg, int lineNum, DataTypeNode* dtype ){
	sprintf( msg, "error at line %d : current type is \"%s\", bool type expected.", lineNum, dataTypeStr( dtype->getDataType() ) );
}


void fmtNotIntError( char* msg, int lineNum, const char* exp, DataTypeNode* dtype ){

	sprintf( msg, "error at line %d : \"%s\" type is \"%s\", int type expected.", lineNum, exp, dataTypeStr( dtype->getDataType() ) );
}



void ErrorEngine::emitError( Error* error ){

    if( error )
        m_errorList.push_back(error->toString());
}

void ErrorEngine::printError() {

	for( list<string>::iterator iter = m_errorList.begin();
	     iter != m_errorList.end();
		 ++iter){
		cout << *iter <<endl;
	}

}

string TypeNotMatchError::toString(){
    
    char msg[ERROR_STR_LEN];
    sprintf( msg, 
             "error at line %d : \"%s\" type is \"%s\", \"%s\" expected.",
             m_expNode->getLineNum(),
             m_expNode->toString().c_str(),
             m_expNode->getDataTypeNode()->toString().c_str(),
             m_expectedType->toString().c_str()
           );
    return string( msg );
}

string NotPrintableError::toString() {
    char msg[ERROR_STR_LEN];
    fmtNonPrintError( msg,
                      m_expNode->getLineNum(),
                      m_expNode->getDataTypeNode()
                    );
    return string(msg);
}

string VarRedeclareError::toString() {
    char msg[ERROR_STR_LEN];

    fmtVarRedecError( msg, 
                      m_varNode->getLineNum(),
                      m_varNode->toString().c_str()
                    );
    return string(msg);
}

string VarNotDeclareError::toString() {
    char msg[ERROR_STR_LEN];

    fmtVarNotDecError( msg, 
                       m_lineNum,
                       m_varName.c_str()
                    );
    return string(msg);
}

string TypeNotEqualError::toString() {
    char msg[ERROR_STR_LEN];

    fmtMisTypeError( msg,
                     m_expNode[0]->getLineNum(),
                     m_expNode[0]->getDataTypeNode(),
                     m_expNode[1]->getDataTypeNode()
                   );
    return string(msg);
}

string BreakWithNoWhileError::toString() {
    
    char msg[ERROR_STR_LEN];
    assert( m_breakNode );
    sprintf( msg, 
             "error at line %d : break stmt should in a while scope ",
             m_breakNode->getLineNum() 
           );
    return string( msg );
}


string FuncRedefinedError::toString() {
    char msg[ERROR_STR_LEN];
    assert( m_orgFunc );
    assert( m_newFunc );
    sprintf( msg, 
             "error at line %d : function \"%s\" redefined at line %d",
             m_newFunc->getLineNum(),
             m_newFunc->getName().c_str(),
             m_orgFunc->getLineNum()
           );
    return string( msg );
}

string FuncNotDefineError::toString() {
    char msg[ERROR_STR_LEN];
    sprintf( msg,
             "error at line %d : function \"%s\" is not defined",
             m_lineNum,
             m_funcName.c_str()
            );
    return string( msg );
}

string ReturnTypeError::toString() {
    
    char msg[ERROR_STR_LEN];
    assert( m_func );
    assert( m_ret );

    sprintf( msg, 
             "error at line %d : return type \"%s\" can't match function \"%s\" return type \"%s\"",
             m_ret->getLineNum(),
             m_ret->getRetType()->toString().c_str(),
             m_func->getName().c_str(),
             m_func->getRetType()->toString().c_str()
           );
    return string( msg );

}

string SingleReturnError::toString() {
    char msg[ERROR_STR_LEN];
    assert( m_ret );
    sprintf( msg, 
             "error at line %d : single return without function",
             m_ret->getLineNum()
           );
    return string( msg );
}

string LackReturnError::toString() {

    char msg[ERROR_STR_LEN];
    assert( m_func );

    sprintf( msg,
             "error at line %d : function \"%s\" needs a return value",
             m_func->getLineNum(),
             m_func->getName().c_str()
            );
    return string( msg );
}
string InheritSelfError::toString() {

    char msg[ERROR_STR_LEN];
    assert( m_class );

    sprintf( msg, 
             "error at line %d : class \"%s\" can't inherit itself",
             m_class->getLineNum(),
             m_class->getName().c_str()
           );

    return string( msg );

}

string ClassRedefinedError::toString() {

    char msg[ERROR_STR_LEN];
    assert( m_orgClass );
    assert( m_newClass );

    sprintf( msg, 
             "error at line %d : class \"%s\" is redefined at line %d",
             m_newClass->getLineNum(),
             m_newClass->getName().c_str(),
             m_orgClass->getLineNum()
            );
    return string( msg );

}

string ClassNotDefineError::toString() {
    char msg[ERROR_STR_LEN];
    sprintf( msg,
             "error at line %d : class \"%s\" is not defined",
             m_lineNum,
             m_className.c_str()
            );
    return string( msg );

}


string NotClassError::toString() {
    char msg[ERROR_STR_LEN];
    sprintf( msg,
             "error at line %d : var \"%s\" is not a class",
             m_lineNum,
             m_varName.c_str()
           );
    return string( msg );
}
