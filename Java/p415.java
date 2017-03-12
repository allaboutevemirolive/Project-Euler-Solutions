package com.company;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by aa on 11/03/17.
 * According to the Sylvester–Gallai theorem, all sets of 2 or more points are titanic except colinear sets of 3 or more points. For 0≤x,y≤N0≤x,y≤N, there are (N+1)2(N+1)2 points and thus 2(N+1)22(N+1)2 possible sets. Of these, the following sets are not titanic:
 a) The empty set: 1
 b) Sets of 1 point: (N+1)2(N+1)2
 c) Sets of 3 or more horizontal or vertical points: 2(N+1)(2N+1−1−(N+1)−N(N+1)2)2(N+1)(2N+1−1−(N+1)−N(N+1)2).
 d) Sets of 3 or more collinear diagonal points: ∑2≤Δx,Δy≤N2(N+1−Δx)(N+1−Δy)(2gcd(Δx,Δy)−1−1)∑2≤Δx,Δy≤N2(N+1−Δx)(N+1−Δy)(2gcd(Δx,Δy)−1−1)

 Thus T(N)=2(N+1)2−1−(N+1)2−2(N+1)(2N+1−1−(N+1)−N(N+1)2)T(N)=2(N+1)2−1−(N+1)2−2(N+1)(2N+1−1−(N+1)−N(N+1)2)
 −∑2≤Δx,Δy≤N2(N+1−Δx)(N+1−Δy)(2gcd(Δx,Δy)−1−1)−∑2≤Δx,Δy≤N2(N+1−Δx)(N+1−Δy)(2gcd(Δx,Δy)−1−1)

 The expression for (c) comes from 2(N+1)2(N+1) lines with 2N+12N+1 possible sets, minus the empty set (1), the sets with 1 point (N+1)(N+1) and the sets with 2 points N(N+1)2N(N+1)2.

 For (d), consider the diagonal collinear set of points with (x1,y1)(x1,y1) and (x2,y2)(x2,y2) at the extremities. Let Δx=x2−x1Δx=x2−x1 and Δy=y2−y1Δy=y2−y1. x1x1 can take (N+1−Δx)(N+1−Δx) values and y1y1 can take (N+1−Δy)(N+1−Δy) values. The number of possible internal points is gcd(Δx,Δy)gcd(Δx,Δy), and thus there are (2gcd(Δx,Δy)−1−1)(2gcd(Δx,Δy)−1−1) non empty sets of internal points.

 Evaluating (d) is the difficult part. Let's write n=N+1n=N+1, g=gcd(Δx,Δy)g=gcd(Δx,Δy), Δx=agΔx=ag and Δy=bgΔy=bg, then (d) becomes
 ∑2≤Δx,Δy≤N2(n−Δx)(n−Δy)(2g−1−1)∑2≤Δx,Δy≤N2(n−Δx)(n−Δy)(2g−1−1)
 =2∑g=2N∑a=1⌊Ng⌋∑b=1gcd(a,b)=1⌊Ng⌋(n−ag)(n−bg)(2g−1−1)=2∑g=2N∑a=1⌊Ng⌋∑b=1gcd(a,b)=1⌊Ng⌋(n−ag)(n−bg)(2g−1−1)
 We can use inclusion/exclusion principle to take care of the gcd(a,b)=1gcd(a,b)=1 condition. Then the two internal sums simplify to:
 =2∑g=2N(n⌊Ng⌋−g⌊Ng⌋⌊Ng+1⌋2)2(2g−1−1)=2∑g=2N(n⌊Ng⌋−g⌊Ng⌋⌊Ng+1⌋2)2(2g−1−1)
 We can sum over ⌊Ng⌋⌊Ng⌋ constant, and the expression becomes k1g2(2g−1−1)+k2g(2g−1−1)+k3(2g−1−1)k1g2(2g−1−1)+k2g(2g−1−1)+k3(2g−1−1)
 There is a close form for the sum of each of these factors (see Wolfram Alpha).
 Evaluating the sum over g is O(n12)O(n12). Using mobius inversion for the inclusion/exclusion, the resulting complexity is O(n34)O(n34).

 So...

 For T(n) there are 2^((n + 1)^2) sets of points. From these sets we have to exclude:
 a) Set with no point (1)
 b) Sets with one point ((n + 1)^2)
 c) Sets with 3 or more points, all collinear, horizontal or vertical.
 For each horizontal or vertical set of points (2^(n + 1) - 1 - n - n(n + 1)/2)
 For 2(n + 1) horizontal and verticals: 2(n + 1)(2^(n + 1) - 1 - n - n(n + 1)/2)
 d) Sets with 3 or more points, all collinear, diagonal.
 For diagonals, consider the segment (x1, y1) to (x2, y2) that contains all points of the set.
 Let dx = x2 - x1, dy = y2 - y1, g = gcd(dx, dy)
 There are g - 1 inside points, so there are 2^(g - 1) - 1 invalid sets.
 Such segment can be placed in 2*(n + 1 - dx)(n + 1 - dy) positions.
 So we exclude 2*(n + 1 - dx)(n + 1 - dy)(2^(g - 1) - 1).

 The last part (d) is the hard part to compute. To get the running time down, I used mobius inversion and grouped terms in sequences that have the same floor(N/k) in sequences. Running time  15 min in java.
 */
