#include <cstdio>
#include <vector>
using namespace std;

// My initial approach was to generate Heronian trianges and check the formula R = abc / 4P
// but obviously there will be problems because the triangles aren't primitive GCD(a, b, c) > 1

// If I assume GCD(a, b, c) = 1 then I can brute-force my search  up to the R value and later 
// multiply by the right factor to correct it

// Although if I focus on the primes and mutual common factors of a, b and c then I can assign 
// them to a, b, c based on their generating factors. This way I can reduce my search space
// significantly.

const int n = 1e7, N = n + 10;

struct node {
    long x, y, z;
};

vector<node> G[N];

long GCD(long a, long b) {
    if (b) return GCD(b, a % b);
    else return a;
}

long LCM(long a, long b) {
    return a / GCD(a, b) * b;
}

int main() {
    long s = 0;
    for (long u = 1; u * u <= n; ++u) {
        for (long v = 1; v < u && u * u + v * v <= n; ++v) {
            if (GCD(u, v) == 1 && (u - v) % 2 != 0) {
                long a = u * u - v * v;
                long b = 2 * u * v;
                long c = u * u + v * v;

                if (c <= n) {
                    ++s;
                    G[c].push_back((node) {a, b, c});
                    G[c].push_back((node) {b, a, c});
                }
            }
        }
    }

    printf("s = %ld\n", s);
    long ans = 0;

    long cnt = 0, last = 1;
    for (int d = 1; d <= n; ++d) {
        vector<node> F;
        for (int i = 1; i * d <= n; ++i) {
            for (auto x : G[i * d]) {
                F.push_back(x);
            }
        }

        if (d >= last) {
            printf("%d: %d\n", d, (int) F.size());
            last = last * 1.5 + 1;
        }

        for (auto a : F) {
            for (auto b : F) {
                if (a.z * b.z > d * n) break;
                long gz = GCD(a.z, b.z);
                if (gz != d) continue;

                long x = a.x * b.z;
                long y = b.x * a.z;
                long z = a.x * b.y + a.y * b.x;

                if (x <= y && y <= z) {
                    long r = a.z * b.z;
                    long g = GCD(GCD(a.z, b.z), z);

                    if (g != 1) {
                        printf("%ld %ld %ld r = %ld, g = %ld\n", x, y, z, r, g);
                        x /= g, y /= g, z /= g, r /= g;
                    }

                    long m = n / r;
                    if (m > 0) {
                        ans += m * (m + 1) / 2 * r;
                        cnt += 1;
                    }
                }
            }
        }
    }

    printf("ans = %ld, cnt = %ld\n", ans, cnt);

    return 0;
}
