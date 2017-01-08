/**
 * Created by hampe on 26 October 2016.
 */
public class p188 {

    private static final long N = 1777;
    private static final long POW = 1855;
    private static final long MOD = 100000000;

    public static void main(String[] args) {
        long start = System.nanoTime();

        long result = hexp(N, POW, MOD);

        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");
    }

    private static long cycleSize(long n, long m) {
        long num = n;
        long i = 1;

        for (; num != 1L; i++) {
            num *= n;
            num %= m;
        }

        return i;
    }

    private static long hexp(long n, long hexp, long mod) {
        if (hexp == 1) {
            return n % mod;
        }

        long mod1 = cycleSize(n, mod);
        long exp = hexp(n, hexp - 1, mod1);
        long num = 1;

        for (long i = 0; i < exp; i++) {
            num *= n;
            num %= mod;
        }

        return num;
    }
}
