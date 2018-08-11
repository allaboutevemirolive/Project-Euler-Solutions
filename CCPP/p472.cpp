#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

const int MOD = 100000000;

void ADD(int& a, ll b) {
    a = (a + b) % MOD;
}

ll sum(ll a, ll b, int d) {
    if (a > b) swap(a, b);
    assert((b - a) % d == 0);
    
    if (d == 1) {
        ll B = b % (2 * MOD);
        ll A = a % (2 * MOD);
        return (B + A) * (B + 2 * MOD - A + 1) % (2 * MOD) / 2;
    }
    if (d == 2) {
        ll B = b / 2 % MOD;
        ll A = a / 2 % MOD;
        return (B + A) * (B + MOD - A + 1) % MOD;
    }
    return 0;
}

int fastSum(ll N) {
    ll pw[64] = {1};
    int small[11] = {0, 1, 2, 2, 4, 3, 6, 2, 6, 3, 8};
    int res = 0;

    for (int n = 1; n < 64; ++n) pw[n] = 2 * pw[n - 1];
    
    for (int k = 1; k <= N && k <= 10; ++k) res += small[k];

    for (int n = 3; pw[n] + 3 <= N; ++n) {
        for (int k = 1; k < n - 1; ++k) {
            if (pw[n] + pw[k + 1] <= N) {
                ADD(res, 2 * sum(2, pw[k], 2) + pw[k + 1]);
                if (pw[n] + pw[k + 1] == N) return res;
            } else {
                if (pw[n] + pw[k] + pw[k - 1] >= N) {
                    ADD(res, 2 * sum(1, N - pw[n] - pw[k], 1));
                    return res;
                }
                ADD(res, sum(2, pw[k], 2) + pw[k + 1] + 2);
                if (N > pw[n] + pw[k] + pw[k - 1] + 1) {
                    ADD(res, 2 * sum(pw[k - 1], pw[n] + pw[k + 1] + 2 - N, 1));
                }
                return res;
            }
        }
        if (pw[n] + pw[n - 1] + 1 > N) return res;
        
        ll j = min(pw[n - 2], N - pw[n] - pw[n - 1]) % MOD;
        ADD(res, j * (j + 1));

        if (pw[n] + pw[n - 1] + pw[n - 2] >= N) return res;
        ADD(res, pw[n - 1] + pw[n - 2] + 3);

        if (pw[n] + pw[n - 1] + pw[n - 2] + 1 >= N) return res;
        ll x = min(N, pw[n + 1] + 1);
        ADD(res, sum(pw[n - 2] + 2, pw[n + 1] + 4 - x, 1));
        
        if (pw[n + 1] + 2 <= N) ADD(res, 8);
    }
    return res;
}

int main() {
    printf("%d\n", fastSum(1000000000000LL));
    return 0;
}