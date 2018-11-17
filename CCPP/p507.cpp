#include <iostream>
#include <vector>

typedef __int128 int128_t;

inline int128_t abs(int128_t x) {
    return x >= 0 ? x : - x;
}

inline int128_t f(int128_t *v, int128_t *w, int128_t k, int128_t l) {
    return abs(v[0]*k, w[0]*l) + abs(v[1]*k + w[1]*l) + abs(v[2]*k + w[2]*l);
}

int128_t S(int128_t *v, int128_t *w) {
    int128_t min_dst = abs(v[0]) + abs(v[1]) + abs(v[2]);
    int128_t min_w = abs(w[0]) + abs(w[1]) + abs(w[2]);

    if (min_w < min_dst) min_dst = min_w;

    for (int j = 0; j <= 2; ++j) {
        if (v[j] == 0) continue;

        int128_t p0 = 0, q0 = 1, p1 = 1, q1 = 0;
        int128_t n = -w[j], d = v[j];
        int128_t e, g;

        for (; ;) {
            int128_t a = n / d;
            int128_t q2 = q0 + a * q1;

            e = p0, p0 = p1, q0 = q1, p1 = e + a * p1, q1 = q2;
            g = n, n = d, d = g - a * d;

            int128_t s = f(v, w, p1, q1);
            if (s < min_dst) min_dst = s;

            if (d == 0) break;
        }
    }

    return min_dst;
}

int main() {
    const int n = 20000000;
    const int mod = 10000000;

    std::vector<int> r(12*n + 1, 0);

    r[0] = 0; r[1] = 0; r[2] = 1;

    for (int i = 3; i <= 12*n; ++i) r[i] = (r[i-1] + r[i-2] + r[i-3]) % mod;

    uint64_t sum = 0;
    
    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (int i = 1; i <= n; ++i) {
        int128_t v[] = {
            r[12 * i - 11] - r[12 * i - 10],
            r[12 * i - 9] + r[12 * i - 8],
            (int64_t) r[12 * i - 7] * r[12 * i - 6]
        };

        int128_t w[] = {
            r[12 * i - 5] - r[12 * i - 4],
            r[12 * i - 3] + r[12 * i - 2],
            (int64_t) r[12 * i - 1] * r[12 * i]
        };
        sum += S(v, w);
    }

    std::cout << "Sum(" << n << ")" << sum << std::endl;

    return 0;
}