/**
 * Created by aa on 28/10/16.
 */
import java.util.Arrays;

public class p211 {
    public static void main(String[] args) {
        int n = 64000000;
        long[] sums = getSumOfDivisors(n);
        long result = 0;

        for (int i = 1; i < n; i++) {
            if (isSquare(sums[i])) {
                result += i;
            }
        }

        System.out.println(result);
    }

    private static long[] getSumOfDivisors(int n) {
        long[] sums = new long[n];
        Arrays.fill(sums, 1);
        sums[0] = 0;

        // TODO: dont be a retard

        for (int i = 2; i < n; i++) {
            if (sums[i] == 1) {
                long p2 = (long) i * i;

                for (int j = i; j < n; j += i) {
                    long s = 1, powp = i, powp2 = p2;

                    while (j % powp == 0) {
                        s += powp2;
                        powp *= i;
                        powp2 *= p2;
                    }

                    sums[j] *= s;
                }
            }
        }

        return sums;
    }

    private static boolean isSquare(long x) {
        long y = Math.round(Math.sqrt(x));

        return y * y == x;
    }

}