public class p415 {
    private static final long MOD = power(10, 8);
    private static final long MOD2  = 2 * MOD;
    private static final long MOD6  = 6 * MOD;
    private static final long n     = power(10, 11);
    private static final long N     = n + 1;
    private static Map<Long, Long> aCache = new HashMap<>();
    private static Map<Long, Long> bCache = new HashMap<>();
    private static Map<Long, Long> cCache = new HashMap<>();

    private static long powerMod(long p, long n, long mod) {
        long result = 1;
        while (n != 0) {
            if ((n & 1) != 0)
                result = result * p % mod;
            p = p * p % mod;
            n >>= 1;
        }
        return result;
    }

    private static long power(long p, long n) {
        if (n < 0) throw new RuntimeException();
        long result = 1;
        while (n != 0) {
            if ((n & 1) != 0)
                result *= p;
            p *= p;
            n >>= 1;
        }
        return result;
    }

    /*
    Mobius inversion
     */
    private static long a(long n) {
        Long result = aCache.get(n);
        if (result != null)
            return result;
        long sum = A(n);
        for (long dmax = n; dmax > 1; ) {
            long r = n / dmax;
            long dmin = n / (r + 1); // exclusive
            if (dmin < 1)
                dmin = 1;
            sum = (sum - (dmax - dmin) % MOD * a(r) % MOD + MOD) % MOD;
            dmax = dmin;
        }
        aCache.put(n, sum);
        return sum;
    }

    private static long A(long n) {
        long sum = 0;
        for (long gmax = n; gmax >= 1; ) {
            long ng = n / gmax;
            long gmin = n / (ng + 1);
            if (gmin < 0)
                gmin = 0;
            long m = gmax % MOD;
            long c2 = powerMod(2, gmax, MOD) - m - 1;
            m = gmin % MOD;
            long c1 = powerMod(2, gmin, MOD) - m - 1;
            sum = (sum + (c2 - c1 + 2 * MOD) % MOD * (ng % MOD) % MOD * (ng % MOD) * 2) % MOD;
            gmax = gmin;
        }
        return sum;
    }

    private static long b(long n) {
        Long result = bCache.get(n);
        if (result != null)
            return result;
        long sum = B(n);
        for (long dmax = n; dmax > 1;) {
            long r      = n / dmax;
            long dmin   = n / (r + 1); // exclusive
            if (dmin < 1)
                dmin = 1;
            long c2     = dmax % MOD2 * ((dmax + 1) % MOD2) / 2 % MOD;
            long c1     = dmin % MOD2 * ((dmin + 1) % MOD2) / 2 % MOD;
            sum         = (sum - (c2 - c1 + 2 * MOD) % MOD * b(r) % MOD + MOD) % MOD;
            dmax        = dmin;
        }
        bCache.put(n, sum);
        return sum;
    }

