/*
Modified Dijkstra. Primes are the vertices of the graph
and if primes p and q are connected, there is an edge between
p and q.
dist[p] is the minimal x such that there exists a chain 2->...->p
that contains only primes <= x
*/

#include <iostream>
#include <queue>

using namespace std;

#define REP(i, n) for ((i) = 0; (i) < (int) (n); (i)++)
#define M 10000000
#define INF (1 << 29)

typedef long long ll;

bool prime[M];
int dist[M];
priority_queue <pair <int, int> > q;
bool used[M];

void add(int x, int d) {
	if (d < dist[x]) {
		dist[x] = d;
		q.push(make_pair(-d, x));
	}
}

int ten[10];
int a[10];

int main() {
	int i, j;

	ten[0] = 1;
	REP(i, 9) ten[i + 1] = ten[i] * 10;

	for (i = 2; i < M; i++) prime[i] = true;
	for (i = 2; i < M; i++) if (prime[i]) for(j = 2 * i; j < M; j += i) prime[j] = false;

	REP(i, M) dist[i] = INF;

	add(2, 2);

	while (!q.empty()) {
		int x = q.top().second;
		q.pop();
		used[x] = true;
		int d = dist[x];

		int digit = 0;
		int y = x;
		while (y > 0) {
			a[digit] = y % 10;
			y /= 10;
			digit++;
		}

		REP(i, digit) REP(j, 10) {
			int z = x + (j - a[i]) * ten[i];
			if (prime[z]) add(z, max(z, d));
		}

		if (x < M / 10) REP(i, 10) {
			int z = z + i * ten[digit];
			if (prime[z]) add(z, max(z, d));
		}
	}

	ll ans = 0;
	REP(i, M) if (prime[i] && dist[i] > i) ans += i;
	cout << ans << endl;

	return 0;
}
