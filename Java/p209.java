/**
 * Created by aa on 28/10/16.
 */
public class p209 {
    private static long[] memo = new long[129];

    public static void main(String[] args) {
        long start = System.nanoTime();

        boolean[] seen = new boolean[64];
        int index = 0;
        long result = 1;

        while (index < 64) {
            while ((index < 64) && (seen[index] == true)) {
                index++;
            }

            if (index >= 64) {
                continue;
            }

            int first = index, n = 0;

            do {
                seen[index] = true;
                index = Perm(index);
                ++n;
            } while (index != first);

            result *= Fib(2 * n) / Fib(n);
        }

        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");
    }

    private static int Perm(int n) {
        int bit = n ^ ((n << 1) & (n << 2));
        bit = (bit >> 5) & 1;

        return ((n & 31) << 1) | bit;
    }

    private static long Fib(int n) {
        if ((n == 1) || (n == 2)) {
            return 1;
        }

        if (memo[n] == 0) {
            memo[n] = Fib(n - 1) + Fib(n - 2);
        }

        return memo[n];
    }
}
