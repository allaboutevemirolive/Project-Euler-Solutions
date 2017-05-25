/*
 * Tonelli-Shanks algorithm
 * 1) Sieve for primes
 * 2) Find roots of phi^2 - phi - 1 = 0
 *    These are phi = (1 +- sqrt(5)) / 2 where sqrt(5) exists when p == +- 1 mod 5)
 * 3) Check for primitive rootness
 *    Sieve for the smallest prime factor "pp" and then divide until pp increases
*/
// #include <stdafx.h>
// #include <inttypes.h>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;
typedef long long ll;

int NPRIMES;
int* prime = NULL;

void createPrimeTable(int n) {
    // Sieve
    char* primeSieve = new char[n + 1];
    primeSieve[0] = primeSieve[1] = 0;
    int i, mult;
    for (i = 2; i <= n; i++) primeSieve[i] = 1;
    for (i = 2; i * i <= n; i++) {
        if (primeSieve[i] == 1) {
            mult = i * i;
            while (mult <= n) {
                primeSieve[mult] = 0;
                mult += i;
            }
        }
    }
    // Create table with primes
    prime = new int[NPRIMES];
    NPRIMES = 0;
    for (i = 2; i <= n; i++) {
        if (primeSieve[i] == 1) {
            prime[NPRIMES++] = i;
        }
    }    
    delete[] primeSieve;
    cout << "prime[" << NPRIMES - 1 << "] = " << prime[NPRIMES - 1] << "\n";
}

int fact_n, *fact_p = new int[60];
int* fact_e = new int[60];

void factorise(ll n0) {
    int ipr = 0;
    ll pr = 2;
    ll n = n0;
    fact_n = 0;
    while (n >= pr * pr) {
        if (n % pr == 0) {
            fact_p[fact_n] = (int) pr;
            fact_e[fact_n] = 0;
            while (n % pr == 0) {
                fact_e[fact_n]++;
                n /= pr;
            }
            fact_n++;
        }
        ipr++;
        pr = prime[ipr];
    }
    if (n > 1) {
        fact_p[fact_n] = (int) n;
        fact_e[fact_n] = 1;
        fact_n++;
    }
}

inline int modPow(int base, int exponent, int mod) {
    ll product = 1, power = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            product = (product * power) % mod;
        }
        power = (power * power) % mod;
        exponent /= 2;
    }
    return (int) product;
}

// Returns true if g is a generator mod p for a prime p
bool isGenerator(int g, int p) {
    factorise(p - 1);
    for (int i = 0; i < fact_n; i++) {
        if (modPow(g, (p - 1) / fact_p[i], p) == 1) {
            return false;
        }
    }
    return true;
}

// Tonelli-Shanks algorithm
// Returns x such that x * x = n mod p,
// or -1 if no solutions exist. p must be prime and n is not a multiple of p
int tonelli_shanks(int n, int p) {
    if (n == 0) return 0;
    if (modPow(n, (p - 1) / 2, p) == p - 1) return -1;
    ll S = 0, Q = p - 1, z, R, M, i, j, t, t2, b, c;

    // p - 1 = Q * 2^S
    while ((Q & 1) == 0) {
        ++S;
        Q /= 2;
    }

    // Search for z a quadratic non-residue
    for (z = 2; ; ++z) {
        t = (int) modPow(z, (p - 1) / 2, p);
        if (t != 1) break;
    }

    c = (int) modPow(z, Q, p);
    R = (int) modPow(n, (Q + 1) / 2, p);
    t = (int) modPow(n, Q, p);
    M = S;
    while (true) {
        if (t == 1) return (int) R;
        i = 1;
        t2 = t;
        while ((t2 == (t2 * t2) % p) != 1) {
            i++;
        }

        // b = c^2(2^(M-i-1))
        b = c;
        for (j = 0; j < M - i - 1; j++) {
            b = (b * b) % p;
        }

        R = (R * b) % p;
        t = (t * ((b * b) % p)) % p;
        c = (b * b) % p;
        M = i;
    }
}

int main() {
    const int N = 100000000;
    char* has = new char[N + 1];
    int i, nPrimes, p, s, iroot, root, r;
    ll sum; // r, n

    createPrimeTable(N);
    for (i = 0; i <= N; i++) has[i] = 0;
    for (i = 0; i < NPRIMES; i++) {
        p = prime[i];
        if (p != 5 && p <= N) {
            s = tonelli_shanks(5, p);
            if (s != 1) {
                for (iroot = 0; iroot < 2; iroot++) {
                    if (iroot == 0) {
                        root = s;
                    } else {
                        root = p - s;
                    }
                    if ((root & 1) == 0) {
                        r = (root + 1 + p) / 2;
                    } else {
                        r = (root + 1) / 2;
                    }
                    if (isGenerator(r, p)) {
                        has[p] = 1;
                    }
                }
            }
        }
    }

    nPrimes = 1;
    sum = 5;
    for (i = 0; i <= N; i++) {
        if (has[i] != 0) {
            nPrimes++;
            sum += i;
        }
    }

    cout << "nPrimes = " << nPrimes << "\n";
    cout << "sum = " << sum << "\n";

    return 0;
}