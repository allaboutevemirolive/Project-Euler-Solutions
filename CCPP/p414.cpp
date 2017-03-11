#include <stdio.h>
#define N 5
#define K 300
#define MOD (1ll*1000000*1000000*1000000)

int base, depth[6*K+3][6*K+3];

int findDepth(int a, int b) {
	if (!depth[a][b]) {
		int h, z[5] = {b ? b - 1 : base - 1, a - (b == 0), base - a, base - b - 1, base - 1};
		#define SWAP(a, b) if (z[a] > z[b]) h = z[a], z[a] = z[b], z[b] = h;
		SWAP(0, 1);
		SWAP(2, 3);
		SWAP(0, 2);
		SWAP(1, 3);
		SWAP(1, 2);
		#undef SWAP
		depth[a][b] = 1 + findDepth(z[4] - z[0], z[3] - z[1]);
	}
	return depth[a][b];
}

int main() {
	long long total = 0, n;
	int k, a, b;
	for (k = 2; k <= K; k++) {
		base = 6 * k + 3;
		for (a = 0; a < base; a++) for (b = 0; b < base; b++) depth[a][b] = 0;
		depth[4 * k + 2][2 * k + 1] = 1;

		for (a = 1; a < base; a++) for (b = 0; b <= a; b++) {
			n = findDepth(a, b);

			if (b == 0) 		total += n * (base - a) * (20 * a - 10);
			else if (b == a)	total += n * (base - a) * (30 * a - 10);
			else				total += n * (base - a) * (120 * (a - b) * b - 20);

			if (total >= MOD) total -= MOD;
		}
		total--;
	}
	printf("total => %lld\n", total);
	return 0;
}
