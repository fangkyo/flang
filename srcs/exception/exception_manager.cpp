#include "exception/exception_manager.h"

namespace flang {

ExceptionManager::ExceptionManager() {}

void ExceptionManager::addException(Exception* e) {
  except_list_.push_back(e);
}

}  // namespace flang
