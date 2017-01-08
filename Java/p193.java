/**
 * Created by hampe on 26 October 2016.
 */
public class p193 {

    public static void main(String[] args) {
        byte[] mu = new byte[1 << 25];
        mu[1] = 1;
        for (int i = 2; i < mu.length; i++)
            mu[i] = -1;
        for (int d = 2; 2 * d < mu.length; d++)
            for (int i = 2 * d; i < mu.length; i += d)
                mu[i] -= mu[d];
        long n = 1L << 50;
        long s = 0;

        for (long d = 1; d < mu.length; d++)
            s += mu[(int) d] * (n / (d * d));
        System.out.println("Answer: " + s);
    }
}
