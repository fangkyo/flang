#ifndef CHECK_H_
#define CHECK_H_

#include <cassert>
#include <cstring>

#include <boost/assert.hpp>

#define CHECK(val) assert(val)

#define CHECK_NULL(val) assert(NULL == val)
#define CHECK_NOTNULL(val) assert(NULL != val)

#define CHECK_EQ(val1, val2) assert(val1 == val2)
#define CHECK_NE(val1, val2) assert(val1 != val2)

#define CHECK_GT(val1, val2) assert(val1 > val2)
#define CHECK_LT(val1, val2) assert(val1 < val2)

#define CHECK_GE(val1, val2) assert(val1 >= val2)
#define CHECK_LE(val1, val2) assert(val1 <= val2)

#define CHECK_STREQ(s1, s2) assert(0 == std::strcmp(s1, s2))
#define CHECK_STRNE(s1, s2) assert(0 != std::strcmp(s1, s2))

#endif
