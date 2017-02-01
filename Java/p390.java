/**
 * Created by aa on 01/02/17.
 * Another way to do this is to notice that b^2c^2 + b^2 + c^2 must be a square.
 * Solve n^2 - (b^2 + 1) c^2 - b^2 = 0 for a given b.
 * Once a primitive solution (n, c) is found, the recurrence equation for additional
 * solutions is:
 * n <- (2b^2 + 1)n + 2b(b^2 + 1)c
 * c <- 2bn + (2b^2 + 1)c
 * 
 * (b, 0) is a seed solution. The area of the triangle is n/2.
 * But this way you can't find all solutions. Missing solutions are found using
 * c <- -b
 * b <- c
 * 
 * or 
 * 
 * c <- b
 * b <- c
 * as new seed from any given solution.
 */
public class p390 {
    private static final long N = 10000000000L;

    private static long iterate(long n, long c, long b) {
        long sum = 0;
        for (; ;) {
            // Check for overflow
            if (Math.abs((2.0 * b * b + 1) * n + 2.0 * b * ((double) b * b + 1) * c) > 10 * N) break;

            // Recurrence equation
            long n1 = (2 * b * b + 1) * n + 2 * b * (b * b + 1) * c;
            long c1 = 2*b*n + (2*b*b + 1) * c;
            n = n1;
            c = c1;

            if (Math.abs(n) > 2*N) break;

            // Collect sum
            if (n > 0 && c >= b && b > 0) sum += n / 2;
        }

        return sum;
    }

    public static void main(String[] args) {
        long sum = 0;
        for (long b = 2; b * b <= 2 * N; b += 2) {
            sum += iterate(b, 0, b);
            System.out.printf("Iteration %d\t%d\n", b, sum);
        }
        System.out.println("Count = " + sum);
    }
}
