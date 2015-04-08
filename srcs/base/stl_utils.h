#ifndef STL_UTILS_H_
#define STL_UTILS_H_

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

#endif
