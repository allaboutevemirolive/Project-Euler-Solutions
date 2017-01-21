package com.company;
import com.company.DataStructures.FenwickTree;
/**
 * Created by aa on 21/01/17.
 * 
 * Used 2 Fenwick trees to loop over all values of j to calculate number of triples
 * in O(n * log(n)).
 */
public class p378 {
    public static void main(String[] args) {
        final long mod = 1000000000000000000L;

        final int N = 60000000;
        final int[] d = new int[N + 2];

        for (int i = 1; i < d.length; i++) d[i] = 1;

        for (int i = 4; i < d.length; i <<= 1)
            for (int j = i; j < d.length; j += 1) ++d[j];

        for (int i = 3; i < d.length; i += 2) {

            if (d[i] == 1) {

                for (int j = i; j < d.length; j += i) {
                    int sum = 1;
                    int tmp = j;

                    do {
                        tmp /= i;
                        ++sum;
                    } while (tmp % i == 0);
                }
            }
        }

        int max = d[1];

        for (int i = 2; i <= N; i++) max = Math.max(max, d[i] = d[i] * d[i + 1]);

        System.out.println(max);

        final FenwickTree grt = new FenwickTree(max + 1), lth = new FenwickTree(max + 1);
        
        for (int i = 1; i <= N; i++) grt.add(d[i], 1);
        
        long ans = 0;
        
        for (int j = 1; j < N; j++) {
            grt.add(d[j], -1);
            ans += modMul(lth.range(d[j] + 1, max), grt.range(0, d[j] - 1), mod);
            if (ans >= mod) ans -= mod;
            lth.ad(d[j], 1);
        }
        
        System.out.println("=> " + ans);
    }

}
