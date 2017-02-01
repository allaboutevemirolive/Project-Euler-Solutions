/**
 * Created by aa on 01/02/17.
 * Assume that the winning move is 'a'. From 'a' we can compute which S_k between 0 and 'n'
 * is the winning move, call this M_a(n)
 * Repeat this, for a+1, a+2, ..., b, to compute M_(a+1)(n), M_(a+2)(n), ..., M_b(n).
 * If M_a(n) = M_(a+1)(n) = ... = M_b(n), then it must be the solution M(n) we are looking for,
 * because one of the a <= i <= b must be a winning move.
 *
 * Next step is finding the range [a, b] having this property. Luckily it appears that any
 * 'a' large enough will do. Here I'm using b = 2^25 - 1, and checking all a <= i <= b.
 *
 * Takes about 12 minutes.
 */
public class p391v1 {
    private static final int N = 1 << 25;

    private static int getWin(int j, int n, int[] S) {
        int i = j;
        while (S[i] > n) {
            while (S[i] + n >= S[j]) --i;
            j = i;
        }

        return S[i];
    }

    public static void main(String[] args) {
        long sum = 0;
        int[] S = new int[N];
        for (int i = 1; i < N; ++i) S[i] = S[i - 1] + Integer.bitCount(i);
        for (int n = 1; n <= 1000; ++n) {
            int m = getWin(N - 1, n, S);
            for (int j = 2; S[N - j] >= S[N - 1] - n; ++j) {
                if (m != getWin(N - j, n, S)) throw new RuntimeException();
            }
            sum += m * m * m;
            System.out.println(n + " " + m + " " + sum);
        }
        System.out.println(sum);
    }
}
