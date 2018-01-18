#include <unordered_map>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

constexpr int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

const int N = 1000000, M = 100000, R = 65432;
const int m = M / gcd(M, R), r = R / gcd(M, R);
const ull mo = 61 + ull(1e16);
ull f[m], g[m];

int main() {
    f[1] = 1;
    bitset<N + 1> c;
    for (int p = 2; p <= N; ++p) if (!c.test(p)) {
        for (int j = p + p; j <= N; j += p) c.set(j);
        int u = 0, t;
        for (t = N; t; ) u += t /= p;
        if (M % p == 0) {
            if (gcd(M, R) != gcd(M, R * p)) continue;
            for (t = gcd(M, R); t % p == 0; --u) t /= p;
        }
        copy(f + 1, f + m, g + 1);
        unordered_map<int, int> w;
        for (ull t = p; u--; t = t * p % m) w[t]++;
        for (auto e : w) {
            ull x = e.first, y = e.second;
            for (int i = 1; i < m; ++i) 
                (f[i * x % m] += g[i] * y) %= mo;
        }
    }

    cout << f[r] << endl;

    return 0;
}
