#include "gtest/gtest.h"
#include "sha256.hpp"
#include <vector>

class sha256Test : public ::testing::Test {
  protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};

typedef struct {
  bool success;
  const char *hash;
  const char *msg;
} Case;

TEST_F(sha256Test, Hashing){
  const std::vector<Case> cases {
    // Strings
    {true, "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb", "a"},
    {true, "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad", "abc"},
    {true, "f7846f55cf23e14eebeab5b4e1550cad5b509e3348fbc4efa3a1413d393cb650", "message digest"},
    {true, "71c480df93d6ae2f1efad1447c66c9525e316218cf51fc8d9ed832f2daf18b73", "abcdefghijklmnopqrstuvwxyz"},
    {true, "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1", "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"},

    // ascii
    {true, "3973e022e93220f9212c18d0d0c543ae7c309e46640da93a4a0314de999f5112", "-"},
    {true, "cdf5313889b8d01277d5e0eef37ad9ecd5446e386ef792dbcefff9674d58f458", "O4"},
    {true, "c536c2b19c6c44c26503232671f2880e83e0f9a21fa4a66f0f3f939cfd699bc6", "Qz5"},
    {true, "51711a1fdd1427fa6e8f7a0f2be369ffc57051f0f78e615d35360d9fd2a89d10", "Y$h/"},
    {true, "669a8bf72055a6718cde70e854a73e57b7cadfa2a4757a16f7f82e2afd0a4382", "p(kaX"},
    {true, "0d128ff4d4e7f6c6ad1ea10941d5ed5c2ecc2d265e4118a00cd88b1dffeeab05", "\"i?#/S"},
    {true, "8ac6b5fbffd71d2aa3c9ac7010ecc6e822dc0fa65156a1bfc58f822fbdddabcc", ";C7zRLL"},
    {true, "e93be12e2fba4cd30fc25c9c46520296a3a31b6da098665df4b39775373ca874", "1eZ0a*(u"},
    {true, "79905db2a5f8a861964ba193911f3541239ec59e8e6286077774464351dcc221", "4?P[@+J5D"},
    {true, "b0edc1df74693b0af165855f65ab7343998b76739ba8915b10504d1b096911c6", "G]ipN8[69O"},
    {true, "8400a08d7f4d9c110c5b9110648d6b4d361d099f7adebd09ce62850e86c82cc0", "jWhXp?l)0Ws"},
    {true, "f6bcc9551fdce540dc7d19787e9c641125144a555a7ba9731fd1d5e067f7bdef", "U!0WFh~5J=,4"},

    //errors
    {false, "55b852781b9995a44c939b64e441ae2724b96f79c8f4fb9a141cfc9842c4b0e3", " "},
    {false, "bb48eeaf857780b9724e7c14f8ef86a74ddc239ab331c2facabd1bca128197cA", "b"},

  };

  for (const Case &tc : cases) {
    if (tc.success) {
      EXPECT_STREQ(Crypto::sha256(tc.msg).c_str(), tc.hash);
    } else {
      EXPECT_STRNE(Crypto::sha256(tc.msg).c_str(), tc.hash);
    }
  }
}
