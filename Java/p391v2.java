package com.company;

/**
 * Created by aa on 01/02/17.
 * This is an improvement because I found out that if we pick 'a' large enough, then
 * we don't actually need to check all values in the range a <= i <= b. Since all M_i(n)
 * are equal, we only need to compute one. This leads to a much simpler and faster program.
 *
 * However there is no way to tell which 'a' is big enough with this variant. You could
 * potentially test increasing values of 'a'.
 *
 * Takes 20 seconds with b = 2 x 10^7 - 1.
 */
public class p391v2 {
    private static final int N = 20000000;

    public static void main(String[] args) {
        long sum = 0;
        int[] S = new int[N];
        for (int i = 1; i < N; ++i) S[i] = S[i - 1] + Integer.bitCount(i);
        for (int n = 1; n <= 1000; ++n) {
            int j = N - 1;
            int i = j;
            while (S[i] > n) {
                while (S[i] + n >= S[j]) --i;
                j = i;
            }
            int m = S[i];
            sum += m * m * m;
        }
        System.out.println(sum);
    }
}
