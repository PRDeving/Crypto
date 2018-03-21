#ifndef BASE64_HPP
#define BASE64_HPP
#include <string>

namespace Crypto {
  namespace Base64 {
    std::string encode(const char *str);
    std::string decode(const char *str);
  }
}

#endif
