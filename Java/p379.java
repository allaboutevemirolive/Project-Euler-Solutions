package com.company;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by aa on 21/01/17.
 * Explanation provided separately.
 */
public class p379 {
    static Map<Long, Long> cache = new HashMap<>();

    public static void main(String[] args) {
        long n = (long) Math.pow(10, 12);
        long ans = 0;
        long sq = (long) Math.sqrt(n);

        for (long g = 1; g <= sq; g++) {
            long ng = n / g;
            ans += recursion(ng);
            long min = Math.max((long) Math.floor(n / (g + 1)), sq);

            if (ng > min) ans += (ng - min) * recursion(g);
        }

        System.out.println("Answer => " + ans);
    }

    public static long recursion(long n) {
        if (cache.containsKey(n)) return cache.get(n);

        long sq = (long) Math.sqrt(n);
        long ans = sq * (sq + 1) / 2;
        for (long eq = 1; eq <= sq; eq++) {
            long min = Math.max((long) Math.floor(n / (eq + 1)), sq);
            long max = n / eq;
            ans += (max - min) * eq;
        }

        for (long d = 2; d <= sq; d++)
            ans -= recursion(n / d / d);

        cache.put(n, ans);

        return ans;
    }
}
