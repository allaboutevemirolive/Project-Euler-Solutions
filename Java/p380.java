/**
 * Created by aa on 22 January 2017.
 *
 * This problem is a count of a m*n grid graph.
 *
 * Found a formula for a square grid at http://mathworld.wolfram.com/SpanningTree.html and
 * took a guess at how to change it for rectangular.
 *
 * Had to use logarithms to calculate because double doesn't have enough bits for the
 * exponent.
 */
public class p380 {

    public static void main(String[] args) {
        calc(100, 500);
    }

    private static double calc(int m, int n) {
        double log = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if ((i == 0) && (j == 0))
                    continue;

                double mult = 2 - Math.cos(Math.PI * i / m) - Math.cos(Math.PI * j / n);
                mult *= 2;

                log += Math.log10(mult);
            }
        }

        log  -= Math.log10(m * n);
        long exp = (long) Math.floor(log);

        double mantissa = Math.pow(10, log - exp);

        System.out.printf("C(%d, %d) = %fe%d", m, n, mantissa, exp);

        return log;
    }

}
