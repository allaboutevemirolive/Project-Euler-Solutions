package com.company;

/**
 * Created by aa on 11/02/17.
 * Very slow piece of code. Not satisfied with it.
 */
public class p401 {
    
    private static final long ARG = 1000000000000000L;
    private static final long MOD = 1000000000L;


    private static long getTotalDivisors(long n) {
        System.out.println("Calculating total number of divisors of " + n);

        long limit = n;
        long numberOfDivisors = 0;

        for (int i = 1; i < limit; i++) {
            if (n % i == 0) {
                limit = n / i;
                if (limit != 1) {
                    numberOfDivisors++;
                }
                numberOfDivisors++;
            }
        }

        return numberOfDivisors;
    }

    private static long[] getDivisors(long n) {
        System.out.println("Calculating divisors of " + n);

        long[] divisors;
        divisors = new long[(int) getTotalDivisors(n)];

        System.out.println(divisors.length + " divisors found.");

        long limit = n * n;

        int divisorsFound = 0;
        int index = 0;
        for (int i = 1; i <= limit + 1; i++) {
            if (divisorsFound == divisors.length) {
                break;
            }

            if (n % i == 0) {
                //System.out.println("i => " + i);
                divisors[index] = i;
                divisorsFound++;
                index++;
            }
        }


        return divisors;
    }

    private static long sigma2(long n) {
        System.out.println("Calculating sum of squares of the divisors of " + n);

        long[] divisors = getDivisors(n);

        long square;
        int sum = 1;

        for (int i = 1; i < divisors.length; i++) {
            square = divisors[i] * divisors[i];
            sum += square;
        }

        return sum;
    }

    private static long SIGMA2(long n) {
        System.out.println("Calculating SIGMA of " + n);

        long sigma2 = 0;
        for (long i = 1; i <= n; i++) {
            sigma2 += sigma2(i);
        }

        return sigma2 % MOD;
    }

    public static void main(String[] args) {
        //System.out.println(Arrays.toString(getDivisors(1231212323)));
        //System.out.println(sigma2(98));
        // 1 + 2^2 + 7^2 + 14^2 + 49^2 + 98^2 for n = 98
        System.out.println(SIGMA2(ARG));
    }
}
