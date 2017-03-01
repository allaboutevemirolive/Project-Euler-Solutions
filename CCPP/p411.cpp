#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

typedef pair<int, int> PII;

inline void MAX(int &a, int b) {
	if (a < b) a = b;
}
#define N 25000000

int maxf[N];

void add (int n, int x, int val) {
	for (; x <= n; x += x & -x) {
		MAX(maxf[x], val);
	}
}

int get (int n, int x) {
	int mx = 0;
	for (; x > 0; x -= x & -x) {
		MAX(mx, maxf[x]);
	}

	return mx;
}

PII a[2*N];
int calc(int n) {
	int len = 0;
	int x = 1, y = 1;
	PII b[30];
	int blen = 0;
	for (int k = 0; k <= 2 * n; k++) {
		a[len++] = make_pair(x, y + 1);
		if (blen < 30) {
			b[blen++] = make_pair(x, y);

			if (blen == 30) {
				sort(b, b + blen);
				blen = unique(b, b + blen) - b;
			}
		} else {
			int j = lower_bound(b, b + blen, make_pair(x, y)) - b;
			if (j < blen && b[j] == make_pair(x, y)) break;
		}
		x = 2 * x % n;
		y = 3 * y % n;
		if (x == 1 && y == 1) break;
	}
	sort(a, a + len);
	len = unique(a, a + len) - a;
	memset(maxf, 0, 4 * (n + 1));

	for (int i = 0; i < len; i++) {
		int mx = get(n, a[i].second) + 1;
		add(n, a[i].second, mx);
	}

	return get(n, n);
}

int main() {
	int ans = 1;
	for (int k = 2; k <= 30; k++) {
		ans += calc(k * k * k * k * k);
	}

	cout << ans << endl;

	return 0;
}
