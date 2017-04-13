#include <iostream>
#include <vector>
#include <algorithm>

#define LIM 10000000

int par[10000005];

int find(int x) {
	return par[x] == x ? x : par[x] = find(par[x]);
}

void unite(int x, int y) {
	par[find(x)] = find(y);
}

bool isprime[10000005];

int toInt(std::string &s) {
	int n = 0;
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		n *= 10, n += (*it) - '0';
	}
	return n;
}

void connect(int n) {
	std::string s;
	int n_ = n;
	while (n > 0) s += '0' + n % 10, n /= 10;
	std::reverse(s.begin(), s.end());

	for (int pos = 0; pos < (int) s.size(); pos++) {
		for (int d = 0; d < 10; d++) {
			std::string t (s);
			t[pos] = '0' + d;
			int y = toInt(t);
			if (pos == 0 and d == 0) continue;
			if (isprime[y] and y < n_)
				unite(n_, y);
		}
	}

	if (s.size() >= 2 and s[1] != '0') {
		std::string s2 = s.substr(1);
		int v = toInt(s2);
		if (v != 0 and isprime[v]) unite(n_, v);
	}
}

int main() {
	for (int i = 1; i < LIM; i++) {
		par[i] = i, isprime[i] = true;
		isprime[1] = isprime[0] = false;
	}

	for (int p = 2; p <= 10000; p++)
		if (isprime[p])
			for (int q = p * p; q < LIM; q += p)
				isprime[q] = false;

	long long answer = 0;
	for (int i = 1; i < LIM; i++) {
		if (isprime[i]) {
			connect(i);
			if (find(i) != find(2))
				answer += i;
		}
	}
	std::cout << answer << std::endl;
}
