#ifndef CHECK_H_
#define CHECK_H_

#include <cstring>

#include <boost/assert.hpp>

#define CHECK(val) BOOST_ASSERT(val)
#define CHECK_MSG(val, msg) BOOST_ASSERT_MSG(val, msg)

#define CHECK_NULL(val) BOOST_ASSERT(nullptr == val)
#define CHECK_NULL_MSG(val, msg) BOOST_ASSERT_MSG(nullptr == val, msg)

#define CHECK_EQ(val1, val2) BOOST_ASSERT(val1 == val2)
#define CHECK_EQ_MSG(val1, val2, msg) BOOST_ASSERT_MSG(val1 == val2, msg)
#define CHECK_NE(val1, val2) BOOST_ASSERT(val1 != val2)
#define CHECK_NE_MSG(val1, val2, msg) BOOST_ASSERT_MSG(val1 != val2, msg)

#define CHECK_GT(val1, val2) BOOST_ASSERT(val1 > val2)
#define CHECK_LT(val1, val2) BOOST_ASSERT(val1 < val2)

#define CHECK_GE(val1, val2) BOOST_ASSERT(val1 >= val2)
#define CHECK_LE(val1, val2) BOOST_ASSERT(val1 <= val2)

#define CHECK_STREQ(s1, s2) BOOST_ASSERT(0 == std::strcmp(s1, s2))
#define CHECK_STRNE(s1, s2) BOOST_ASSERT(0 != std::strcmp(s1, s2))

#endif
