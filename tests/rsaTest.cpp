#include "gtest/gtest.h"
#include "crypto.hpp"

using namespace Crypto;
class RSATest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      RSA::generateKeys(&keyring);
      msg = (char*)"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb";
    }
    virtual void TearDown() { }

  public:
    RSA::Keyring keyring;
    char *msg;
};

TEST_F(RSATest, KeyGen) {
  ASSERT_TRUE(keyring.e.exponent);
  ASSERT_TRUE(keyring.e.modulus);
  ASSERT_TRUE(keyring.d.exponent);
  ASSERT_TRUE(keyring.d.modulus);
  ASSERT_EQ(keyring.e.modulus, keyring.d.modulus);
}

TEST_F(RSATest, encodeAndDecode) {
  HASH *crypt = RSA::encrypt(msg, strlen(msg), &keyring.e);
  std::string decrypt = RSA::decrypt(crypt, strlen(msg), &keyring.d);
  free(crypt);

  EXPECT_STREQ(decrypt.c_str(), msg);
}

TEST_F(RSATest, signAndCheck_HASH) {
  HASH *crypt = RSA::encrypt(msg, strlen(msg), &keyring.e);
  HASH sign = RSA::sign(*crypt, &keyring.d);

  ASSERT_TRUE(RSA::check(sign, *crypt, &keyring.e));
  free(crypt);
}

TEST_F(RSATest, signAndCheck_string) {
  HASH sign = RSA::sign(msg, &keyring.d);
  ASSERT_TRUE(RSA::check(sign, msg, &keyring.e));
}
