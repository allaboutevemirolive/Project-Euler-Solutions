/**
 * Created by aa on 29/10/16.
 */
public class p219 {

    public static void main(String[] args) {
        long start = System.nanoTime();

        long counter = 0, f0 = 1, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
        long remaining = 999999999;

        while (remaining > 0) {
            if (remaining >= f0) {
                remaining -= f0;
                f1 += f0;
                f4 += f0;
                f0 = f1;
                f1 = f2;
                f2 = f3;
                f3 = f4;
                f4 = 0;
                counter++;
            } else {
                f0 -= remaining;
                f1 += remaining;
                f4 += remaining;
                remaining = 0;
            }
        }

        long result = f0 * counter + f1 * (counter + 1) + f2 * (counter + 2)
                + f3 * (counter + 3) + f4 * (counter + 4);
        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");
    }

}
