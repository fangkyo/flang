#ifndef STL_UTILS_H_
#define STL_UTILS_H_

#include <boost/ptr_container/ptr_vector.hpp>

/**
 * Delete the elements of the container
 * @param container input container which contains pointers need to be released
*/
template <typename C>
void stdDeleteElements(C& container) {
  for (auto* ptr : container) {
    delete ptr;
  }
}

template <typename T, typename U>
void ptrVectorToVector(const boost::ptr_vector<T>& pv, std::vector<U*>* v) {
  for (auto& t : pv) {
    v->push_back(const_cast<U*>(dynamic_cast<const U*>(&t)));
  }
}

#endif
