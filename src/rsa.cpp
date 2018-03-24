#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <math.h>
#include <time.h>
#include <sstream>
#include "utils.hpp"
#include "base64.hpp"
#include "rsa.hpp"

using namespace Crypto;
unsigned int primes[PRIMES_N] {
  10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093,
  10099, 10103, 10111, 10133, 10139, 10141, 10151, 10159, 10163, 10169,
  10177, 10181, 10193, 10211, 10223, 10243, 10247, 10253, 10259, 10267,
  10271, 10273, 10289, 10301, 10303, 10313, 10321, 10331, 10333, 10337,
  10343, 10357, 10369, 10391, 10399, 10427, 10429, 10433, 10453, 10457,
  10459, 10463, 10477, 10487, 10499, 10501, 10513, 10529, 10531, 10559,
  10567, 10589, 10597, 10601, 10607, 10613, 10627, 10631, 10639, 10651,
  10657, 10663, 10667, 10687, 10691, 10709, 10711, 10723, 10729, 10733,
  10739, 10753, 10771, 10781, 10789, 10799, 10831, 10837, 10847, 10853,
  10859, 10861, 10867, 10883, 10889, 10891, 10903, 10909, 10937, 10939,
  10949, 10957, 10973, 10979, 10987, 10993, 11003, 11027, 11047, 11057,
  11059, 77839, 77849, 77863, 77867, 77893,
};


HASH gcd(HASH a, HASH b) {
	HASH c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

HASH lcm(HASH a, HASH b) {
  HASH temp = gcd(a, b);
  return temp ? (a / temp * b) : 0;
}

HASH modinv(const HASH a, const HASH m) {
  HASH la = a % m;
  for (int x = 1; x < m; x++) {
    if ((la * x) % m == 1) return x;
  }
  return 0;
}

HASH modExp(HASH b, HASH e, HASH m) {
	if (b < 0 || e < 0 || m <= 0) exit(1);
	b = b % m;
	if (e == 0) return 1;
	if (e == 1) return b;
	if (e % 2 == 0){
		return (modExp(b * b % m, e/2, m) % m);
	}
	if (e % 2 == 1){
		return (b * modExp(b, (e-1), m) % m);
	}
	return 0;
}

void RSA::generateKeys(struct Keyring *keys) {
  srand(time(0));
  HASH e =  primes[Utils::randomBetween(0, PRIMES_N)];
  HASH p, q, lambda;

  do {
		p =  primes[Utils::randomBetween(0, PRIMES_N)];
		q =  primes[Utils::randomBetween(0, PRIMES_N)];
    lambda = lcm((p - 1), (q - 1));
  } while (gcd(e, lambda) != 1 || abs((p - q)) >> ((sizeof(int) * 10) - 100) == 0);

  HASH mod = p * q;
  // Public
	keys -> e.modulus = mod;
	keys -> e.exponent = modinv(e, lambda);
  //Private
	keys -> d.modulus = mod;
	keys -> d.exponent = e;
}

void RSA::parseKey(struct Key *k, std::string b64) {
  std::string r = Base64::decode(b64.c_str());
  int delim = r.find(',');

  k -> exponent = (HASH)atoi(r.substr(0, delim).c_str());
  k -> modulus = (HASH)atoi(r.substr(delim + 1, r.length()).c_str());
}


void RSA::parseKeyring(struct Keyring *keys, std::string b64) {
  std::string r = Base64::decode(b64.c_str());
  int kd = r.find(';');

  std::string d = r.substr(0, kd);
  int dd = d.find(',');
  std::string e = r.substr(kd + 1, r.length());
  int ed = e.find(',');

  keys -> d.exponent = (HASH)atoi(d.substr(0, dd).c_str());
  keys -> d.modulus = (HASH)atoi(d.substr(dd + 1, d.length()).c_str());

  keys -> e.exponent = (HASH)atoi(e.substr(0, ed).c_str());
  keys -> e.modulus = (HASH)atoi(e.substr(ed + 1, e.length()).c_str());
}

HASH *RSA::encrypt(const char *msg, const unsigned long size, struct Key *e) {
	HASH *encrypted = (HASH*)malloc(sizeof(HASH) * size);
	for (unsigned long i = 0; i < size; i++) {
		encrypted[i] = modExp(msg[i], e -> exponent, e -> modulus);
	}
	return encrypted;
}

std::string RSA::decrypt(const HASH *msg, const unsigned long size, struct Key *d) {
  std::string decrypted(size, '\0');
	for (unsigned long i = 0; i < size; i++) {
		decrypted[i] = modExp(msg[i], d -> exponent, d -> modulus);
	}
	return decrypted;
}

std::string RSA::sign(const char *str, struct Key *k) {
  int size = strlen(str);
  HASH h[size];
	for (int i = 0; i < size; i++) {
		h[i] = (int)str[i];
	}
  return sign(&h[0], size, k);
}

std::string RSA::sign(HASH *hash, int size, struct Key *k) {
  std::string r = "";
  for (int i = 0; i < size; i++) {
    if (i > 0) r += "x";
    r += std::to_string(modExp(*(hash + i), k -> exponent, k -> modulus));
  }
  r += ":" + std::to_string(size);

  return Base64::encode(r.c_str());
}

bool RSA::check(std::string signature, const char *control, struct Key *k) {
  std::string sig = Base64::decode(signature.c_str());

  int idx = 0;
  int size_delim = sig.find(':');
  std::stringstream ss(sig.substr(0, size_delim));
  std::string item;
  while (std::getline(ss, item, 'x')) {
    if (modExp((HASH)atoi(item.c_str()), k -> exponent, k -> modulus) != (HASH)control[idx]) return false;
    idx++;
  }
  return true;
}

std::string RSA::serialize(struct Key *key) {
  std::string s = std::to_string(key -> exponent) + ',' + std::to_string(key -> modulus);
  return Base64::encode(s.c_str());
}

std::string RSA::serialize(struct Keyring *keys) {
  std::string s = std::to_string(keys -> d.exponent) + ',' + std::to_string(keys -> d.modulus) + ';'
                  + std::to_string(keys -> e.exponent) + ',' + std::to_string(keys -> e.modulus);
  return Base64::encode(s.c_str());
}

void RSA::print(struct Keyring *keyring) {
	printf("Private key:\n Modulus: %lld\n Exponent: %lld\n",
			keyring -> d.modulus,
			keyring -> d.exponent);
	printf("Public key:\n Modulus: %lld\n Exponent: %lld\n",
			keyring -> e.modulus,
			keyring -> e.exponent);
}
