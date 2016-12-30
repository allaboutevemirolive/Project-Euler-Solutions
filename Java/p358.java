package com.company;
import com.company.Math.PrimeUtils;
/**
 * Created by aa on 28/12/16.
 */
public class p358{
    private static final int MOD = 100000;

    public static void main(String[] args) {
        calculate();
    }

    private static void calculate() {
        int firstNumberTail = 56789;
        int lastNumberTail = 43210;
        int lengthTail = 0;

        for (int i = 0, f = 1; i < 5; i++) {
            int f10 = f * 10;

            for (int j = 0; j < 10; j++) {
                int factor = f * j + lengthTail;
                if ((firstNumberTail * factor) % f10 == lastNumberTail % f10) {
                    lengthTail = factor;
                    break;
                }
            }
            f = f10;
        }
        System.out.println("Last five digits is: " + (lengthTail + 1));

        long rangeStart = 99999999999L / 138;
        long rangeEnd = 99999999999L / 137;
        System.out.println("Looking for numbers between " + rangeStart + " and " + rangeEnd);

        PrimeUtils.Context c = new PrimeUtils.Context();
        int numbers = 0;

        for (long i = rangeStart; i < rangeEnd; i += MOD) {
            numbers++;

            long candidate = (int) (i - (i % MOD) + lengthTail) + 1;

            if (!PrimeUtils.isPrime(candidate, c)) {
                continue;
            }

            System.out.println("Checking " + candidate + " with sum of digits " + ((candidate - 1) / 2 * 9));
        }
        System.out.println(numbers + " numbers are verified");
    }

}
