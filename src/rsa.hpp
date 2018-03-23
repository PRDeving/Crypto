#ifndef RSA_HPP
#define RSA_HPP

#include <string>

#define PRIMES_N 116
typedef long long HASH;

namespace Crypto {
  namespace RSA {
    struct Key {
      HASH modulus;
      HASH exponent;
    };

    struct Keyring {
      struct Key d;
      struct Key e;
    };

    void generateKeys(struct Keyring *keys);
    void parseKeyring(struct Keyring *keys, std::string b64);
    void parseKey(struct Key *k, std::string b64);
    HASH *encrypt(const char *msg, const unsigned long size, struct Key *key);
    std::string decrypt(const HASH *msg, const unsigned long size, struct Key *key);
    HASH sign(const char *str, struct Key *k);
    HASH sign(HASH hash, struct Key *k);
    bool check(HASH hash, const char *str, struct Key *k);
    bool check(HASH hash, HASH control, struct Key *k);
    std::string serialize(struct Key *key);
    std::string serialize(struct Keyring *keys);
    void print(struct Keyring *keyring);
  }
}

#endif
