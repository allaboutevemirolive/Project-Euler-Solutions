/**
 * Created by aa on 06 February 2017.
 *
 * I found the close form for the last two digits by working with small examples by hand.
 *
 * Otherwise decrement iteratively the first two digits. Much room for improvement but it got
 * the job done.
 */
public class p396 {
    private static final long MOD = 1000000000L;

    private static long powerMod(long p, long n, long mod) {
        long result = 1;
        while (n != 0) {
            if ((n & 1) != 0)
                result = result * p % mod;
            p = p * p % mod;
            n >>= 1;
        }

        return result;
    }

    private static long twoDigit(long n2, long n1, long base) {
        long x = n1;
        long count = x;
        base += x;
        count += (powerMod(2, n2, MOD) - 1) * (base + 1) % MOD;

        return count;
    }

    private static long threeDigit(long n3, long n2, long n1, long base) {
        long x = twoDigit(n2, n1, base);
        long count = x;
        base += x;
        while (n3 > 0) {
            n3--;
            base++;
            count++;
            x = twoDigit(base - 1, base - 1, base);
            count = (count + x) % MOD;
            base = (base + x) % MOD;

            if (base < 9) throw new RuntimeException();
        }

        return count;
    }

    private static long fourDigit(long n4, long n3, long n2, long n1, long base) {
        long x = threeDigit(n3, n2, n1, base);
        long count = x;
        base += x;
        while (n4 > 0) {
            n4--;
            base++;
            count++;
            x = threeDigit(base - 1, base - 1, base - 1, base);
            count = (count + x) % MOD;
            base += x;
        }

        return count;
    }

    public static void main(String[] args) {
        long sum = fourDigit(0, 0, 0, 1, 2)
                + fourDigit(0, 0, 1, 0, 2)
                + fourDigit(0, 0, 1, 1, 2)
                + fourDigit(0, 1, 0, 0, 2)
                + fourDigit(0, 1, 0, 1, 2)
                + fourDigit(0, 1, 1, 0, 2)
                + fourDigit(0, 1, 1, 1, 2)
                + fourDigit(1, 0, 0, 0, 2)
                + fourDigit(1, 0, 0, 1, 2)
                + fourDigit(1, 0, 1, 0, 2)
                + fourDigit(1, 0, 1, 1, 2)
                + fourDigit(1, 1, 0, 0, 2)
                + fourDigit(1, 1, 0, 1, 2)
                + fourDigit(1, 1, 1, 0, 2)
                + fourDigit(1, 1, 1, 1, 2);
        System.out.println(sum % MOD);
    }
}
