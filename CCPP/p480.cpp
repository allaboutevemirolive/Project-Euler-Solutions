#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

char s[111] = "thereisasyetinsufficientdataforameaningfulanswer";

map<pair<vi, int>, ll> dp;

ll DP(vi a, int n) {
    if (n == 0) return 1;

    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    while (a.size() && !a.back()) a.pop_back();

    pair<vi, int> p(a, n);
    ll& res = dp[p];
    res = 1;

    for (int i = 0; i < a.size(); ++i) {
        a[i]--;
        res += DP(a, n - 1);
        a[i]++;
    }

    return res;
}

string word(vi num, int bound, ll pos) {
    if (pos == 1) return "";
    pos--;

    for (int c = 0; c < 26; ++c) if (num[c]) {
        num[c]--;
        ll cnt = DP(num, bound - 1);
        if (cnt < pos) {
            num[c]++;
            pos -= cnt;
            continue;
        }
        string res(1, c + 'a');
        return res + word(num, bound - 1, pos);
    }
}

ll POS(vi num, int bound, string s) {
    if (s.size() == 0) return 1;
    int c0 = s[0] - 'a';
    ll pos = 1;

    for (int c = 0; c < c0; ++c) if (num[c]) {
        num[c]--;
        pos += DP(num, bound - 1);
        num[c]++;
    }
    num[c0]--;
    pos += POS(num, bound - 1, s.substr(1));
    return pos;
}

vi num(26);

ll p(string s) {
    return POS(num, 15, s) - 1;
}

string w(ll p) {
    return word(num, 15, p + 1);
}

int main() {
    for (int i = 0; s[i]; ++i) num[s[i] - 'a']++;
    puts(w(p("legionary") + p("calorimeters") - p("annihilate") + p("orchestrated") - p("fluttering")).c_str());

    return 0;
}