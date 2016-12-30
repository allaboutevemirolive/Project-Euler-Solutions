import java.math.BigInteger;
import java.util.TreeSet;
/**
 * Created by aa on 29/10/16.
 */
public class p221 {

    public static void main(String[] args) {
        long start = System.nanoTime();

        BigInteger result = BigInteger.ZERO;
        int count = 150000;
        TreeSet<Triplet> tset = new TreeSet<Triplet>();
        tset.add(new Triplet(1, 2, 3));

        while (count-- > 0) {
            Triplet t = tset.pollFirst();
            result = t.bigInt;
            tset.add(t.ret1());
            tset.add(t.ret2());
        }

        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");
    }

    private static class Triplet implements Comparable<Triplet> {
        long a, b, c;
        BigInteger bigInt;

        Triplet(long a, long b, long c) {
            this.a = a;
            this.b = b;
            this.c = c;
            bigInt = convert(a).multiply(convert(b)).multiply(convert(c));
        }

        public Triplet ret1() {
            return new Triplet(b, 2 * b - a, 2 * b + c);
        }

        public Triplet ret2() {
            return new Triplet(c, 2 * c - a, 2 * c + b);
        }

        @Override
        public int compareTo(Triplet t) {
            return bigInt.compareTo(t.bigInt);
        }

        public BigInteger convert(long l) {
            return BigInteger.valueOf(l);
        }
    }

}
