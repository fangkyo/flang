#include "syntax_tree/import_node.h"

namespace flang {

void ImportListNode::addImport(ImportNode* import) {
  import_list_.push_back(import);
}

}  // namespace flang
