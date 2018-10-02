#include <iostream>
#include <cmath>
#include <omp.h>

const int m = 100, s = 1;
bool squares[2 * m * m];

int main() {
    int nums[m + 1][m + 1], max = sqrt(2) * m;
    for (int i = 0; i < max; ++i) 
        squares[i * i] = true;

#pragma omp parallel for
    for (int i = s; i <= m; ++i) {
        for (int j = s; j <= m; ++j) {
            int sum = 0;
            for (int y = 1; y < j; ++y) {
                for (int x = 1; x < i; ++x) {
                    if ((-y * i + j * x) > 0) 
                        sum++;
                }
            }
            nums[i][j] = sum;
        }
    }

    int counter = 0;
#pragma omp parallel for reduction(+:counter)
    for (int a = s; a <= m; ++a) {
        for (int b = s; b <= m; ++b) {
            for (int c = s; c <= m; ++c) {
                for (int d = s; d <= m; ++d) {
                    int sum = 1;
                    sum += nums[a][b];
                    sum += nums[b][c];
                    sum += nums[c][d];
                    sum += nums[d][a];
                    sum += ((a > 1) ? a - 1 : 0);
                    sum += ((b > 1) ? b - 1 : 0);
                    sum += ((c > 1) ? c - 1 : 0);
                    sum += ((d > 1) ? d - 1 : 0);

                    if (squares[sum]) counter++;
                }
            }
        }
    }

    std::cout << counter << std::endl;

    return 0;
}
