#ifndef EXCEPTION_MANAGER_H_
#define EXCEPTION_MANAGER_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "exception/exception.h"

namespace flang {

class ExceptionManager {
 public:
  ExceptionManager();
  virtual ~ExceptionManager() {}

  /**
   * @brief Add exception to manager.
   *
   * @param[in] e Exception to be added. ExceptionManager takes the ownship of this exception.  */
  void addException(Exception* e);

  const boost::ptr_vector<Exception>& getExceptionList() const {
    return except_list_;
  }

 private:
  boost::ptr_vector<Exception> except_list_;
};

};

#endif
