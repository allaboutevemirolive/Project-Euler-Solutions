import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by aa on 10 February 2017.
 * Let a_p be the smallest value such that F(a_p) is divisible by prime p.
 * I assumed without proof that (p a_p) is divisible by p^2 (related to Wall's conjecture?)
 *
 * Since F(nk) is divisible by F(l), if F(b = p a_p) is divisible by p^2, then all
 * F(kb) are also divisible by p^2. Used a sieve to remove all non-square free F(n).
 */
public class p399 {
    private static final int  SIEVE = 150000000;
    private static final int  PRIME =  10000000;
    private static final int  N     = 100000000;
    private static final long MOD   = 10000000000000000L;

    private static int[] findPrimes(int limit) {
        List<Integer> list = new ArrayList<>();

        boolean[] isComposite = new boolean[limit + 1];
        isComposite[1] = true;

        for (int i = 2; i <= limit; i++) {
            if (!isComposite[i]) {
                list.add(i);
                int multiple = 2;
                while (i * multiple <= limit) {
                    isComposite[i * multiple] = true;
                    multiple++;
                }
            }
        }

        int[] listSize = new int[list.size()];
        Iterator<Integer> iterator = list.iterator();

        for (int i = 0; i < listSize.length; i++)
            listSize[i] = iterator.next();

        return listSize;
    }

    private static long F(long k) {
        long f0 = 1;
        long f1 = 1;
        for (int n = 2; n < k; n++) {
            long f2 = (f1 + f0) % MOD;
            f0 = f1;
            f1 = f2;
        }

        return f1;
    }

    private static int A(long p) {
        long f0 = 1;
        long f1 = 1;
        int n = 2;
        for (; ;) {
            n++;
            long f2 = (f1 + f0) % p;
            if (f2 == 0) return n;
            if (n * p  > SIEVE) return Integer.MAX_VALUE;
            f0 = f1;
            f1 = f2;
        }
    }

    public static void main(String[] args) {
        int[] primes = findPrimes(PRIME);
        boolean[] sieve = new boolean[SIEVE];
        for (int p : primes) {
            int a = A(p);
            if (a < sieve.length / p) {
                int b = p * a;
                for (int i = b; i < sieve.length; i += b)
                    sieve[i] = true;
            }
        }

        int count = 0;
        for (int i = 1; i < sieve.length; i++) {
            if (!sieve[i] && ++count == N) {
                double phi = 0.5 + 0.5 * Math.sqrt(5);
                double logphi = Math.log10(phi);
                double logF = i * logphi - 0.5 * Math.log10(5);
                long exp = (long) Math.floor(logF);
                double mant = Math.pow(10, logF - exp);

                System.out.printf("%d,%3.1fe%d\n", F(i), mant, exp);
            }
            //System.out.println(F(i));
        }
    }

}
