#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>

typedef uint32_t uint;
typedef uint64_t big;

enum : uint {
    N = 10000000, MODULUS_445 = 1000000007
};

struct primefac {
    uint32_t prime;
    int32_t count;
};

uint8_t powers[N + 1];
primefac * factorised[N + 1];
uint mindiv[N + 1];
uint fact[N + 1];
uint inv[N + 1];

uint mod(big a) {
    return a % MODULUS_445;
}

uint mod(uint a) {
    return a % MODULUS_445;
}

uint mul(uint a, uint b) {
    return mod(big(a) * b);
}

uint modinv(uint a) {
    uint ainv = 1;
    uint e = MODULUS_445 - 2;
    while (e > 0) {
        if (e & 1) {
            ainv = mul(ainv, a);
        }
        e >>= 1;
        a = mul(a, a);
    }

    return ainv;
}

void init_inv() {
    fact[0] = fact[1] = 1;
    for (uint i = 2; i <= N; ++i) {
        fact[i] = mul(fact[i - 1], i);
    }
    uint factinv = modinv(fact[N]);
    for (uint i = N; i > 0; --i) {
        inv[i] = mul(fact[i - 1], factinv);
        factinv = mul(factinv, i);
    }
}

uint div(uint a, uint b) {
    if (b <= N) {
        return mul(a, inv[b]);
    } else {
        return mul(a, modinv(b));
    }
}

uint powermod(uint a, uint e) {
    uint p = 1;
    while (e > 0) {
        if (e & 1) {
            p = mul(p, a);
        }
        e >>= 1;
        a = mul(a, a);
    }

    return p;
}

uint inc(uint a) {
    if (a == MODULUS_445 - 1) {
        return 0;
    }

    return a + 1;
}

uint add(uint a, uint b) {
    return mod(a + b);
}

uint sub(uint a, uint b)
{
	return add(a, MODULUS_445 - b);
}

void union_factorlists(primefac *u, const primefac *a, const primefac *b, int a_sign, int b_sign) {
    while (a->prime || b->prime) {
        if (a->prime == b->prime) {
            u->prime = a->prime;
            u->count = a->count * a_sign + b->count * b_sign;
            a++; b++;
        } else if (!b->prime || a->prime && a->prime < b->prime) {
            u->prime = a->prime;
            u->count = a->count * a_sign;
            a++;
        } else {
            u->prime = b->prime;
            u->count = b->count * b_sign;
            b++;
        }
        u++;
        u->prime = u->count = 0;
    }
}

void verify_factorisation(uint n, primefac *pf) {
    uint prod = 0;
    if (n > 0) {
        prod = 1;
        while (pf->prime) {
            uint count = pf->count;
            while (count) {
                prod *= pf->prime;
                count--;
            }
            pf++;
        }
    }

    if (prod != n) {
        printf("factor_table() failed on %d\n", n);
        exit(0);
    }
}

void init_factor_table() {
    for (uint i = 0; i <= N; ++i) {
        mindiv[i] = i;
    }

    uint limit = (uint) sqrt(uint(N));
    for (uint i = 2; i < limit; ++i) {
        if (mindiv[i] == i) {
            for (uint j = i * i; j <= N; j += i) {
                if (mindiv[j] == j) {
                    mindiv[j] = i;
                }
            }
        }
    }

    for (uint i = 0; i <= N; ++i) {
        primefac scratch[32];

        memset(scratch, 0, sizeof(scratch));

        auto *pf = scratch;
        uint n = i;

        if (n == 0) {

        } else if (n == 1) {
            pf->count = 1;
            pf->prime = 1;
            pf++;
        } else {
            while (n > 1) {
                uint d = mindiv[n];
                uint count = 0;
                while (n % d == 0) {
                    n = n / d;
                    count++;
                }

                if (count) {
                    pf->count = count;
                    pf->prime = d;
                    pf++;
                }
            }
        }

        pf->count = pf->prime = 0;
        pf++;

        uint numfacs = (uint) (pf - scratch);
        uint bytes = numfacs * sizeof(*pf);
        memcpy(factorised[i] = (primefac*) malloc(bytes), scratch, bytes);
    }
}

uint solve() {
    uint answer = 0;
    uint delta = 1;

    init_inv();
    init_factor_table();

    for (uint i = N, j = 1; i >= j; --i, ++j) {
        primefac i_over_j[16 + 1];
        union_factorlists(i_over_j, factorised[i], factorised[j], 1, -1);

        for (const auto *pf = i_over_j; pf->prime; ++pf) {
            uint old_count = powers[pf->prime];
            uint new_count = powers[pf->prime] += pf->count;
            if (pf->prime != 1 && old_count != new_count) {
                if (old_count != 0) {
                    uint leaving = inc(powermod(pf->prime, old_count));
                    delta = div(delta, leaving);
                }
                if (new_count != 0) {
                    uint entering = inc(powermod(pf->prime, new_count));
                    delta = mul(delta, entering);
                }
            }
        }

        answer = add(answer, delta);
    }

    answer = sub(mul(answer, 2), delta);
    answer = sub(answer, powermod(2, N));
    answer = add(answer, 2);
}

int main() {
    uint answer = solve();
    printf("Answer = %d\n", answer);

    return 0;
}