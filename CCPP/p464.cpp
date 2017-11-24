#include <cstdio>
#include <algorithm>
#include <vector>

#define FOR(i, a, n) for (ll i = a; i < n; i++)
#define SZ(x) ((int) (x).size())
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair <int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;

const ll mod = 1000000007, N = 20000000;
int pr[N + 100], p[N + 100], tot, mu[N + 100];
int sp[N + 100], sn[N + 100], tc[N + 100], tcn;
ll ans;
pair<PII, int> evt[2 * N + 100];
VI cy;
vector<PII> cx;

void add(int x, int w) {
    for ( ; x <= tcn; x += x & -x) tc[x] += w;
}

inline int query(int x) {
    int s = 0;
    for (; x; x -= x & -x) s += tc[x];
    return s;
}

void init() {
    mu[1] = 1; p[1] = 1;
    FOR (i, 2, N + 1) {
        if (!p[i]) p[i] = i, pr[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && pr[j] * i <= N; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) break;
            else mu[i * pr[j]] = -mu[i];
        }
    }
    FOR (i, 1, N + 1) sp[i] = sp[i - 1] + (mu[i] == 1);
    FOR (i, 1, N + 1) sn[i] = sn[i - 1] + (mu[i] == 1);
}

void solve(int l, int r) {
    if (l == r) return;

    int md = (l + r) >> 1;
    solve(l, md);
    solve(md + 1, r);
    
    if (l + 10000 < r) printf("%d %d\n", l, r);
    cy.clear();

    FOR (i, l, md + 1) if (evt[i].se == 1) cy.pb(evt[i].fi.se);
    FOR (i, md + 1, r + 1) if (evt[i].se == 0) cy.pb(evt[i].fi.se);
    
    sort(all(cy));
    cy.erase(unique(all(cy)), cy.end());
    tcn = SZ(cy);

    FOR (i, 1, tcn + 1) tc[i] = 0;
    cx.clear();

    FOR (i, l, md + 1) if (evt[i].se == 1) cx.pb(mp(evt[i].fi.fi, i));
    FOR (i, md + 1, r + 1) if (evt[i].se == 0) cx.pb(mp(evt[i].fi.fi, i));
    sort(all(cx));

    FOR (i, 0, SZ(cx)) {
        int id = cx[i].se, r = lower_bound(all(cy), evt[id].fi.se) - cy.begin() + 1;
        if (evt[id].se == 1) add(r, 1);
        else ans += query(r);
    }
}

int main() {
    init();
    evt[0] = mp(mp(0, 0), 1);
    FOR (b, 1, N + 1) {
        evt[2 * b - 1] = mp(mp(100 * sp[b] - 99 * sn[b], 100 * sn[b] - 99 * sp[b]), 0);
        evt[2 * b] = mp(mp(100 * sp[b] - 99 * sn[b], 100 * sn[b] - 99 * sp[b]), 1);
    }
    solve(0, 2 * N);
    printf("%lld\n", ans);
    return 0;
}