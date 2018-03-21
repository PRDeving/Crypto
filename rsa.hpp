#ifndef RSA_HPP
#define RSA_HPP

#define PRIMES_N 116
typedef long long HASH;

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
  HASH *encrypt(const char *msg, const unsigned long size, struct Key *e);
  char *decrypt(const HASH *msg, const unsigned long size, struct Key *d);
  void print(struct Keyring *keyring);
}

#endif
