import java.util.Arrays;

/**
 * Created by aa on 10 February 2017.
 *
 * Green Hackenbush on Fibonacci trees.
 *
 * Colon Principle shows that when branches come together at a vertex, one may replace the branches
 * by a non-branching line of length equal to their NIM sum.
 *
 * http://www.math.ucla.edu/~tom/Game_Theory/comb.pdf
 *
 * So it's easy to write a function that computes the number of ways of pruning a tree to achieve
 * a specific value of the Sprague-Grundy function.
 *
 * The solution is the number of ways of pruning the root tree to obtain a Sprague-Grundy value of
 * zero.
 */
public class p400 {
    private static final int N = 10000;
    private static final long MOD = 1000000000000000000L;
    private static int[] sg = new int[N + 1];
    private static long[][] cache = new long[N + 1][N + 1];
    private static long nodes = 0;

    // How many ways can I prune T(n) to obtain Sprague-Grundy = target
    private static long prune(int n, int target) {
        if (target == -1) return 1; // Only move is pruning the whole sub-tree
        if (n == 1) return 0; // if n == 1, only target == -1 is possible... right?
        if (n == 2) return target == 0 ? 1 : 0;

        if (cache[n][target] < 0) {
            nodes++;
            long right = prune(n - 2, ((sg[n - 1] + 1) ^ target) - 1);
            long left = prune(n - 1, ((sg[n - 2] + 1) ^ target) - 1);

            cache[n][target] = (right + left) % MOD;
        }

        return cache[n][target];
    }

    public static void main(String[] args) {
        // initialise cache
        for (int i = 0; i < cache.length; i++)
            Arrays.fill(cache[i], -1L);

        // Compute Sprague-Grundy function for T(n)
        sg[1] = 0;
        sg[2] = 1;

        for (int i = 3; i < sg.length; i++)
            sg[i] = (1 + sg[i - 1]) ^ (1 + sg[i - 2]);

        // Result
        long result = prune(N, 0);
        System.out.println(nodes);
        System.out.println(result);
    }
}
