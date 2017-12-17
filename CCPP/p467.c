#include <stdio.h>
#include <stdlib.h>

#define N 10000
#define M 105000
#define Q 1000000007LL

typedef long long int ll;

typedef enum {
    X,
    Y,
    XY
} direction;

typedef struct entry {
    direction dir;
    short len;
} entry;

static char ps[N];
static char cs[N];
static entry state[N + 1][N + 1];

static int digitsum(int n) {
    int r = 0;
    for ( ; n != 0; n /= 10 ) r += n % 10;
    return r;
}

static char droot(int n) {
    while (n >= 10) n = digitsum(n);
    return n;
}

static void makepc(void) {
    char *b = calloc(M + 1, sizeof(char));

    int psi = 0, csi = 0;
    for (int p = 2; p <= M; p++) {
        if (b[p] == 0) {
            if (psi < N) {
                ps[psi] = droot(p);
                psi++;
            }
            for (int q = 2 * p; q <= M; q += p) b[q] = 1;
        } else {
            if (csi < N) {
                cs[csi] = droot(p);
                csi++;
            }
        }
    }

    free(b);
}

static void initstate(void) {
    for (int i = 0; i <= N; i++) {
        state[i][N] = (entry) { X, N - i };
        state[N][i] = (entry) { Y, N - i };
    }
}

static void resolvestate(void) {
    for (int y = N - 1; y >= 0; y--) {
        char b = cs[y];
        for (int x = N - 1; x >= 0; x--) {
            char a = ps[x];
            if (a == b) state[x][y] = (entry) { XY, state[x + 1][y + 1].len + 1 };
            else {
                short nx = state[x + 1][y].len;
                short ny = state[x][y + 1].len;
                if (nx < ny) state[x][y] = (entry) { X, nx + 1 };
                else if (ny < nx) state[x][y] = (entry) { Y, ny + 1 };
                else if (a <= b) state[x][y] = (entry) { X, nx + 1 };
                else state[x][y] = (entry) { Y, nx + 1 };
            }
        }
    }
}

static ll solve(void) {
    ll r = 0;
    int x = 0, y = 0;
    char d;

    while ((x < N) || (y < N)) {
        switch (state[x][y].dir) {
            case X:
                d = ps[x];
                x++;
                break;
            case Y:
                d = cs[y];
                y++;
                break;
            default:
                d = ps[x];
                x++;
                y++;
        }
        r = (10LL * r + (ll)d) % Q;
    }
    
    return r;
}

int main() {
    makepc();
    initstate();
    resolvestate();

    printf("%lld\n", solve());

    return 0;
}
