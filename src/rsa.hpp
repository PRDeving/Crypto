#ifndef RSA_HPP
#define RSA_HPP

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
    HASH *encrypt(const char *msg, const unsigned long size, struct Key *key);
    char *decrypt(const HASH *msg, const unsigned long size, struct Key *key);
    HASH sign(const char *str, struct Key *k);
    HASH sign(HASH hash, struct Key *k);
    bool check(HASH hash, const char *str, struct Key *k);
    bool check(HASH hash, HASH control, struct Key *k);
    void print(struct Keyring *keyring);
  }
}

#endif
