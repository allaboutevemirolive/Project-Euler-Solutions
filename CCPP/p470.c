#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 20

double r(int n, char d[], double c) {
    double result = 0, cur = 0, expect = 0, e2;
    int i;
    for ( ; ; ) {
        cur -= c;
        e2 = 0;
        for (i = 0; i < n; ++i) {
            if (d[i] > expect)
                e2 += d[i];
            else
                e2 += expect;
        }
        e2 /= n;
        expect = e2;
        if (result < cur + expect)
            result = cur + expect;
        if (result > cur + d[n - 1])
            return result;
    }
}

int main() {
    int c, i, j, k, x, d;
    double matrix[N][N + 1], res[N], sum = 0;

    for (d = 4; d <= N; ++d) {
        for (c = 0; c <= N; ++c) {
            memset(matrix, 0, sizeof(matrix));
            
            for (x = 1; x < (1 << d); ++x) {
                char dice[N + 1];
                int i, n = 0;
                for (i = 0; i < d; ++i)
                    if (x & 1 << i)
                        dice[n++] = i + 1;
                matrix[n - 1][d] += c == 0 ? dice[n - 1] : r(n, dice, c);
            }

            for (i = 0; i < d; ++i) {
                matrix[i][i] = 1;
                if (i)
                    matrix[i][i - 1] = (double) i / d - 1;
                if (i < d - 1)
                    matrix[i][i + 1] = -(i + 2.0) / d;
            }

            for (i = 0; i < d; ++i) {
                double tmp;
                k = i;
                
                for (j = i + 1; j < d; ++j)
                    if (fabs(matrix[k][i]) < fabs(matrix[j][i]))
                        k = j;

                if (fabs(matrix[k][i]) < 1e-10)
                    break;

                for (j = 0; j <= d; ++j)
                    tmp = matrix[i][j], matrix[i][j] = matrix[k][j], matrix[k][j] = tmp;

                for (k = i + 1; k < d; ++k) {
                    tmp = matrix[k][i] / matrix[i][i];
                    for (j = 0; j <= d; ++j)
                        matrix[k][j] -= tmp * matrix[i][j];
                }
            }

            if (i < d) {
                printf("Error. Rank = %d < %d\n", i, d);
                return 1;
            }

            sum += matrix[d - 1][d] / matrix[d - 1][d - 1];
            printf("S(%d, %d) = %lf\n", d, c, matrix[d - 1][d] / matrix[d - 1][d - 1]);
        }
    }
    printf("%lf\n", sum);
    return 0;
}
