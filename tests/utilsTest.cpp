#include "gtest/gtest.h"
#include "crypto.hpp"

using namespace Crypto;
class utilsTest : public ::testing::Test {
  protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
  public:
    char n[16]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
};


TEST_F(utilsTest, parseHexDigit) {
  for (int i = 0; i < 16; i++) ASSERT_EQ(i, Utils::parseHexDigit(n[i]));
}
