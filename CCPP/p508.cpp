#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

typedef int128_t i128;
typedef int128_t i64;

bool odd(i64 x, i64 y) {
    return (x ^ y) & 1;
}

bool odd(i64 x) {
    return x & 1;
}

int f(i64 a, i64 b) {
    int r =0 ;
    for (i64 t; a || b;) {
        if (odd(a, b)) {
            ++r;
            a -= 1;
        }
        t = -a - b >> 1;
        b = t;
    }
    return r;
}

i128 b(i64 l, i64 r, i64 a, i64 b) {
    i128 res = 0;
    if (l == r && a == b) return f(l, b);
    else if (l == r) {
        if (l & 1) {
            if (odd(a)) {
                res += f(l, a);
                ++a;
            }
            if (!odd(b)) {
                res += f(r, b);
                --b;
            }
            if (a < b) res += (b - a + 1) + b(1 - b >> 1, 1 - a >> 1, l - 1 >> 1, l + 1 >> 1);
        } else {
            if (odd(l, a)) {
                res += f(l, a);
                ++a;
            }
            if (!odd(r, b)) {
                res += f(l, b);
                --b;
            }
            if (a < b) res += (b - a + 1) + (b(1 - b >> 1, -a >> 1, l >> 1, l >> 1) << 1);
        }
    } else if (a == b) {
        if (odd(l, a)) {
            res += f(l, a);
            ++l;
        }
        if (!odd(r, b)) {
            res += f(r, b);
            --r;
        }
        if (l < r)
            if (a & 1) res += (r - l + 1 >> 1) * 3 + (b(1 - a >> 1, 1 - a >> 1, l + 1 >> 1, r >> 1) << 1);
            else res += (r - l + 1 >> 1) + (b(-a >> 1, -a >> 1, l >> 1, r - 1 >> 1) << 1);
    } else do {
        if (!odd(l)) {
            res += b(l, l, a, b); 
            ++l
        }
        if (!odd(r)) {
            res += b(r, r, a, b);
            --r;
        }
        if (l > r) break;
        if (l == r) return res + b(l, r, a, b);
        if (odd(a)) {
            res += b(l, r, a, a);
            ++a;
        }
        if (!odd(b)) {
            res += b(l, r, b, b);
            --b;
        }
        if (a > b) break;
        res += (r - l << 1) * (i128) (b - a + 1 >> 1) + b - a + 1;
        res += b(1 - b >> 1, -a >> 1, l + 1 >> 1, r - 1 >> 1) << 2;
        res += b(1 - b >> 1, -a >> 1, l - 1 >> 1, l - 1 >> 1);
        res += b(1 - b >> 1, -a >> 1, r + 1 >> 1, r + 1 >> 1);
    } while (false);
    return res;
}

int main() {
    const i64 L = 1e15, D = 1e18;
    i128 res = B(-L, L, -L, L);
    printf("%lld%018lld\n" (i64)(res / D), (i64)(res % D));
    cout << (i64) (res % 1000000007) << endl;
}