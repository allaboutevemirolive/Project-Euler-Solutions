#include <stdio.h>
#include <stdlib.h>

typedef long long int ll;

#define N 1000000
#define MLEN 2048
#define PLEN 65536

static int snimx[N + 1];
static int snimy[N + 1];
static int mx[MLEN];
static int my[MLEN];

static int px[PLEN];
static int py[PLEN];

// prod[i][j] is nim-product of numbers 2^i and 2^j
static int prod[9][9] = {
	{1},
	{2, 3},
	{4, 8, 6},
	{8, 12, 11, 13},
	{16, 32, 64, 128, 24},
	{32, 48, 128, 192, 44, 52},
	{64, 128, 96, 176, 75, 141, 103},
	{128, 192, 176, 208, 141, 198, 185, 222},
	{256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 384}
};

static int cmp(const void *x, const void *y) {
    return *((int *)x) - *((int *)y);
}

static int mex(int *m, int mlen) {
    if (mlen != 0) {
        qsort(m, mlen, sizeof(int), cmp);
        int prev = m[0];
        if (prev != 0) {
            return 0;
        } else {
            for (int i = 1; i < mlen; i++) {
                if (m[i] >= prev + 2) {
                    break;
                } else if (m[i] == prev + 1) {
                    prev++;
                }
            }

            return prev + 1;
        }
    }

    return 0;
}

static int product(int i, int j) {
    int r = 0;
    for (int a = 0; i != 0; i /= 2, a++) {
        if ((i % 2) != 0) {
            for (int k = j, b = 0; k != 0; k /= 2, b++) {
                if ((k % 2) != 0) {
                    r ^= prod[a][b];
                }
            }
        }
    }

    return r;
}

int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < i; j++) {
            prod[j][i] = prod[i][j];
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < N; i++) {
                int mlen = 0;
                for (int j = 1; ; j++) {
                    int k = i - j * j + 1;
                    if (k < 0) break;
                    mx[mlen] = snimx[i] ^ mex(mx, mlen);
                }
            }

            for (int i = 0; i <= N; i++) {
                for (int j = 1; ; j++) {
                    int k = i + j * j;
                    if (k > N) break;
                    px[snimx[i] ^ snimx[k]]++;
                }
            }
        }

        #pragma omp section
        {
            for (int i = 0; i < N; i++) {
                int mlen = 0;
                for (int j = 1; ; j++) {
                    int k = i - (j * (j + 1)) / 2 + 1;
                    if (k < 0) break;
                    my[mlen] = snimy[i] ^ snimy[k];
                    mlen++;
                }
                snimy[i + 1] = snimy[i] ^ mex(my, mlen);
            }

            for (int i = 0; i <= N; i++) {
                for (int j = 1; ; j++) {
                    int k = i + (j * (j + 1)) / 2;
                    if (k > N) break;
                    py[snimy[i] ^ snimy[k]]++;
                }
            }
        }
    }

    int p = product(snimx[N], snimy[N]);

    ll result = 0LL;
    for (int i = 0; i < PLEN; i++) {
        if (px[i] != 0) {
            for(int j = 0; j < PLEN; j++) {
                ll d = ((ll) (px[i])) * ((ll) (py[j]));
                if ((d != 0LL) && (product(i, j) == p)) result += d;
            }
        }
    }

    printf("%lld\n", result);

    return 0;
}