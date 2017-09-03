#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)

template <typename T> T gcd(T x, T y) {
    for (T t; x; ) 
    t = x, x = y % x, y = t; 
    return y; 
}

typedef long long i64;

const i64 N = 1e15, LMT = 100;

i64 find(i64 n) {
    i64 g = n * 3;
    FOR (i, 1, sqrt(n)) {
        g += gcd(g, n + i);
        if (g == (n + i) * 3) n += i, i = 0;
    }

    return n;
}

int main() {
    ios_base::sync_with_stdio(false);

    i64 n = 8, g = 13;

    for ( ; n <= N; ) {
        i64 x = find(n);
        cout << n << " " << x - n << endl;
        n = x * 2;
        if (n > N) {
            cout << n + N << endl;
            return 0;
        }
    }

    return 0;
}