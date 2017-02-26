package com.company;

import java.util.Arrays;
import java.util.Comparator;

/**
 * Created by aa on 26/02/17.
 */
public class p408 {
    private static long[] cache = new long[10000];

    private static int mod = 1000000007;
    private static int[][] q = new int[10000][];

    private static int p = 0;
    private static int N = 10000000;
    private static int ct = 0;
    private static long[] fact = new long[N*2 + 1];
    private static long[] ifact = new long[N*2 + 1];

    private static void generate(int[] t) {
        if (t[0] * t[0] > N || t[1] * t[1] > N)
            return;

        for (int i = 1; ; i++) {
            if ((long) t[0] * t[0] * i * i > N || (long) t[1] * t[1] * i * i > N)
                break;
            q[p++] = new int[] {t[0] * t[0] * i * i, t[1] * t[1] * i * i};
            q[p++] = new int[] {t[1] * t[1] * i * i, t[0] * t[0] * i * i};
        }

        generate(new int[] {
                t[0] + 2 * t[1] + 2 * t[2],
                2 * t[0] + t[1] + 2 * t[2],
                2 * t[0] + 2 * t[1] + 3 * t[2]
        });

        generate(new int[] {
                -t[0] + 2 * t[1] + 2 * t[2],
                -2 * t[0] + t[1] + 2 * t[2],
                -2 * t[0] + 2 * t[1] + 3 * t[2]
        });

        generate(new int[] {
                t[0] - 2 * t[1] + 2 * t[2],
                2 * t[0] - t[1] + 2 * t[2],
                2 * t[0] - 2 * t[1] + 3 * t[2]
        });
    }

    private static long U(int a, int b) {
        return fact[a + b] * ifact[a] % mod * ifact[b] % mod;
    }

    private static long dfs(int cur) {
        if (cache[cur] != -1)
            return cache[cur];
        ct++;
        long ret = U(N - q[cur][0], N - q[cur][1]);

        for (int i = cur + 1; i < p; i++) {
            if (q[cur][1] <= q[i][1]) {
                ret -= dfs(i) * U(q[i][0] - q[cur][0], q[i][1] - q[cur][1]) % mod;
            }
        }
        ret = ((ret % mod) + mod) % mod;
        return cache[cur] = ret;
    }

    private static long invl(long a, long mod) {
        long b = mod;
        long p = 1, q = 0;
        while (b > 0) {
            long c = a / b;
            long d;
            d = a;
            a = b;
            b = d % b;
            d = p;
            p = q;
            q = d - c * q;
        }
        return p < 0 ? p + mod : p;
    }

    private static void tr(Object... o) {
        System.out.println(Arrays.deepToString(o));
    }

    private static void solve() {
        generate(new int[] {3, 4, 5});

        fact[0] = 1;
        ifact[0] = 1;

        for (int i = 1; i <= 2*N; i++) {
            fact[i] = fact[i - 1] * i % mod;
            ifact[i] = invl(fact[i], mod);
        }

        q = Arrays.copyOf(q, p);

        Arrays.sort(q, (a, b) -> {
            if (a[0] != b[0])
                return a[0] - b[0];
            return a[1] - b[1];
        });

        Arrays.fill(cache, -1);
        long ret = U(N, N);
        for (int i = 0; i < p; i++) {
            ret -= dfs(i) * U(q[i][0], q[i][1]) % mod;
        }
        tr((ret % mod + mod) % mod);
    }

    public static void main(String[] args) {
        solve();
    }
}
