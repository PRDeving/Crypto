# CRYPTO

simple library in c++ for cryptography.

### FEATURES

- SHA256 (Hashing)
- RSA (encrypt/decript and signature/validation)
- uint256 (enough to store a sha256)

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

