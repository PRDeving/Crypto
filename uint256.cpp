#include <cassert>
#include <cstring>
#include "uint256.hpp"
#include "utils.hpp"

Uint256::Uint256() : value() {}
Uint256::Uint256(const char *str) : value() {
  assert(str && strlen(str) == NUM_WORDS * 8);
  for (int i = 0; i < NUM_WORDS * 8; i++) {
    int digit = Utils::parseHexDigit(str[NUM_WORDS * 8 - 1 - i]);
    assert(digit != -1);
    value[i >> 3] |= static_cast<unsigned int>(digit) << ((i & 7) << 2);
  }
}

Uint256::Uint256(const unsigned char b[NUM_WORDS * 4]) : value() {
  assert(b);
  for (int i = 0; i < NUM_WORDS * 4; i++)
    value[i >> 2] |= static_cast<unsigned int>(b[NUM_WORDS * 4 - 1 - i]) << ((i & 3) << 3);
}


unsigned int Uint256::add(const Uint256 &other, unsigned int enable) {
  assert(&other != this && (enable >> 1) == 0);
  unsigned int mask = -enable;
  unsigned int carry = 0;
  for (int i = 0; i < NUM_WORDS; i++) {
    unsigned long sum = static_cast<unsigned long>(value[i]) + (other.value[i] & mask) + carry;
    value[i] = static_cast<unsigned int>(sum);
    carry = static_cast<unsigned int>(sum >> 32);
    assert((carry >> 1) == 0);
  }
  return carry;
}


unsigned int Uint256::subtract(const Uint256 &other, unsigned int enable) {
  assert(&other != this && (enable >> 1) == 0);
  unsigned int mask = -enable;
  unsigned int borrow = 0;
  for (int i = 0; i < NUM_WORDS; i++) {
    unsigned long diff = static_cast<unsigned long>(value[i]) - (other.value[i] & mask) - borrow;
    value[i] = static_cast<unsigned int>(diff);
    borrow = -static_cast<unsigned int>(diff >> 32);
    assert((borrow >> 1) == 0);
  }
  return borrow;
}


unsigned int Uint256::shiftLeft1() {
  unsigned int prev = 0;
  for (int i = 0; i < NUM_WORDS; i++) {
    unsigned int cur = value[i];
    value[i] = (0U + cur) << 1 | prev >> 31;
    prev = cur;
  }
  return prev >> 31;
}


void Uint256::shiftRight1(unsigned int enable) {
  assert((enable >> 1) == 0);
  unsigned int mask = -enable;
  unsigned int cur = value[0];
  for (int i = 0; i < NUM_WORDS - 1; i++) {
    unsigned int next = value[i + 1];
    value[i] = ((cur >> 1 | (0U + next) << 31) & mask) | (cur & ~mask);
    cur = next;
  }
  value[NUM_WORDS - 1] = ((cur >> 1) & mask) | (cur & ~mask);
}


bool Uint256::operator==(const Uint256 &other) const {
  unsigned int diff = 0;
  for (int i = 0; i < NUM_WORDS; i++)
    diff |= value[i] ^ other.value[i];
  return diff == 0;
}


bool Uint256::operator!=(const Uint256 &other) const {
  return !(*this == other);
}


bool Uint256::operator<(const Uint256 &other) const {
  bool result = false;
  for (int i = 0; i < NUM_WORDS; i++) {
    bool eq = value[i] == other.value[i];
    result = (eq & result) | (!eq & (value[i] < other.value[i]));
  }
  return result;
}


bool Uint256::operator<=(const Uint256 &other) const {
  return !(other < *this);
}


bool Uint256::operator>(const Uint256 &other) const {
  return other < *this;
}


bool Uint256::operator>=(const Uint256 &other) const {
  return !(*this < other);
}


// Static initializers
const Uint256 Uint256::ZERO;
const Uint256 Uint256::ONE("0000000000000000000000000000000000000000000000000000000000000001");
