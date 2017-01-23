/**
 * Created by aa on 15/11/16.
 */
public class p58 {

    public static void main(String[] args) {
        double prob = 1;
        int dim = 19001;
        while (prob > 0.1d) {
            dim += 2;
            prob = grid(dim);
            System.out.printf("%d: %f\n", dim, prob);
        }
        System.out.printf("%d: %f\n", dim, prob);
    }

    public static double grid(int dim) {
        int[][] grid = new int[dim + 1][dim + 1];
        int space = 1;
        int j;
        int i = 1;
        int x = (dim - 1) / 2;
        int y = (dim - 1) / 2;
        long max = dim * dim + 1;
        grid[x][y] = i;
        while (i < max) {
            /* right */
            if (i < max) {
                for (j = 0; j < space; j++) {
                    y++;
                    i++;
                    grid[x][y] = i;
                }
            }
            /* down */
            if (i < max) {
                for (j = 0; j < space; j++) {
                    x++;
                    i++;
                    grid[x][y] = i;
                }
            }
            space++;
            /* left */
            if (i < max) {
                for (j = 0; j < space; j++) {
                    y--;
                    i++;
                    grid[x][y] = i;
                }
            }
            /* up */
            if (i < max) {
                for (j = 0; j < space; j++) {
                    x--;
                    i++;
                    grid[x][y] = i;
                }
            }
            space++;
        }
        int count = 0;
        for (i = 0; i < dim; i++) {
            if ((isPrime(grid[i][i]) == true))
                count++;
            if (isPrime(grid[i][dim - 1 - i]) == true)
                count++;
        }
        int bottom = (dim - 1) * 2 + 1;
        double prob = (double) count / (double) bottom;
        return prob;
    }

    public static boolean isPrime(int x) {
        Boolean prime = true;
        if (x == 2)
            prime = true;
        else if ((x < 2) | (x % 2 == 0))
            prime = false;
        else
            for (int i = 3; i < (int) Math.sqrt(x) + 1; i += 2) {
                if (x % i == 0) {
                    prime = false;
                    break;
                }
            }
        return prime;
    }

}