    private static long B(long n) {
        long sum = 0;
        for (long gmax = n; gmax >= 1;) {
            long ng = n / gmax;
            long gmin = n / (ng + 1);
            if (gmin < 0)
                gmin = 0;
            long m  = gmax % MOD2;
            long c2 = (powerMod(2, gmax + 1, MOD2) - m - 2 + 2 * MOD2) % MOD2 * (m - 1 + MOD2) / 2 % MOD;
            m       = gmin % MOD2;
            long c1 = (powerMod(2, gmin + 1, MOD2) - m - 2 + 2 * MOD2) % MOD2*(m - 1 + MOD2) / 2 % MOD;
            sum     = (sum + (c2 - c1 + 2 * MOD) % MOD * (ng % MOD) % MOD * (ng % MOD) % MOD * ((ng + 1) % MOD) * 2) % MOD;
            gmax    = gmin;
        }
        sum = (MOD - sum) % MOD;
        return sum;
    }

    private static long c(long n) {
        Long result = cCache.get(n);
        if (result != null)
            return result;
        long sum = C(n);
        for (long dmax = n; dmax > 1;) {
            long r    = n/dmax;
            long dmin = n/(r + 1); // exclusive
            if (dmin < 1)
                dmin = 1;
            long c2   = dmax%MOD6*((dmax + 1)%MOD6)%MOD6*((2*dmax + 1)%MOD6)/6%MOD;
            long c1   = dmin%MOD6*((dmin + 1)%MOD6)%MOD6*((2*dmin + 1)%MOD6)/6%MOD;
            sum       = (sum - (c2 - c1 + 2*MOD)%MOD*c(r)%MOD + MOD)%MOD;
            dmax      = dmin;
        }
        cCache.put(n, sum);
        return sum;
    }

    private static long C(long n)
    {
        long sum = 0;
        for (long gmax = n; gmax >= 1;) {
            long ng   = n / gmax;
            long gmin = n / (ng + 1);
            if (gmin < 0)
                gmin = 0;
            long m  = gmax % MOD;
            long c2 = (((m - 2 + MOD) * m + 3) % MOD * powerMod(2, gmax, MOD) % MOD - ((((2 * m) % MOD6 + 3) * m % MOD6 + 1) * m % MOD6 + 18) / 6 % MOD + MOD) % MOD;
            m       = gmin % MOD;
            long c1 = (((m - 2 + MOD) * m + 3) % MOD * powerMod(2, gmin, MOD) % MOD - ((((2 * m) % MOD6 + 3) * m % MOD6 + 1) * m % MOD6 + 18) / 6 % MOD + MOD) % MOD;
            sum     = (sum + 2 * (c2 - c1 + 2 * MOD) % MOD * ng % MOD2 * (ng + 1) / 2 % MOD * ng % MOD2 * (ng + 1) / 2) % MOD;
            gmax    = gmin;
        }
        return sum;
    }

    public static void main(String[] args) {
        long x0     = powerMod(2, N % MOD * (N % MOD) + MOD, MOD); // all point sets, 2^n periodic 4*5^7 if n > 8
        long x1     = (1 + N % MOD * (N % MOD)) % MOD; // 0 and 1 point sets
        long x2  = (powerMod(2, N, MOD) - 1 - N%MOD - N%MOD2*(n%MOD2)/2%MOD + 3*MOD)%MOD*(2*N%MOD)%MOD; // 3+ colinear horizontal/vertical
        long a = a(N); // part 1 of diagonal
        long b = b(N); // part 2 of diagonal
        long c = c(N); // part 3 of diagonal
        long sum = (x0 - x1 - x2 - a * (N % MOD) % MOD * (N % MOD) % MOD - b * (N % MOD) % MOD - c + 5 * MOD) % MOD;
        System.out.println(sum);
    }
}
