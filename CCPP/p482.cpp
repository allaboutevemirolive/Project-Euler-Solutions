#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;

vector<vector<ll> > reg(1000000);

void find_triads(ll a, ll b, ll c) {
    if (c > 3400000) return;

    for (ll m = 1; m * a < 1000000; ++m)
        reg[a * m].push_back(b * m);
    for (ll m = 1; m * b < 1000000; ++m)
        reg[b * m].push_back(a * m);

    find_triads(2 * c - 2 * b + a, 2 * c - b + 2 * a, 3 * c - 2 * b + 2 * a);
    find_triads(2 * c + 2 * b + a, 2 * c + b + 2 * a, 3 * c + 2 * b + 2 * a);
    find_triads(2 * c + b - 2 * a, 2 * c + 2 * b - a, 3 * c + 2 * b - 2 * a);
}

int main() {
    find_triads(3, 4, 5);
    ll sum = 0;
    for (ll r = 1; r < 1000000; ++r) {
        if (r % 1000000 == 0)
            cout << r << endl;
        vector<ll> legs = reg[r];
        int sz = legs.size();
        for (int i = 0; i < sz; ++i) {
            for (int j = i; j < sz; ++j) {
                ull num = r * r * (legs[i] + legs[j]);
                ull den = legs[i] * legs[j] - r * r;

                if (den <= 0) continue;
                if (num % den) continue;
                ll z = num / den;
                if (z < legs[j]) continue;
                if (z < legs[i]) continue;
                ll hh = z * z + r * r;
                ll sq = sqrt(hh + 0.1);
                if (sq * sq != hh) continue;
                den = legs[i] + legs[j] + z;
                if (den > 5000000) continue;
                sum += 2 * den;
                sum += sqrt(legs[i] * legs[i] + r * r + 0.1);
                sum += sqrt(legs[j] * legs[j] + r * r + 0.1);
                sum += sqrt(z * z + r * r + 0.1);
            }
        }
    }
    cout << sum << endl;

    return 0;
}