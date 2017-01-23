import java.math.BigInteger;

/**
 * Created by aa on 23 January 2017.
 *
 * Wilson's theorem.
 */
public class p381 {

    public static void main(String[] args) {
        int N = 100000000;
        int[] primes = prime(N);

        BigInteger pcount = BigInteger.ZERO;

        for (int i = 2; i < primes.length; i++) {
            BigInteger s = BigInteger.valueOf(primes[i]);
            BigInteger count = s.add(s.subtract(BigInteger.ONE).divide(BigInteger.valueOf(2)));

            int y = 0;
            for (int k = 1; ; k++) {
                if ((k * primes[i] + 1) % 8 == 0) {
                    y = (k * primes[i] + 1) / 8;
                    break;
                }
            }

            count = count.add(BigInteger.valueOf(y)).mod(s);
            pcount = pcount.add(count);
        }
        System.out.println(pcount);
    }

    private static int[] prime(int N) {
        boolean[] tf = new boolean[N];
        int counter = 0;
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == 1)
                tf[i] = false;
            else
                tf[i] = true;
        }

        for (int i = 2; i < N; i++) {
            if (tf[i]) {
                counter++;
                for (int j = 2 * i; j < N; j += i) {
                    tf[j] = false;
                }
            }
        }

        int[] prim = new int[counter];
        int k = 0;
        for (int i = 2; i < N; i++) {
            if (tf[i]) {
                prim[k] = i;
                k++;
            }
        }

        return prim;
    }
}
