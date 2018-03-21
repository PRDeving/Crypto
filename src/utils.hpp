#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>

namespace Crypto {
  namespace Utils {
    template <class T>
      T randomBetween(T a, T b) {
        return (T)rand() % (b - a) + a;
      }

    int parseHexDigit(int ch);
  }
}

#endif
