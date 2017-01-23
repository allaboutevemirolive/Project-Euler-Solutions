import java.math.BigInteger;
/**
 * Created by aa on 29/10/16.
 */
public class p217 {

    private static BigInteger[][] numPerm, sumPerm,
            numPermNoZeroStart, sumPermNoZeroStart;

    public static void main(String[] args) {
        long start = System.nanoTime();
        fillArrays(47);
        BigInteger tOfN = getTOfN(47);
        BigInteger result = tOfN.mod(BigInteger.valueOf(3).pow(15));

        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");
    }

    public static void fillArrays(int n) {
        numPerm = new BigInteger[n / 2 + 1][(n / 2) * 9 + 1];
        sumPerm = new BigInteger[n / 2 + 1][(n / 2) * 9 + 1];
        numPermNoZeroStart = new BigInteger[n / 2 + 1][(n / 2) * 9 + 1];
        sumPermNoZeroStart = new BigInteger[n / 2 + 1][(n / 2) * 9 + 1];

        for (int i = 0; i < n / 2 + 1; i++) {
            for (int j = 0; j < (n / 2) * 9 + 1; j++) {
                numPerm[i][j] = BigInteger.ZERO;
                sumPerm[i][j] = BigInteger.ZERO;
                numPermNoZeroStart[i][j] = BigInteger.ZERO;
                sumPermNoZeroStart[i][j] = BigInteger.ZERO;

                if (i == 0) {
                    continue;
                }

                if (j < 10) {
                    if (i == 1) {
                        numPerm[i][j] = BigInteger.ONE;
                        sumPerm[i][j] = BigInteger.valueOf(j);

                        if (j != 0) {
                            numPermNoZeroStart[i][j] = BigInteger.ONE;
                            sumPermNoZeroStart[i][j] = BigInteger.valueOf(j);
                        }
                    }
                }

                for (int k = 0; k < 10 && k <= j; k++) {
                    numPerm[i][j] = numPerm[i][j].add(numPerm[i - 1][j - k]);
                    sumPerm[i][j] = sumPerm[i][j].add(sumPerm[i - 1][j - k])
                            .add(BigInteger.valueOf(k)
                            .multiply(BigInteger.TEN.pow(i - 1))
                            .multiply(numPerm[i - 1][j - k]));

                    if (k != 0) {
                        numPermNoZeroStart[i][j] = numPermNoZeroStart[i][j]
                                .add(numPerm[i - 1][j - k]);
                        sumPermNoZeroStart[i][j] = sumPermNoZeroStart[i][j]
                                .add(sumPerm[i - 1][j - k])
                                .add(BigInteger.valueOf(k)
                                        .multiply(BigInteger.TEN.pow(i - 1))
                                        .multiply(numPerm[i - 1][j - k]));
                    }
                }
            }
        }
    }

    private static BigInteger getTOfN(int n) {
        BigInteger tOfN = BigInteger.ZERO;
        BigInteger tOfi;

        for (int i = 0; i <= n; i++) {
            if (i == 1) {
                tOfN = BigInteger.valueOf(45);
            }

            if (i % 2 == 0) {
                for (int j = 0; j <= (i / 2) * 9; j++) {
                    tOfi = sumPerm[i / 2][j]
                            .multiply(numPermNoZeroStart[i / 2][j]);
                    tOfi = tOfi.add(sumPermNoZeroStart[i / 2][j].multiply(
                            numPerm[i / 2][j]).multiply(
                            BigInteger.TEN.pow(i / 2)));
                    tOfN = tOfN.add(tOfi);
                }
            } else {
                for (int j = 0; j <= ((i - 1) / 2) * 9; j++) {
                    tOfi = sumPerm[(i - 1) / 2][j]
                            .multiply(numPermNoZeroStart[(i - 1) / 2][j]);

                    tOfi = tOfi.add(sumPermNoZeroStart[(i - 1) / 2][j]
                            .multiply(numPerm[(i - 1) / 2][j]).multiply(
                                    BigInteger.TEN.pow((i + 1) / 2)));

                    tOfi = tOfi.multiply(BigInteger.valueOf(10));

                    tOfi = tOfi.add(BigInteger.valueOf(45)
                            .multiply(BigInteger.TEN.pow((i - 1) / 2))
                            .multiply(numPerm[(i - 1) / 2][j])
                            .multiply(numPermNoZeroStart[(i - 1) / 2][j]));

                    tOfN = tOfN.add(tOfi);
                }
            }
        }

        return tOfN;
    }
}
