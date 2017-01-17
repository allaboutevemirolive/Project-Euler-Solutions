#include <iostream>
#include <bitset>
#include <iomanip>
#include <cmath>
#include <cstring>

using namespace std;

#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)

typedef long double real;

const int P = 20, N = P * 100 + 1;

typedef real mat[N][N];

int cb[20][20];
mat G, U, t, w;

void matmul(mat a, mat b, mat c, int L) {
    memset(t, 0, sizeof(t));
    FOR(i, 0, N - 1) {
        FOR(j, 0, N - 1) {
            w[i][j] = b[j][i];
        }
    }

    FOR(i, 0, L - 1) {
        real *p = a[i];
        FOR(k, 0, N - 1) {
            real *q = w[k];
            FOR(j, 0, N - 1) {
                t[i][k] += p[j] * q[j];
            }
        }
    }
    memcpy(c, t, sizeof(t));
}

bool check(int x) {
    if (x < 100) return true;
    return x % 1000 % 111 != 0 && check(x / 10);
}

int main() {
    ios_base::sync_with_stdio(false);
    cerr << setprecision(20) << endl;

    FOR(i, 0, 10) {
        FOR(j, 0, i) {
            cb[i][j] = j ? cb[i - 1][j - 1] + cb[i - 1][j] : 1;
        }
    }
    FOR(i, 0, 9) {
        FOR(j, 0, 9) {
            FOR(k, 0, 9) {
                if (i == j && j == k) continue;
                FOR(u, 1, P) {
                    FOR(v, u, P) {
                        G[(v - 1) * 100 + i * 10 + j][(u - 1) * 100 + j * 10 + k] += 1.0 * cb[v - 1][u - 1] * pow(-k, v - u) / pow(10, v);
                    }
                }
            }
        }
    }
    FOR(i, 0, 100 - 1) G[i][N - 1] = 1;
    G[N - 1][N - 1] = 1;

    FOR(i, 1, 9) {
        FOR(j, 0, 9) {
            FOR(t, 1, P) {
                U[0][(t - 1) * 100 + i * 10 + j] += 1 / pow(i * 10 + j, t);
            }
        }
    }
    FOR(i, 1, 9) {
        U[0][N - 1] += 1.0 / i;
    }

    const int T = 1000;

    FOR(i, 1, T - 1) {
        matmul(U, G, U, 1);
        cerr << i << " " << U[0][N - 1] << endl;
        matmul(G, G, G, N);
    }

    cerr << U[0][N - 1] << endl;

    return 0;
}