#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve() {
    ll sum = 0, delta = 0, s = 0;
    int N = 10000 * 10000;
    vector<ll> tab;

    for (int i = 0; i < N; ++i) {
        tab.push_back(s);
        sum += s;
        s = (s * s + 45) % 1000000007;

        while (tab.size() >= 3) {
            int size = tab.size();
            ll a = tab[size - 1];
            ll b = tab[size - 2];
            ll c = tab[size - 3];
            if (!(b >= a && b >= c)) break;
            tab.resize(size - 3);
            tab.push_back(a - b + c);
        }
    }

    for (int i = 0; i < tab.size(); ++i) {
        cout << "vector elements:\t" << tab[i] << endl;
    }

    cout << endl << "vector sum (s*s + 45) mod 1000000007:\n\t\t\t" << sum << endl;

    int w1, w2;
    w1 = 0;
    w2 = tab.size() - 1;

    int step = 1;
    
    while (w1 <= w2) {
        if (tab[w1] > tab[w2]) {
            delta += tab[w1] * step;
            step = -step;
            w1++;
        } else {
            delta += tab[w2] * step;
            step = -step;
            w2--;
        }
    }

    cout << endl << "delta:\t\t" << delta << endl;
    cout << "answer:\t\t" << (sum + delta) / 2 << endl;
}

int main() {
    solve();
    return 0;
}