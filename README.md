# CRYPTO

simple library in c++ for cryptography.

### FEATURES

- SHA256 (Hashing)
- RSA (encrypt/decript and signature/validation)
- uint256 (enough to store a sha256)
- base64 (encode/decode, ya know)

### Building

Crypto is built as an static library, just run:

```

$make

$make install

```

after that, your product should include crypto.hpp `#include "crypto.hpp"` and link the library on compilation `-lcrypto`


### Testing

The testing suite is gtest, grab it from its github, cmake->make->make install and make the tests folder

The tests can be compiled either with the crypto source code (`$make`) or the .a lib (`$make static`)


### Organization

check the tests for examples

```

Crypto
  |-RSA (namespace)
  |   |- Key (struct)
  |   |   |- <long long> modulus
  |   |   |- <long long> exponent
  |   |
  |   |- Keyring (struct)
  |   |   |- <Key> d (for decrypt)
  |   |   |- <Key> e (for encrypt)
  |   |
  |   |- <void> generateKeys(struct Keyring *out)
  |   |- <long long*> encrypt(const char *message, const unsigned long size, struct Key *public)
  |   |- <char*> decrypt(const long long *message, const unsigned long size, struct Key *private)
  |   |- <long long> sign(const char *message, struct Key *private)
  |   |- <long long> sign(long long *message, struct Key *private)
  |   |- <bool> check(long long hash, const char *control, struct Key *public)
  |   |- <bool> check(long long hash, long long control, struct Key *public)
  |   +- <void> print(struct Keyring*) (debug pruporses)
  |
  |-SHA256(class helper) (class wil be renamed as SHA256::CSHA256 and converted to namespace)
  |
  |-SHA256Hash(class type) (class wil be renamed as SHA256::Hash)
  |   |- (constructor) Sha256Hash(const char); (from string <<hash>>)
  |   +- (Constructor) Sha256Hash(const unsigned int, size_t); (from num)
  |
  |-<std::string> sha256(std::string) (to be moved into SHA256::encode)
  |
  |-Uint256 (class type)
  |   |- <unsigned int> add(const Uint256, unsigned int<def 1>)
  |   |- <unsigned int> subtract(const Uint256, unsigned int<def 1>)
  |   |- <unsigned int> shiftLeft1()
  |   +- <void> shiftRight1(unsigned int<def 1>)
  |
  |-Base64 (namespace)
      |-<std::string> encode(cons char*)
      +-<std::string> decode(cons char*)

```
