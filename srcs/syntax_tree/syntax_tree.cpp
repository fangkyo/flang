#include <cstring>
#include <iostream>

#include "ast_visitor/ast_visitor.h"
#include "base/check.h"
#include "syntax_tree/syntax_tree.h"

using namespace std;

//const char* dataTypeStr( DataType dtype ){
  //static const char* typeStr[] = {
    //"int",
    //"bool",
    //"char",
    //"string",
    //"class",
    //"void",
    //"undefined"
  //};
  //return typeStr[dtype];
//}

namespace flang {

// static
ProgramNode* SyntaxTree::CreateProgramNode() {
  return new ProgramNode();
}

void SyntaxTree::accept(ASTVisitor* visitor) {
  visitor->doProgramNode(root_.get());
}

}  // namespace flang
