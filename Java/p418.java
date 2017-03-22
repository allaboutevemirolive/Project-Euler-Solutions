package com.company;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by aa on 22/03/17.
 * To maximize c/a, a, b and c must be close to the cubic root of 43!. Using the prime factorization of 43!,
 * I generate all factors 0.9999 43!^(1/3) < x < 1.0001 43!^(1/3). Then for each pair of factors (x, y), if x*y divides
 * 43! I compute z = 43!/(x*y). I keep the best triplet (x, y, z) [based on z - x, which is almost equivalent to z/x
 * since x ~= z].
 */
public class p418 {
    private static final int N = 43;
    // prime factors
    private static final long[] p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    // exponent of each prime factor
    private static final long[] e = {38, 18, 9, 5, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1};
    private static List<Long> list = new ArrayList<>();
    private static double min;
    private static double max;

    // populate list of factors of 43! between min and max
    private static void recurse(long x, int i) {
        if (i == p.length) {
            if (x > min)
                list.add(x);
        } else {
            for (int j = 0; j <= e[i]; ++j) {
                recurse(x, i + 1);
                long y = x * p[i];
                if (y / x != p[i] || y > max)
                    break;
                x = y;
            }
        }
    }

    public static void main(String[] args) {
        double target = 1;

        for (int i = 1; i <= N; ++i)
            target *= i;

        double root = Math.cbrt(target);

        min = root * 0.9999;
        max = root * 1.0001;
        BigInteger n = BigInteger.ONE;

        for (int i = 2; i <= N; ++i)
            n = BigInteger.valueOf(i).multiply(n);

        recurse(1, 0);

        Long[] a = list.toArray(new Long[list.size()]);
        Arrays.sort(a);

        long best = Long.MAX_VALUE;
        long result = 0;

        for (int i = 0; i < a.length; ++i) {
            BigInteger mi = BigInteger.valueOf(a[i]);
            BigInteger[] q = n.divideAndRemainder(mi);

            if (q[1].signum() != 0)
                throw new RuntimeException();

            for (int j = 0; j <= i; ++j) {
                BigInteger mj = BigInteger.valueOf(a[j]);
                BigInteger[] z = q[0].divideAndRemainder(mj);

                if (z[1].signum() == 0 && z[0].compareTo(mi) >= 0) {

                    long diff = z[0].longValue() - a[j];

                    if (diff < best) {
                        best = diff;
                        result = mj.add(mi).add(z[0]).longValue();
                    }
                }
            }
        }
        System.out.println(result);
    }
}
