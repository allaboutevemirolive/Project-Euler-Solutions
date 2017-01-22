import java.math.BigInteger;
import java.util.ArrayList;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * Created by aa on 13/12/16.
 */
public class p119 {

    private static final int INDEX = 30;

    public static void main(String[] args) {
        p119 p = new p119();
        System.out.println(p.calculate());

    }

    public String calculate() {
        for (BigInteger limit = BigInteger.ONE; ; limit = limit.shiftLeft(8)) {
            SortedSet<BigInteger> candidates = new TreeSet<>();

            for (int k = 2; BigInteger.valueOf(1).shiftLeft(k).compareTo(limit) < 0; k++) {
                for (int n = 2; ; n++) {
                    BigInteger pow = BigInteger.valueOf(n).pow(k);
                    if (pow.compareTo(limit) >= 0 && pow.toString().length() * 9 < n) {
                        break;
                    }
                    if (pow.compareTo(BigInteger.TEN) >= 0 && isDigitSumPower(pow)) {
                        candidates.add(pow);
                    }
                }
            }
            if (candidates.size() >= INDEX) {
                return new ArrayList<>(candidates).get(INDEX - 1).toString();
            }
        }
    }

    private static boolean isDigitSumPower(BigInteger x) {
        int digitSum = digitSum(x);
        if (digitSum == 1) {
            return false;
        }

        BigInteger base = BigInteger.valueOf(digitSum);
        BigInteger pow = base;
        while(pow.compareTo(x) < 0) {
            pow = pow.multiply(base);
        }
        return pow.equals(x);
    }

    private static int digitSum(BigInteger x) {
        if (x.signum() < 1) {
            throw new IllegalArgumentException("Only positive ints");
        }
        int sum = 0;
        for (char c : x.toString().toCharArray()) {
            sum += c - '0';
        }
        return sum;
    }
}
