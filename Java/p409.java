package com.company;

/**
 * Created by aa on 27/02/17.
 * Let dp[m] be the number of ways to choose m numbers x_1, ..., x_m such that:
 * For each i 1 <= x_i <= 2^n
 * x_i are pairwise distinct
 * x_1 xor x_2 xor ... xor x_m = 0

 If you decide the values of x_1, ..., x_m, you can decide x_(m+1) uniquely from the xor condition.
 So dp[m+1] is almost (2^n - 1) * ... * (2^n - m). There are two types of exceptions:
 * When x_1 xor ... xor x_m = 0, x_(m+1) will be 0. This exception happens dp[m] times.
 * When x_1 xor ... xor x_m = x_k for some k, x_(m+1) will be equal to x_k. This exception happens dp[m-1] * m * (2^n - 1 - m + 1) times.
 */
public class p409 {
    private static long m = 1000000007;

    public static void main(String[] args) {
        int n = 10000000;
        long two2n = modulo(2, n);

        long[] prods = new long[n];
        long answer = 1;
        for (int i = 1; i <= n; i++) {
            long this_fact = (two2n - i) % m;
            answer = (answer * this_fact) % m;
            prods[i - 1] = answer;
        }

        long[] add_to_zero = new long[n];
        add_to_zero[0] = 0;
        add_to_zero[1] = 0;

        for (int k = 2; k <= (n - 1); k++) {
            long ans = (prods[k - 1] - add_to_zero[k - 1]) % m;
            long mult = (two2n - k) % m;
            mult = (mult * k) % m;
            mult = (add_to_zero[k - 2] * mult) % m;
            ans = (ans - mult) % m;

            add_to_zero[k] = ans;
        }

        long temp = (prods[n - 1] - add_to_zero[n - 1]) % m;
        if (temp < 0)
            temp += m;

        System.out.println(temp);
    }

    private static long modulo(long base, long exp) {
        long ans = 1;
        long pow = base;
        while (exp > 0) {
            if (exp % 2 == 1)
                ans = (ans * pow) % m;
            pow = (pow * pow) % m;
            exp /= 2;
        }

        return ans % m;
    }
}
