#include <cstdio>
#include <vector>
#include <string.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int P = 6;
const int P2 = 1 << P;
const int P21 = 1 << (P - 1);

bool isPalindrome(int* L, int* R) {
    int* i = L;
    int* j = R - 1;
    for ( ; i < j; i++, j--)
        if (*i != *j) return false;
    return true;
}

bool isPalindrome(int mask) {
    int a[P];
    for (int i = 0; i < P; i++)
        a[i] = (mask & 1 << i) > 0;
    return isPalindrome(a, a + P - 1) || isPalindrome(a, a + P) || isPalindrome(a + 1, a + P);
}

bool isPalindrome(int mask, int n) {
    int a[P];
    for (int i = 0; i < P; i++)
        a[i] = (mask & 1 << i) > 0;
    return isPalindrome(a, a + n);
}

bool palindrome[P2];
pair<int, vi> calculatePeriods(int MOD) {
    int sdp = 0, pw2 = 1, per = 0;
    int dp[P2] = { 0 };
    vi ns;

    for (int n = P - 1; ; n++) {
        int newdp[P2];
        for (int mask = 0; mask < P2; mask++) {
            int& cur = newdp[mask];
            if (n > P) {
                if (palindrome[mask]) cur = pw2;
                else {
                    cur = dp[mask / 2] + dp[mask / 2 + P21];
                    if (cur >= MOD) cur -= MOD;
                }
            } else if (n == P - 1) {
                cur = mask < P21 && isPalindrome(mask, P - 1);
            } else if (n == P) {
                cur = palindrome[mask];
            }
            sdp += cur;
            if (sdp >= MOD) sdp -= MOD;
        }

        if (sdp == 0) {
            ns.push_back(n);
            int k = ns.size() - 1;
            if (k >= 4) {
                if (ns[k] - ns[k - 1] == ns[3] - ns[2] &&
                        ns[k - 1] - ns[k - 2] == ns[2] - ns[1] &&
                        ns[k - 2] - ns[k - 3] == ns[1] - ns[0]) {
                    per = ns[k - 3] - ns[0];
                    ns.pop_back();
                    ns.pop_back();
                    ns.pop_back();
                    ns.pop_back();
                    break;
                }
            }
        }

        memcpy(dp, newdp, 4 * P2);
        if (n >= P) pw2 = pw2 * 2 % MOD;
    }
    
    return make_pair(per, ns);
}

ll inv(ll a, ll m) {
    ll x0 = 1, x1 = 0;
    ll b = m;
    while (b > 0) {
        ll q = a / b;
        
        ll c = a - q * b;
        a = b;
        b = c;

        ll x = x0 - q * x1;
        x0 = x1;
        x1 = x;
    }
    return x0 < 0 ? x0 + m : x0;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

ll m1 = 1;
vl r1s(1, 0);

ll calc(ll n) {
    ll res = 0;
    for (int i = 0; i < r1s.size(); i++) {
        ll r = r1s[i];
        res += (n + m1 - r) / m1;
    }
    
    return res;
}

int main() {
    for (int mask = 0; mask < P2; mask++)
        palindrome[mask] = isPalindrome(mask);
    int mods[3] = { 9, 1997, 4877 };
    for (int h = 0; h < 3; h++) {
        pair<int, vi> p = calculatePeriods(mods[h]);
        int m2 = p.first;
        vi r2s = p.second;
        vl R1s;
        int d = gcd(m1, m2);
        int M1 = m1 / d, M2 = m2 / d;
        int INV = inv(M1, M2);
        for (int i = 0; i < r1s.size(); i++)
            for (int j = 0; j < r2s.size(); j++) {
                int r1 = r1s[i];
                int r2 = r2s[j];
                if ((r2 - r1) % d) continue;
                ll y = ll((r2 - r1) / d) * INV % M2;
                if (y < 0) y += M2;
                R1s.push_back(m1 * y + r1);
            }
        r1s = R1s;
        m1 *= m2 / d;
    }
    printf("%lld\n", calc(1000000000000000000LL));
}