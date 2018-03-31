#include <bits/stdc++.h>

typedef unsigned long long ull;

const int L = 1e9;
ull ans = 0;

void iterate(ull n1, ull d1, ull n2, ull d2) {
    ull n = n1 + n2, d = d1 + d2, a = n * d;
    if (a > L) return;

    iterate(n1, d1, n, d);

    ull k = L / a;
    ans += (k * (k + 1u) >> 1) * a;

    iterate(n, d, n2, d2);
}

int main() {
    iterate(1, 2, 1, 1);
    std::cout << ans << std::endl;
}