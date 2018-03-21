#include "gtest/gtest.h"
#include "crypto.hpp"
#include <string>

using namespace Crypto;
class Base64Test : public ::testing::Test {
  protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};


TEST_F(Base64Test, encode) {
    ASSERT_STREQ(Base64::encode("123").c_str(), "MTIz");
    ASSERT_STREQ(Base64::encode(" ").c_str(), "IA==");
    ASSERT_STREQ(
        Base64::encode("ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb").c_str(),
        "Y2E5NzgxMTJjYTFiYmRjYWZhYzIzMWIzOWEyM2RjNGRhNzg2ZWZmODE0N2M0ZTcyYjk4MDc3ODVhZmVlNDhiYg=="
    );
    ASSERT_STREQ(
        Base64::encode("9q8rq2n93ur9q2u982q3ruf9qf2u92qu ufjn qfjq 9h 9qfh kwejfhñ qwaehfñ").c_str(),
        "OXE4cnEybjkzdXI5cTJ1OTgycTNydWY5cWYydTkycXUgdWZqbiBxZmpxIDloIDlxZmgga3dlamZow7EgcXdhZWhmw7E="
    );
    ASSERT_STREQ(
        Base64::encode("-!%\"$·%&!)·$%(!\"·)·$/)(\"·%(!\"=").c_str(),
        "LSElIiTCtyUmISnCtyQlKCEiwrcpwrckLykoIsK3JSghIj0="
    );
}

TEST_F(Base64Test, decode) {
    ASSERT_STREQ("123", Crypto::Base64::decode("MTIz").c_str());
    ASSERT_STREQ(" ", Crypto::Base64::decode("IA==").c_str());
    ASSERT_STREQ(
        "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb",
        Crypto::Base64::decode("Y2E5NzgxMTJjYTFiYmRjYWZhYzIzMWIzOWEyM2RjNGRhNzg2ZWZmODE0N2M0ZTcyYjk4MDc3ODVhZmVlNDhiYg==").c_str()
    );
    ASSERT_STREQ(
        "9q8rq2n93ur9q2u982q3ruf9qf2u92qu ufjn qfjq 9h 9qfh kwejfhñ qwaehfñ",
        Crypto::Base64::decode("OXE4cnEybjkzdXI5cTJ1OTgycTNydWY5cWYydTkycXUgdWZqbiBxZmpxIDloIDlxZmgga3dlamZow7EgcXdhZWhmw7E=").c_str()
    );
    ASSERT_STREQ(
        "-!%\"$·%&!)·$%(!\"·)·$/)(\"·%(!\"=",
        Crypto::Base64::decode("LSElIiTCtyUmISnCtyQlKCEiwrcpwrckLykoIsK3JSghIj0=").c_str()
    );
}
