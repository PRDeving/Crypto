#include "gtest/gtest.h"
#include "crypto.hpp"

using namespace Crypto;
class RSATest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      RSA::generateKeys(&keyring);
      msg = (char*)"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb";
      msg2 = (char*)"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807795fee48bb";
    }
    virtual void TearDown() { }

  public:
    RSA::Keyring keyring;
    char *msg, *msg2;
};

TEST_F(RSATest, KeyGen) {
  ASSERT_TRUE(keyring.e.exponent);
  ASSERT_TRUE(keyring.e.modulus);
  ASSERT_TRUE(keyring.d.exponent);
  ASSERT_TRUE(keyring.d.modulus);
  ASSERT_EQ(keyring.e.modulus, keyring.d.modulus);
}

TEST_F(RSATest, parseKey) {
  struct RSA::Key k;
  RSA::parseKey(&k, "MSwy");

  ASSERT_EQ(k.exponent, 1);
  ASSERT_EQ(k.modulus, 2);
}

TEST_F(RSATest, parseKeyring) {
  struct RSA::Keyring k;
  RSA::parseKeyring(&k, "MSwyOzMsNA==");

  ASSERT_EQ(k.d.exponent, 1);
  ASSERT_EQ(k.d.modulus, 2);
  ASSERT_EQ(k.e.exponent, 3);
  ASSERT_EQ(k.e.modulus, 4);
}

TEST_F(RSATest, encodeAndDecode) {
  HASH *crypt = RSA::encrypt(msg, strlen(msg), &keyring.e);
  std::string decrypt = RSA::decrypt(crypt, strlen(msg), &keyring.d);
  free(crypt);

  EXPECT_STREQ(decrypt.c_str(), msg);
}

TEST_F(RSATest, signAndCheck) {
  std::string sign = RSA::sign(msg, &keyring.d);
  ASSERT_TRUE(RSA::check(sign.c_str(), msg, &keyring.e));
  ASSERT_FALSE(RSA::check(sign.c_str(), msg2, &keyring.e));
}

TEST_F(RSATest, serializeKey) {
  struct RSA::Key k;
  k.exponent = 1;
  k.modulus = 2;

  std::string ser = RSA::serialize(&k);
  ASSERT_STREQ(ser.c_str(), "MSwy");
}

TEST_F(RSATest, serializeKeyring) {
  struct RSA::Key k1;
  k1.exponent = 1;
  k1.modulus = 2;

  struct RSA::Key k2;
  k2.exponent = 3;
  k2.modulus = 4;

  struct RSA::Keyring kr;
  kr.d = k1;
  kr.e = k2;

  std::string ser = RSA::serialize(&kr);
  ASSERT_STREQ(ser.c_str(), "MSwyOzMsNA==");
}
