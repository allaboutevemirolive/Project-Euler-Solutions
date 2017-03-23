#include <cstdio>
#include <string>
#include <map>
using namespace std;
typedef long long ll;

#define n 92

map<string, int> ind;
string id[n];
int cnt = 0;
int num[n][3] = {0};

int get_ind(string s) {
	if (!ind.count(s)) {
		id[cnt] = s;
		ind[s] = cnt++;
	}
	return ind[s];
}

int main() {
	freopen("p418.txt", "rt", stdin);
	int a[n][n] = {0};
	int prev = -1;
	for (int j = 0; j < n; j++) {
		char ids[11], rep[111];
		scanf("%*s%*s%s%s", ids, rep);
		int u = get_ind(ids);
		if (prev >= 0) {
			a[prev][u]++;
		}
		for (int i = 0; rep[i];) {
			if (rep[i] == '.') i++;
			else {
				string s;
				for (; rep[i] && rep[i] != '.'; i++) s+= rep[i];
				if (s[0] <= '3') {
					for (int j = 0; j < s.length(); j++)
						num[u][s[j] - '1']++;
				} else {
					int v = get_ind(s);
					a[prev][v]++;
				}
			}
		}
		prev = u;
	}

	a[prev][prev]++;
	ll d = 1000000000000;
	d -= 8;
	int x[n] = {0};
	x[get_ind("Hf")] = x[get_ind("Sn")] = 1;
	for (; d; ) {
		if (d % 2) {
			int y[n] = {0};

			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					y[i] += a[j][i] * x[j];

			for (int i = 0; i < n; i++)
				x[i] = y[i];
		}

		if (d /= 2) {
			int b[n][n] = {0};
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					for (int k = 0; k < n; k++)
						b[i][j] += a[i][k] * a[k][j];

			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					a[i][j] = b[i][j];
		}
	}

	unsigned res[3] = {0};
	for (int i = 0; i < n; i++)
		if (x[i])
			for (int j = 0; j < 3; j++)
				res[j] += num[i][j] * x[i];

	for (int j = 0; j < 3; j++)
		printf("%u%c", res[j] & ((1 << 30) - 1), j < 2 ? ',' : '\n');

	return 0;
}
