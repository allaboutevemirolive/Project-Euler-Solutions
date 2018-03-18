#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

static mpz_t t, max, n1, n2;

void print_time() {
    static char buf[32];
    static time_t t;
    time(&t);
    strftime(buf, sizeof(buf), "%F %T", localtime(&t));
    fprintf(stderr, "%s| ", buf);
}

void gcd(mpz_t a, mpz_t b) {
    for ( ; mpz_sgn(b) != 0; mpz_set(a, b), mpz_set(b, t))
        mpz_tdiv_r(t, a, b);
}

void set(mpz_t z, long x, int y) {
    mpz_set_si(z, x);
    mpz_mul_si(z, z, x);
    mpz_mul_si(z, z, x);
    mpz_add_ui(z, z, (unsigned long) y);
}

long G(int a, int b) {
    long a3 = a * a * a, z = a * (a3 * a3 + 27L * b * b), i = 0;
    mpz_set_si(max, 0);
    for (long n = 0; n <= z; ++n) {
        set(n1, n, b);
        set(n2, n + a, b);
        gcd(n1, n2);
        if (mpz_cmp_si(n1, z) == 0) return n;
        if (mpz_cmp(n1, max) <= 0) continue;
        mpz_set(max, n1);
        i = n;
    }
    return i;
}

void f(int a, int b, int k, int m) {
    long v = 0;
    print_time();
    fprintf(stderr, "(a:%d, b:%d, m:%d, k:%d)\n", a, b, m, k);
    for (int i = 1; i <= a; ++i) {
        print_time();
        frpintf(stderr, "%d:", i);
        for (int j = 1; j <= b; ++j) {
            if (j % m != k) continue;
            v += G(i, j);
            fprintf(stderr, " %d", j);
        }
        fprintf(stderr, " (%ld)\n", v);
    }
    print_time();
    fprintf(stderr, "%ld\n", v);A
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    int a = 18, b = 1900, m = atoi(argv[1]), k = atoi(argv[2]);
    mpz_inits(t, max, n1, n2, 0);
    f(a, b, k, m);
    mpz_clears(t, max, n1, n2, 0);
    return 0;
}