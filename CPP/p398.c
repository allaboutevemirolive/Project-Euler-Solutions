#include <stdio.h>
#define N 10000000
#define M 100

double binomial(int x, int y, int x2) {
    if (y > x)
        return 0;

    double answer = 1.0;
    for (int n = x - y + 1; n <= x; n++) {
        double d = n - x + x2;
        answer *= n / d;
    }

    return answer;
}

double ways[N / M + 100];

int main() {
    for (int i = 1; i <= N / M + 4; i++) {
        double way_1 = M * (binomial(N - i * (M - 1) + M - 2, M - 1, N - 1) - binomial(N - (i * M - 1) + M - 2, M - 1, N - 1));
        double way_2 = binomial(N - i * M + M - 1, M - 1, N - 1);
        ways[i] = way_1 + way_2;
    }

    double answer = 0;

    for (int j = 1; j <= N / M + 4; j++)
        answer += (ways[j] - ways[j + 1]) * j;

    printf("%1.5f\n", answer);
}