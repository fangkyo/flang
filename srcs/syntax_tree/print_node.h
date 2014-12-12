#ifndef PRINT_NODE_H
#define PRINT_NODE_H

#include "exp_node.h"

class PrintNode : public SyntaxNode {
    public:
        ExpNode* m_exp;

        PrintNode( ExpNode* exp ) : m_exp(exp) { assert(m_exp); }

        // TODO  将canPrint()方法放在DataNodeType内部
        bool canPrint( DataTypeNode* dtypeNode ) {  return dtypeNode->getDataType() <= TYPE_STRING; }
        void accept( Visitor& visitor );
};



#endif
