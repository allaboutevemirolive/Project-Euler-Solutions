/**
 * Created by hampe on 25 October 2016.
 */
public class p182 {

    static long p = 1009;
    static long q = 3643;

    static long phi = (p - 1) * (q - 1);

    static long gcd(long x, long y) {
        long r;
        while (y != 0) {
            r = x % y;
            x = y;
            y = r;
        }
        return x;
    }

    public static void main(String[] args) {
        long min = Long.MAX_VALUE;
        long noUnconcealedMsgs;

        long ans = 0;

        for (long e = 2; e < phi; e++) {
            if (gcd(e, phi) == 1) {
                noUnconcealedMsgs = (gcd(e - 1, p - 1) + 1) * (gcd(e - 1, q - 1) + 1);

                if (noUnconcealedMsgs < min) {
                    ans = 0;
                    min = noUnconcealedMsgs;
                }

                if (noUnconcealedMsgs == min) {
                    ans += e;
                }
            }
        }

        System.out.println("Answer: " + ans);
    }
}
