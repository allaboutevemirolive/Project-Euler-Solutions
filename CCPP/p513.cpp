#include <iostream>
#include <inttypes.h>

using namespace std;
typedef unsigned int64_t u64;

#define L 100000

u64 gcd(u64 a, u64 b) {
    while (b) {
        u64 c = a % b; a = b; b = c;
    }
    return a;
}

int main() {
    u64 s = 0;
#pragma omp parallel for reduction(+ : s) schedule(dynamic,10)
    for (u64 a0 = 3; a0 < L / 2; ++a0)
    for (u64 c0 = (a0 >> 2 & -2) + 2 - (a0 & 1); c0 < a0; c0 += 2) {
        u64 g = gcd(a0, c0);
        u64 b0 = c0 / g, d0 = a0 / g;
        u64 n = a0 / b0;
        u64 c = a0 + b0 * n, d = c0 + d0 * n;
        
        if (b0 & 1 ? c & 1 : d & 1) {
            c += b0;
            d += d0;
        }

        u64 ss = (d0 + a0 - c / 2 - 1) / d0;
        u64 b = (c + d) / 2 - a0;
        u64 dc = b0 + b0; c += dc * ss; if (c > L) continue;
        u64 db = b0 + d0; b += db * ss; if (b > c) continue;
        s += min((L - c) / dc, (c - b) / (db - dc)) + 1;
    }

    std::cout << s;
    return 0;
}