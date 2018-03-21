#include "gtest/gtest.h"
#include "uint256.hpp"

class uint256Test : public ::testing::Test {
  protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};


TEST_F(uint256Test, StringHexConstructor) {
  Uint256 n("15d2e2bf94051026b54336f6ac15d6a9c1e171f84d5ded7d4eab86861edbfb5a");
  ASSERT_TRUE(n.value);
}

TEST_F(uint256Test, eqOperator) {
  Uint256 n1("15d2e2bf94051026b54336f6ac15d6a9c1e171f84d5ded7d4eab86861edbfb5a");
  Uint256 n2("15d2e2bf94051026b54336f6ac15d6a9c1e171f84d5ded7d4eab86861edbfb5a");
  ASSERT_TRUE(n1 == n2);
}

TEST_F(uint256Test, neOperator) {
  Uint256 n1("15d2e2bf94051026b54336f6ac15d6a9c1e171f84d5ded7d4eab86861edbfb5a");
  Uint256 n2("ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
  ASSERT_TRUE(n1 != n2);
}

TEST_F(uint256Test, gtOperator) {
  Uint256 n1("ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
  Uint256 n2("15d2e2bf94051026b54336f6ac15d6a9c1e171f84d5ded7d4eab86861edbfb5a");
  ASSERT_TRUE(n1 > n2);
}

TEST_F(uint256Test, ltOperator) {
  Uint256 n1("0000000000000000000000000000000000000000000000000000000000000001");
  Uint256 n2("15d2e2bf94051026b54336f6ac15d6a9c1e171f84d5ded7d4eab86861edbfb5a");
  ASSERT_TRUE(n1 < n2);
}
