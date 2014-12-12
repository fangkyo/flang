#include <sstream>

#include "data_type.h"
#include "class_node.h"
#include "visitor.h"

using namespace std;

const char* dataTypeStr(DataTypeNode* dtypeNode) {
  return dataTypeStr(dtypeNode->getDataType());
}

/*********************************************
 *               DataTypeNode
 *********************************************/
bool DataTypeNode::isEqual(DataTypeNode* node) {

  if (NULL == node) return false;

  return m_dataType == node->m_dataType;
}

/*********************************************
 *               IntTypeNode
 *********************************************/

IntTypeNode IntTypeNode::ms_instance;

bool IntTypeNode::canCast(DataTypeNode* node) {

  assert(node);
  if (isEqual(node) || node->getDataType() == TYPE_CHAR) return true;
  return false;
}

/*********************************************
 *               CharTypeNode
 *********************************************/
CharTypeNode CharTypeNode::ms_instance;

bool CharTypeNode::canCast(DataTypeNode* node) {

  assert(node);
  if (isEqual(node) || node->getDataType() == TYPE_INT) return true;
  return false;
}

ClassTypeNode::ClassTypeNode(ClassNode* classNode) : m_classNode(classNode) {

  setDataType(TYPE_CLASS);
  if (NULL == m_classNode)
    m_className = "";
  else
    m_className = m_classNode->getName();
}

void ClassTypeNode::accept(Visitor& visitor) { visitor.doClassTypeNode(this); }

bool ClassTypeNode::isEqual(DataTypeNode* dataType) {

  if (NULL == dataType || dataType->getDataType() != TYPE_CLASS) return false;
  if (this == dataType) return true;

  return m_classNode == static_cast<ClassTypeNode*>(dataType)->m_classNode;
}

string ClassTypeNode::toString() {

  stringstream sstream;
  sstream << "class";

  if (m_classNode) {
    sstream << " " << m_classNode->getName();
  }

  return sstream.str();
}

BoolTypeNode BoolTypeNode::ms_instance;

StringTypeNode StringTypeNode::ms_instance;

UndefTypeNode UndefTypeNode::ms_instance;

VoidTypeNode VoidTypeNode::ms_instance;
