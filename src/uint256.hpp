#ifndef UINT256_HPP
#define UINT256_HPP

#include <cstdint>

namespace Crypto {
  class Uint256 {
    public:
      const static int NUM_WORDS = 8;
      unsigned int value[NUM_WORDS];

      Uint256();
      explicit Uint256(const char *str);
      explicit Uint256(const unsigned char b[NUM_WORDS * 4]);

      unsigned int add(const Uint256 &other, unsigned int enable=1);
      unsigned int subtract(const Uint256 &other, unsigned int enable=1);

      unsigned int shiftLeft1();
      void shiftRight1(unsigned int enable=1);
      bool operator==(const Uint256 &other) const;

      bool operator!=(const Uint256 &other) const;
      bool operator<(const Uint256 &other) const;
      bool operator<=(const Uint256 &other) const;
      bool operator>(const Uint256 &other) const;
      bool operator>=(const Uint256 &other) const;

      static const Uint256 ZERO;
      static const Uint256 ONE;

  };
}

#endif
