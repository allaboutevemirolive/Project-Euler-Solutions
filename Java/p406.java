package com.company;

import java.util.Arrays;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;

public class p406 {
    private static void solve() {
        double[] f = new double[31];
        f[1] = f[2] = 1;
        double ret = 0;
        for(int k = 1;k <= 30;k++){
            if(k >= 3){
                f[k] = f[k-2] + f[k-1];
            }
            double plus = C(1000000000000L, Math.sqrt(k), Math.sqrt(f[k]));
            ret += plus;
        }
        tr(ret);
//		tr(C(2000000, Math.sqrt(5), Math.sqrt(7)));
    }

    private static double C(long n, final double a, final double b) {
        Queue<long[]> q = new PriorityQueue<>(100000, (x, y) -> {
            double vx = x[0] * a + x[1] * b; // + ??
            double vy = y[0] * a + y[1] * b;
            return Double.compare(vx, vy);
        });
        Set<Long> ved = new HashSet<>();
        q.add(new long[]{0L, 0L, 1L});
        ved.add(0L);

        while(true){
            long[] cur = q.poll();
            n -= cur[2];
            if(n <= 0){
                return cur[0]*a+cur[1]*b;
            }
            {
                long n0 = cur[0]+1, n1 = cur[1], nc = cur[2]*(n0+n1)/n0;
                if(!ved.contains(n0<<32|n1)){
                    ved.add(n0<<32|n1);
                    q.add(new long[]{n0, n1, nc});
                }
            }
            {
                long n0 = cur[0], n1 = cur[1]+1, nc = cur[2]*(n0+n1)/n1;
                if(!ved.contains(n0<<32|n1)){
                    ved.add(n0<<32|n1);
                    q.add(new long[]{n0, n1, nc});
                }
            }
        }
    }

    public static void main(String[] args) {
        long s = System.currentTimeMillis();
        solve();
        long g = System.currentTimeMillis();
        tr(g-s+"ms");
        System.out.println("Used memory in bytes: " + (Runtime.getRuntime().totalMemory()
            - Runtime.getRuntime().freeMemory()));
    }

    private static void tr(Object... o) {
        System.out.println(Arrays.deepToString(o));
    }
}
