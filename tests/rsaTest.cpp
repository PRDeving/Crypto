#include "gtest/gtest.h"
#include "rsa.hpp"

class RSATest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      generateKeys(&keyring);
    }
    virtual void TearDown() { }

  public:
    RSA::Keyring keyring;
};



TEST_F(RSATest, StringHexConstructor) {
  ASSERT_TRUE(keyring.e.exponent);
  ASSERT_TRUE(keyring.e.modulus);
  ASSERT_TRUE(keyring.d.exponent);
  ASSERT_TRUE(keyring.d.modulus);
  ASSERT_EQ(keyring.e.modulus, keyring.d.modulus);
}
