import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class P524 {
    private static void solve() {
        long x = 1;
        for (int i = 0; i < 12; i++) x = x * 12;
        long min = Long.MAX_VALUE;
        tr(Long.toBinaryString(x));
        int y = 63 - Long.numberOfLeadingZeros(x);
        int q = Long.bitCount(x);
        int[] bs = new int[q];
        int p = 0;
        for (int i = 0; i <= y; i++) {
            if (x << ~i < 0) bs[p++] = i;
        }

        outer:
        do {
            List<Integer> list = new ArrayList<>();
            list.add(0);
            int t = 0;
            for (int i = 0; t < p; i++) {
                if (i > y) continue outer;
                if (bs[t] <= i) {
                    int s = bs[t];
                    for (int j = 0; j < list.size(); j++) {
                        if (list.get(j) >= s) {
                            list.set(j, list.get(j) + 1);
                        }
                    }
                    list.add(s);
                    t++;
                } else {
                    list.add(i + 1);
                }
            }
            int[] u = new int[list.size()];
            for (int i = 0; i < list.size(); i++) u[i] = list.get(i);
            long v = encPerm(u);
            if (v < min) {
                min = v;
                tr(bs, v);
                tr(list);
            }
        } while (nextPermutation(bs));
        tr(min);
    }

    public static boolean nextPermutation(int[] a) {
        int n = a.length;
        int i;
        for (i = n - 2; i >= 0 && a[i] >= a[i + 1]; i--)
            ;
        if (i == -1) return false;
        int j;
        for (j = i + 1; j < n && a[i] < a[j]; j++)
            ;
        int d = a[i];
        a[i] = a[j - 1];
        a[j - 1] = d;
        for (int p = i + 1, q = n - 1; p < q; p++, q--) {
            d = a[p];
            a[p] = a[q];
            a[q] = d;
        }
        return true;
    }

    public static long encPerm(int[] a) {
        int n = a.length;
        long used = 0;
        long ret = 0;
        BigInteger rets = BigInteger.ZERO;
        for (int i = 0; i < n; i++) {
            ret = ret * (n - i) + a[i] - Long.bitCount(used & ((1L << a[i]) - 1));
            rets = rets.multiply(BigInteger.valueOf(n - i)).add(BigInteger.valueOf(a[i] - Long.bitCount(used & ((1L << a[i]) - 1))));
            used |= 1L << a[i];
        }
        if (used + 1 != 1L << a.length) return -1;
//		return rets.add(BigInteger.ONE));
        return ret + 1;
    }

    public static void main(String[] args) {
        solve();
    }

    private static void tr(Object... o) {
        System.out.println(Arrays.deepToString(o));
    }
}
