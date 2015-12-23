#include <string>

#include "test/test.h"
#include "base/stl_utils.h"

namespace flang {

class STLUtilsTest : public Test {
};

TEST_F(STLUtilsTest, testPtrVectorToVector) {
  boost::ptr_vector<std::string> pv;
  pv.push_back(new std::string("a"));
  pv.push_back(new std::string("b"));
  pv.push_back(new std::string("c"));

  std::vector<std::string*> v;
  ptrVectorToVector(pv, &v);
  ASSERT_EQ(pv.size(), v.size());
}

}  // namespace flang
