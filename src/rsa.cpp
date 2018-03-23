#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <math.h>
#include <time.h>
#include "utils.hpp"
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

HASH numerizeString(const char *str) {
  int size = strlen(str);
  HASH r;
	HASH *h = &r;
	for (HASH i = 0; i < size; i++) {
		h[i] = (int)str[i];
	}
  return r;
}

HASH RSA::sign(const char *str, struct Key *k) {
  HASH n = numerizeString(str);
  return sign(n, k);
}

HASH RSA::sign(HASH hash, struct Key *k) {
  return modExp(hash, k -> exponent, k -> modulus);
}

bool RSA::check(HASH hash, const char *control, struct Key *k) {
  HASH n = numerizeString(control);
  return check(hash, n, k);
}

bool RSA::check(HASH hash, HASH control, struct Key *k) {
  return modExp(hash, k -> exponent, k -> modulus) == control;
}

void RSA::print(struct Keyring *keyring) {
	printf("Private key:\n Modulus: %lld\n Exponent: %lld\n",
			keyring -> d.modulus,
			keyring -> d.exponent);
	printf("Public key:\n Modulus: %lld\n Exponent: %lld\n",
			keyring -> e.modulus,
			keyring -> e.exponent);
}
