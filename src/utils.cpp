#include "utils.hpp"

using namespace Crypto;
int Utils::parseHexDigit(int ch) {
  if ('0' <= ch && ch <= '9')
    return ch - '0';
  else if ('a' <= ch && ch <= 'f')
    return ch - 'a' + 10;
  else if ('A' <= ch && ch <= 'F')
    return ch - 'A' + 10;
  else
    return -1;
}
