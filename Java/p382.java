/**
 * Created by aa on 23 January 2017.
 *
 * Condition for forming a polygon is that the longest side is smaller
 * than the sum of others.
 *
 * So S_n > ∑ Si,  i ≤ n - 3
 * Therefore to form a polygon with S_n as largest, the subset must
 * contain S_(n-1) or S_(n-2) or both.
 * Define V(n) as number of subsets forming a polygon containing S_n but not S_(n-1).
 * Define W(n) as number of subsets forming a polygon containing S_n and S_(n-1).
 * 
 * For V(n) there are 2^(n-5) - 1 subsets containing S_(n-2), S_(n-3) and S_(n-4)
 *          there are V(n - 4) + W(n - 4) subsets containing S_(n-2), S_(n-3) but not S_(n-4)
 *          there are V(n-3) subsets containing S_(n-2), S_(n-4) but not S_(n-3)
 *          
 * For W(n) there are 2^(n-5) subsets containing S_(n-1) and S_(n-2)
 *          there are 2^(n-4) - 1 subsets containing S_(n-1), S_(n-3) but not S_(n-2)
 *          there are V(n - 3) + W(n - 3) subsets containing  S_(n-1) but not S_(n-2), S_(n-3)
 *          
 * V(n) = 2^(n-5) - 1 + V(n - 4) + W(n - 4) + V(n - 3)
 * W(n) = 2^(n-3) + 2^(n-4) - 1 + V(n-3) + W(n-3)
 * f(n) = f(n - 1) + V(n) + W(n)
 * 
 * Used matrix power to compute f(10^18) from recursive formula.
 *
 */
public class p382 {
    private final static long MOD = 1000000000L;
    private static final long N = 1000000000000000000L;

    private static long[] matrixMultiply(long[][] a, long[] x) {
        int n = x.length;
        long[] y = new long[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                y[i] = (y[i] + a[i][j] * x[j]) % MOD;
            }
        }

        return y;
    }

    private static long[][] matrixMultiply(long[][] a, long[][] b) {
        int rows = a.length;
        int cols = b.length;
        int n = a[0].length;
        long[][] c = new long[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < n; k++) {
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
                }
            }
        }

        return c;
    }

    private static long[][] matrixPower(long[][] a, long m) {
        int n = a.length;
        long[][] b = new long[n][n];

        for (int i = 0; i < n; i++) b[i][i] = 1;

        for ( ; m != 0; m >>>= 1) {
            if ((m & 1) == 1)
                b = matrixMultiply(b, a);
        }

        return b;
    }

    public static void main(String[] args) {
        long[][] A = new long[11][11];

        A[0][0] = 1;
        A[0][3] = 1 + 1;
        A[0][4] = 1;
        A[0][7] = 1;
        A[0][8] = 1;
        A[0][9] = 1 + 4 + 2;
        A[0][10] = MOD - 1 - 1;
        A[1][3] = 1;
        A[1][4] = 1;
        A[1][8] = 1;
        A[1][9] = 1;
        A[1][10] = MOD -1;
        A[2][1] = 1;
        A[3][2] = 1;
        A[4][3] = 1;
        A[5][3] = 1;
        A[5][7] = 1;
        A[5][9] = 4 + 2;
        A[5][10] = MOD - 1;
        A[6][5] = 1;
        A[7][6] = 1;
        A[8][7] = 1;
        A[9][9] = 2;
        A[10][10] = 1;

        long[] X = new long[11];

        X[0] = 2;
        X[5] = 2;
        X[9] = 1;
        X[10] = 1;

        long[] Y = matrixMultiply(matrixPower(A, N - 4), X);

        System.out.print(Y[0]);
    }
}
