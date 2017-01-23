import CornellBigNumber.BigDecimalMath;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.math.RoundingMode;

/**
 * Created by aa on 23/12/16.
 */
public class p356 {
    public static void main(String[] args) {
        int n = 30;
        Cubic cubic = new Cubic();
        /*// for n = 30
        // x^3 - 2^30 * x^2 + 30
        cubic.solve(1, (long) -Math.pow(2, n), 0, 2);
        System.out.println("x1 = " + cubic.x1);
        if (cubic.nRoots == 3) {
            System.out.println("x2 = " + cubic.x2);
            System.out.println("x3 = " + cubic.x3);
        }*/
        double sum = 0;
        BigDecimal bigSum = BigDecimal.ZERO;
        for (int i = 1; i <= 30; i++) {
            cubic.solve(1, -Math.pow(2, i), 0, i);
            double modded = cubic.x1 % 100000000;

            /*System.out.println("Iteration " + i + ": LRoot = " + new BigDecimal(cubic.x1).toPlainString());
            System.out.println("Iteration " + i + ": Mod 100000000 = " + new BigDecimal(modded).toPlainString());
            System.out.println();*/
            sum += cubic.x1;
            //System.out.println("Sum of i = 1 to 30: " + new BigDecimal(sum).toPlainString());
            bigSum = BigDecimal.valueOf(sum);
            System.out.println("Sum = " + bigSum);
        }
        System.out.println("bigSum outside for loop = " + bigSum.toPlainString());
        BigDecimal exponent = BigDecimal.valueOf(987654321); // I want to bigSum^exponent
        BigDecimal modBy = BigDecimal.valueOf(1000000000);

        //MathContext mc = new MathContext(4);
        BigDecimal result = bigSum.pow(987654321);
        //BigDecimal result = BigDecimalMath.pow(bigSum, exponent).setScale(0, RoundingMode.FLOOR).remainder(modBy);

        System.out.printf("\n\n");
        System.out.println("sum from 1 to 30 ^ 9876543221 = " + result.toString());
    }

}
