#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef __int128 lll;
typedef long long ll;

#define one ((lll) 1)
#define two ((lll) 2)
#define three ((lll) 3)
#define four ((lll) 4)
#define six ((lll) 6)

#define D 90

typedef struct Triple {
    double value;
    int pw2, pw3;
} Triple;

static int cmp(const void *x, const void *y) {
    double xx = ((Triple *) x)->value;
    double yy = ((Triple *) y)->value;

    return (xx < yy) ? -1 : 1;
}

static short key[90][90];
static void init(void) {
    Triple x[90 * 90];
    for (int pw2 = 0, i = 0; pw2 < D; ++pw2) {
        for (int pw3 = 0; pw3 < D; ++pw3, ++i) {
            x[i] = (Triple) {
                .value = pw2 * log(2) - pw3 * log(3), .pw2 = pw2, .pw3 = pw3
            };
        }
    }

    qsort(x, 90 * 90, sizeof(Triple), cmp);

    for (int i = 0; i < 90 * 90; ++i) {
        key[x[i].pw2][x[i].pw3] = i;
    }
}

static int r = 0;
static void g(lll x, int i) {
    if (i < D - 2) {
        g(two * x, i + 1);
        if ((x % six) == four) g(two * ((x - one) / three), i + 2);
    } else if (i == D - 2) {
        r++;
        if ((x % six) == four) r++;
    } else r++;
}

static lll stack[D];
static int limstack[D];
static void f(lll x, int i, int pw3, int pw2, int c) {
    limstack[i] = key[pw2][pw3];
    stack[i] = x;

    int flag = 0;
    for (int j = 0; j < i - 1; ++j) {
        if ((stack[j] < stack[i]) ^ (limstack[j] < limstack[i])) {
            flag = 1;
            break;
        }
    }

    if (flag) g(x, i);
    else {
        if (i <= D - 2) {
            if (c < 5) f(two * x, i + 1, pw3, pw2 + 1, c + 1);
            if ((x % six) == four) f((x - one) / three, i + 1, pw3 + 1, pw2, 0);
        }
    }
}

static ll fib(int n) {
    ll a = 0, b = 1;
    for ( ; n > 1; --n) {
        ll t = a;
        a = b;
        b += t;
    }

    return b;
}

int main() {
    init();

    f(5, 0, 0, 0, 0);
    printf("%lld\n", fib(D) + r);

    return 0;
}