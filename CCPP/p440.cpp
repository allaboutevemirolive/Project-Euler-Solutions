#include <cstdio>

#define MOD 987898789

typedef long long ll;

struct Matrix {
    int _[2][2];
    Matrix() {}
    Matrix(int a00, int a01, int a10, int a11) {
        _[0][0] = a00;
        _[0][1] = a01;
        _[1][0] = a10;
        _[1][1] = a11;
    }
};

void operator*=(Matrix &a, Matrix b) {
    Matrix c;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c._[i][j] = (ll(a._[i][0]) * b._[0][j] + ll(a._[i][1]) * b._[1][j]) % MOD;
        }
    }
    a = c;
}

Matrix powmod(Matrix a, int n) {
    Matrix p(1, 0, 0, 1);
    for ( ; n; ) {
        if (n % 2) p *= a;
        if (n /= 2) a *= a;
    }
    
    return p;
}

int gcd(int a, int b) {
    int c;
    while (b) {
        c = a % b, a = b, b = c;
    }

    return a;
}

int main() {
    const int L = 2000;
    int s[L + 1] = {0};
    for (int c = 1; c <= L; c++) {
        Matrix a(10, 1, 1, 0);
        for (int d = 1; d <= L; d++) {
            a = powmod(a, c);
            s[d] = (s[d] + 10LL * a._[1][0] + a._[1][1]) % MOD;
        }
    }

    int s2 = 0;
    for (int c = 1; c <= L; c++) {
        s2 += c % 2 ? 10 : 1;
    }

    int ans = 0;
    for (int a = 1; a <= L; a++) {
        for (int b = 1; b <= L; b++) {
            int d = gcd(a, b);
            if (a / d % 2 == 0 || b / d % 2 == 0) {
                ans = (ans + s2) % MOD;
            } else {
                ans = (ans + s[d]) % MOD;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}