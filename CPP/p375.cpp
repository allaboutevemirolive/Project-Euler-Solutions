#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define car first
#define cdr second
#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)

typedef long long int64;

const int MOD = 50515093, N = 2000000000;
const int64 M = 1000000033;

pair<int, int> S[MOD + 1];

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);

    int s = 290797, top = 0; int64 ans = 0;
    S[++top] = make_pair(0, 0);

    FOR (i, 1, N + 1) {
        if (i > N) s = 0;
        s = (int64) s * s % MOD;
        for (; top && S[top].car >= s; --top) {
            ans += (int64) (i - S[top].cdr) * (S[top].cdr - S[top - 1].cdr) % M * S[top].car % M;
        }
        S[++top] = make_pair(s, i);
    }

    cout << M << " " << ans % M << endl;

    return 0;
}