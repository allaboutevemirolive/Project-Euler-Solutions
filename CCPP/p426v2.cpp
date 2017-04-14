#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

ll solve(ll N = 10000000LL) {
	deque<ll> state(N + 2);
	ll s = 290797, ans = 0;

	for (ll k = 0; k <= N; ++k) {
		state[k] = s % 64 + 1;
		s = (s * s) % 50515093;
	}

	state[N + 1] = 50515093;

	for (ll i = 0; i < (N + 2) / 2; ++i) {
		for (ll j = 0; j < state.size() - 1; ++j) {
			if (state[j] <= state[j + 1]) {
				ans += state[j] * state[j];
				if (j > 0) state[j - 1] += state[j + 1] - state[j];
				state.erase(state.begin() + j, state.begin() + j + 2);
				break;
			}
		}
	}
	return ans;
}

int main() {
	cout << solve() << endl;
	return 0;
}
