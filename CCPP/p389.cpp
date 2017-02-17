#include <cstdio>

const in N = 4 * 6 * 8 * 12 * 20 + 1;
double p[N], q[N];
double prev[N];
double cur[N];

int main() {
	int i, j, k;
	for(i = 1; i <= 4; i++) p[i] = 1. / 4;
	int L = 4;
	int x[] = {6, 8, 12, 20};

	for (int it = 0; it < 4; it++) {
		int M = x[it];
		for (i = 0; i <= L * M; i++) q[i] = prev[i] = 0;
		prev[0] = 1;
		for (j = 1; j <= L; j++) {
			cur[0] = 0;
			for (i = 1; i <= j * M; i++)
				cur[i] = cur[i - 1] + (prev[i - 1] - (i > M ? prev[i - M - 1] : 0)) / M;
			for (i = 0; i <= j * M; i++) {
				prev[i] = cur[i];
				q[i] += cur[i] * p[j];
			}
		}
		L *= M;
		for (i = 0; i <= L; i++) p[i] = q[i];
	}
	double E = 0, E2 = 0;
	for (i = 0; i <= L; i++) {
		E += i * p[i];
		E2 += i * i * p[i];
	}
	double ans = E2 - E * E;
	printf("%.4lf\n", ans);

	return 0;
}