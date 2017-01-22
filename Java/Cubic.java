/**
 * Created by aa on 23/12/16.
 *
 * Cubic formula: http://mathworld.wolfram.com/CubicFormula.html
 */
public class Cubic {
    private static final double TWO_PI = 2.0 * Math.PI;
    private static final double FOUR_PI = 4.0 * Math.PI;

    // Number of real roots
    public int nRoots;
    // First real root
    public double x1;
    // Second real root
    public double x2;
    // Third real root
    public double x3;

    public Cubic() { }

    // x^3 - (2^n * x^2) + n
   /* public void balanceCoefficients(double a, double d, int n) {
        double two_pow_n = Math.pow(2, n);

        solve(1, two_pow_n, 0, n);
    }*/

    /**
     * Solves a cubic equation with given coefficients.
     * The equation must be in the format ax^3 + bx^2 + cx + d
     * @param a coefficient of x^3
     * @param b coefficient of x^2
     * @param c coefficient of x
     * @param d constant coefficient
     */
    public void solve(double a, double b, double c, double d) {
        if (a == 0.0) {
            System.err.println("Cubic.solve(): a = 0");
        }

        double denom = a;
        a = b / denom;
        b = c / denom;
        c = d / denom;

        double a_over_3 = a / 3.0;
        double Q = (3 * b - a * a) / 9.0;
        double Q_CUBE = Q * Q * Q;
        double R = (9 * a * b - 27 * c - 2 * a * a * a) / 54.0;
        double R_SQR = R * R;
        double D = Q_CUBE + R_SQR;

        if (D < 0.0) {
            // 3 unequal real roots
            nRoots = 3;
            double theta = Math.acos(R / Math.sqrt(-Q_CUBE));
            double SQRT_Q = Math.sqrt(-Q);
            x1 = 2.0 * SQRT_Q * Math.cos(theta / 3.0) - a_over_3;
            x2 = 2.0 * SQRT_Q * Math.cos((theta + TWO_PI) / 3.0) - a_over_3;
            x3 = 2.0 * SQRT_Q * Math.cos((theta + FOUR_PI) / 3.0) - a_over_3;
            sortRoots();
        } else if (D > 0.0) {
            // One real root
            nRoots = 1;
            double SQRT_D = Math.sqrt(D);
            double S = Math.cbrt(R + SQRT_D);
            double T = Math.cbrt(R - SQRT_D);
            x1 = (S + T) - a_over_3;
            x2 = Double.NaN;
            x3 = Double.NaN;
        } else {
            // 3 real roots, at least 2 equal
            nRoots = 3;
            double CBRT_R = Math.cbrt(R);
            x1 = 2 * CBRT_R - a_over_3;
            x2 = x3 = CBRT_R - a_over_3;
            sortRoots();
        }
    }

    // Sorts roots into descending order
    private void sortRoots() {
        if (x1 < x2) {
            double tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        if (x2 < x3) {
            double tmp = x2;
            x2 = x3;
            x3 = tmp;
        }
        if (x1 < x2) {
            double tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
    }
}
