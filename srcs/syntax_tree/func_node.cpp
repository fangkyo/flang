#include <sstream>

#include "func_node.h"
#include "visitor.h"

using namespace std;

namespace flang {

ReturnNode::ReturnNode(ExpNode* exp_returned) :
  StmtNode(ASTNode::RETURN_NODE), exp_returned_(exp_returned) {

}

void ReturnNode::accept(ASTVisitor* visitor) {
  if (exp_returned_) {
    exp_returned_->accept(visitor);
  }
  visitor->doReturnNode(this);
}


void CallNode::addParam( ExpNode* param ) {
    if( NULL == param )
        return;
    m_paramList.push_back( param );
}

void CallNode::accept( Visitor& visitor ){
    
    for(size_t i=0; i<m_paramList.size(); ++i )
        if( m_paramList[i] )
            m_paramList[i]->accept( visitor );

    visitor.doCallNode( this );
}

void CallNode::getParamsType( vector<DataTypeNode*>& paramsType ){

    for(size_t i=0; i < m_paramList.size(); ++i )
        paramsType.push_back( m_paramList[i]->getDataTypeNode() );

}

}  // namespace flang
