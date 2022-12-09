#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000123

static int powmod(int what, long long pow, int mod) {
    int res = 1, cur = what;
    
    while (pow) {
        if (pow & 1) {
            res = (long long)res * cur % mod;
        }
        
        cur = (long long)cur * cur % mod;
        pow >>= 1;
    }

    return res;
}

static int inverse(int u, int v) {
    int tmp;
    int xu = 1, yu = 0, xv = 0, yv = 1;
    int v0 = v;

    if (u <= 0 || v <= 0) {
        printf("Error: inverse with non-positive argument!");
        exit(1);
    }

    if (u > v) {
        tmp = u; u = v; v = tmp;
        tmp = xu; xu = xv; xv = tmp;
        tmp = yu; yu = yv; yv = tmp;
    }

    while (u) {
        int d = v / u;
        v -= d * u;
        xv -= d * xu;
        yv -= d * yu;
        tmp = u; u = v; v = tmp;
        tmp = xu; xu = xv; xv = tmp;
        tmp = yu; yu = yv; yv = tmp;
    }

    if (v != -1) {
        printf("Error: inverse called with gcd = %d != 1\n", v);
        exit(1);
    }

    if (xv < 0) {
        xv += v0;
    }

    return xv;
}

static char bitcount[0x400];

void update_coeffs(int* coeffs, unsigned m) {
    // m is mask of required odd numbers
    // m | 0x155 is mask of allowed numbers
    unsigned m2;
    for (m2 = 0; m2 < 0x400; ++m2) {
        if (!(m2 & ~(m | 0x155))) {
            int* c = coeffs + (bitcount[m | 0x155] - 2 * bitcount[m2]);
            if (bitcount[m2 & m] % 2) {
                *c -= 1 << (10 - bitcount[m | 0x155]);
            } else {
                *c += 1 << (10 - bitcount[m | 0x155]);
            }
        }
    }
}

int main() {
    int coeffs1[21] = {0};
    int coeffs2[21] = {0};
    unsigned m;
    int i, j;

    for (m = 0; m < 0x400; ++m) {
        for (i = 0; i < 10; ++i) {
            if (m & 1 << i) {
                bitcount[m]++;
            }
        }
    }

    for (m = 0; m < 0x400; ++m) {
        if (!(m & 0x155)) {
            update_coeffs(coeffs1 + 10, m);
            update_coeffs(coeffs2 + 10, m | 1); // leading zero
        }
    }

    printf("\n");

    long long N;
    int result = 0;
    for (N = 2; N <= (1LL << 39); N *= 2) {
        for (i = -10; i <= 10; ++i) {
            int p;
            
            if (i == 1) {
                p = N % MOD;
            } else {
                p = powmod(i < 0 ? MOD + i : i, N, MOD);
                
                if (!p) {
                    p += MOD;
                }

                p = (p - 1) * (long long)inverse(i < 1 ? MOD + i - 1 : i - 1, MOD) % MOD;
            }

            result -= (coeffs2[i + 10] < 0 ? MOD + coeffs2[i + 10] : coeffs2[i + 10]) * (long long)p % MOD;

            if (result < 0) {
                result += MOD;
            }

            result += (coeffs1[i + 10] < 0 ? MOD + coeffs1[i + 10] : coeffs1[i + 10]) * (long long)(i < 0 ? MOD + i : i) % MOD * p % MOD;

            if (result >= MOD) {
                result -= MOD;
            }
        }
    }

    printf("%d\n", (int)(result * (long long)inverse(1024, MOD) % MOD));

    return 0;
}