package com.company;

/**
 * Created by aa on 01/03/17.
 */
public class p412 {
    private static void getFact() {
        long n = 10000;
        long m = 5000;
        long mod = 76543217;

        long res = 1;
        for (long i = 0; i < n - m; i++) {
            for (long j = 0; j < n - m; j++) {
                if (j < m) {
                    res = (res * (i + j + 1) * (i + j + 1)) % mod;
                }
                res = (res * (2 * m + i + j + 1)) % mod;
            }
        }
        long fact = 1;
        for (long i = 1; i <= mod - 2; i++) {
            if (i <= n * n - m * m) {
                fact = (fact * i) % mod;
            }
            fact = (fact * res) % mod;
        }
        System.out.println(fact);
    }

    public static void main(String[] args) {
        getFact();
    }
}
