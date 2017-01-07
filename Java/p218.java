/**
 * Created by aa on 29/10/16.
 */
public class p218 {

    public static void main(String[] args) {
        long start = System.nanoTime();

        long perfect = 0, superperfect = 0;
        long result = 0;
        long max = 10000000000000000L;

        for (long t = 1; t * t * t * t <= max; ++t)
            for (long s = t + 1; s * s * s * s + t * t * t * t + 2 * s * s * t
                    * t <= max; ++s) {
                if ((s & 1) == (t & 1)) {
                    continue;
                }

                if (gcd(s, t) != 1) {
                    continue;
                }

                long m = 2 * s * t;
                long n = s * s - t * t;

                if (m < n) {
                    long temp = m;
                    m = n;
                    n = temp;
                }

                long a = 2 * m * n;
                long b = m * m - n * n;
                ++perfect;

                if (((a % 3) != 0) && ((b % 3) != 0)) {
                    continue;
                }

                if (((a % 7) != 0) && ((b % 7) != 0)) {
                    continue;
                }

                a /= 2;

                if (((a & 1) != 0) && ((b & 1) != 0)) {
                    continue;
                }

                ++superperfect;
            }

        result = perfect - superperfect;

        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");

    }

    private static long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}
