/**
 * Created by aa on 01/02/17.
 */
public class p389 {
    private static final double[] dice = {20, 12, 8, 6, 4};

    private static double getVariance() {
        double a1, a2;
        double b1 = 1;
        double b2 = 0;
        for (int i = 0; i < dice.length; i++) {
            a1 = (dice[i] + 1) / 2;
            a2 = (dice[i] * dice[i] - 1) / 3;

            b2 = b2 * a1 + b1 * b1 * a2;
            b1 *= a1;
        }

        return b2 + b1 - b1 * b1;
    }

    public static void main(String[] args) {
        System.out.println(getVariance());
    }
}
