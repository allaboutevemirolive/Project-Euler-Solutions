#include <iostream>
#include <set>

using namespace std;
typedef long long ll;

#define N 1000000

set<pair<int,int>> exist;

int gcd(int a, int b) { 
    return b ? gcd(b, a % b) : a; 
}

ll calc(int a, int b, int c) {
	// cos(t*r/(R,r)) = a/c, sin(t*r/(R,r)) = b/c
	int an = a * a - b * b, bn = 2 * a * b, cn = c * c, tmp;
	int n = 2;
	ll sum = 0;
	while (cn <= N/2) {
		int am = a, bm = b, cm = c;
		int m = 1;
		while (m < n) {
			// r = m*d, R-r = n*d
			// cm | R-r, cn | r
			// cm/gcd(cm,n) | d, cn/gcd(cn,m) | d
			int r1 = cm / gcd(cm, n);
			int r2 = cn / gcd(cn, m);
			ll dbase = (ll)r1 * r2 / gcd(r1, r2);
			int dmult = N / dbase / (m + n);
			if (dmult) {
				// x = (R-r)*am/cm + r*an/cn
				// y = \pm((R-r)*bm/cm + r*bn/cn)
				int x = n * dbase / cm * am + m * dbase / cn * an;
				int y = n * dbase / cm * bm - m * dbase / cn * bn;
				int i;
				if (y < 0)
					y = -y;
				for (i = 1; i <= dmult; i++) {
					if (exist.insert(make_pair(i*x, i*y)).second) {
						sum += (y ? 2 : 1) * ((x > 0 ? x : -x) * i + y * i);
					}
				}
			}
			tmp = am * a - bm * b;
			bm = am * b + bm * a;
			am = tmp;
			cm *= c;
			m++;
		}
		tmp = an * a - bn * b;
		bn = an * b + bn * a;
		an = tmp;
		cn *= c;
		n++;
	}
	return sum;
}

int main() {
	ll sum = 0;
	int i, d, m, n;
	// cos(t*r/(R,r)) and sin(t*r/(R,r)) must be rational
	// special cases: cos(t*r/(R,r)) is integer
	// cos(t*r/(R,r))=1: x=R, y=0
	// \sum_{R=3}^N R*floor((R-1)/2)
	sum += (ll)(N/2 + 1) * (N/2) * (N/2 - 1) / 3 * 2 + (ll)((N+1)/2) * ((N-1)/2) * ((N-1)/2 * 4 + 5) / 6;
	// cos(t*r/(R,r))=-1, r/(r,R) is even: x=R-2r, y=0
	// cos(t*r/(R,r))=-1, r/(r,R) is odd, R/(r,R) is odd: x=-(R-2r), y=0
	for (d = 1; d <= N / 3; d *= 2) {
		// r = d*something, R = d*(something odd)
		ll l = (N / d - 1) / 2;
		sum += l * (l + 1) * (2 * l + 1) / 6 * d;
	}
	// cos(t*r/(R,r))=-1, R/(r,R) is even: x=-R, y=0
	for (d = 1; d <= N / 4; d *= 2) {
		// r = d*(something odd), R = 2*d*something
		ll l = N / (2 * d);
		sum += ((l/2) * (l/2 + 1) * (l/2 * 2 + 1) / 3 + ((l+1)/2) * ((l-1)/2) * ((l-1)/2 * 4 + 5) / 6) * 2 * d;
	}
	// cos(t*r/(R,r))=0, 4|r/(r,R): x=R-r, y=\pm r
	// cos(t*r/(R,r))=0, 2||r/(r,R): x=-(R-r), y=\pm r
	// cos(t*r/(R,r))=0, r/(r,R) is odd, R/(r,R) is odd: x=r or x=-r depending on parity of (R-r)/(r,R), y=\pm(R-r)
	for (d = 1; d <= N / 3; d *= 2) {
		// r = d*something, R = d*(something odd)
		ll l = (N / d - 1) / 2;
		sum += l * (l + 1) * (4 * l + 5) / 6 * d * 2;
	}
	// cos(t*r/(R,r))=0, 4|R/(r,R): x=0, y=\pm R
	for (d = 1; d <= N / 4; d *= 2) {
		ll l = (N / (d * 4));
		sum += l * (l + 1) * (2 * l + 1) / 6 * d * 8;
	}
	// cos(t*r/(R,r))=0, 2||R/(r,R): x=0, y=\pm(R-2r)
	for (d = 1; d <= N / 3; d *= 2) {
		ll l = (N / (d * 2) - 1) / 2;
		sum += l * (l + 1) * (l + 2) / 6 * 8 * d;
	}
	// common case: cos(t*r/(R,r)) is not integer
	for (m = 2; m * m * m * m <= N/2; m++)
		for (n = (m % 2) ? 2 : 1; n < m && (m * m + n * n) * (m * m + n * n) <= N/2; n += 2)
			if (gcd(m, n) == 1) {
				int a = m * m - n * n;
				int b = 2 * m * n;
				int c = m * m + n * n;
				sum += calc(a, b, c);
				sum += calc(-a, b, c);
				sum += calc(b, a, c);
				sum += calc(-b, a, c);
			}
	printf("%lld\n", sum);
	return 0;
}