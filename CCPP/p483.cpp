#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;
typedef long double ld;

#define A first
#define B second

ll gcd(ll a, ll b) {
    return a ? gcd(b % a, a) : b;
}

bool prime[2000];
ll primepow[2000];

ld g(ll N) {
    for (ll i = 1; i <= N; ++i) {
        prime[i] = true;
        primepow[i] = 1;
    }
    prime[1] = false;
    for (ll i = 1; i <= N; ++i) {
        if (prime[i]) {
            for (ll j = i; j <= N; j *= i) primepow[j] = i;
            for (ll j = i + i; j <= N; j += i) prime[j] = false;
        }
    }

    map<pair<ll, ll>, ld> dp;
    dp[make_pair(0LL, 1LL)] = 1;

    for (ll v = N; v > 0; --v) {
        map<pair<ll, ll>, ld> ndp;
        
        for (auto it : dp) {
            ll s = it.first.first;
            ll g = it.first.second;
            ld num = it.second;

            auto state = make_pair(s, (g % v == 0) ? g / primepow[v] : g);
            if (!ndp.count(state)) ndp[state] = num;
            else ndp[state] += num;

            ll m = v / gcd(g, v);
            g *= m;
            assert(g >= it.first.second);
            g /= primepow[v];

            num *= m * m;

            for (ll c = 1; v + s <= N; ++c) {
                s += v;
                num /= v;
                num /= c;

                state = make_pair(s, g);
                if (!ndp.count(state)) ndp[state] = num;
                else ndp[state] += num;
            }
        }
        dp = ndp;
    }
    ld res = 0;
    for (auto it : dp) {
        if (it.first.first == N) {
            res += it.second;
        }
    }

    return res;
}

int main() {
    cerr << scientific << setprecision(10-1) << '\n';
    cout << scientific << setprecision(10-1) << '\n';

    cerr << g(3) << '\n';
    cerr << g(5) << '\n';
    cerr << g(20) << '\n';
    cout << g(350) << '\n';

    return 0;
}