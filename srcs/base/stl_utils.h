#ifndef STL_UTILS_H_
#define STL_UTILS_H_

#include <boost/ptr_container/ptr_vector.hpp>

namespace flang {

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

/**
 * @brief Append the elements of boost::ptr_vector to a std::vector.
 * @return True if there exists element appended, otherwise false.
 */
template <typename T, typename U>
bool appendPtrVectorToVector(
    const boost::ptr_vector<T>& pv, std::vector<U*>* v) {
  for (auto& t : pv) {
    v->push_back(const_cast<U*>(dynamic_cast<const U*>(&t)));
  }
  return (v->size() > 0);
}

/**
 * @brief Copy the elements of boost::ptr_vector to a std::vector.
 * @return True if there exists element copied, otherwise false.
 */
template <typename T, typename U>
bool ptrVectorToVector(const boost::ptr_vector<T>& pv, std::vector<U*>* v) {
  v->clear();
  return appendPtrVectorToVector(pv, v);
}

}  // namespace flang

#endif
