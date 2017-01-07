<<<<<<< HEAD
public class Main {
  public static void main(String[] args) {
    Q1 problem1 = new Q1();   // Creating an instance so I can compile whatever
                              // method I want

    // c
    
  }
=======
import java.math.BigInteger;
import java.util.HashSet;
import java.util.Set;
// Problem 155 

public class Main {

    public static void main(String[] args) {
        System.out.println(new Main().run());
    }

    private static final int SIZE = 18;

    public static int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    // Warning: Running this solution requires about 600 MiB of memory
    public String run() {
        @SuppressWarnings("unchecked")
        // possible[i] holds all the possible capacitance values of a series/parallel
                // capacitor network that uses exactly i capacitors of 60 uF each
                Set<FastFraction>[] possible = new Set[SIZE + 1];
        Set<FastFraction> all = new HashSet<>();  // Union of every possible[i]
        possible[0] = new HashSet<>();
        possible[1] = new HashSet<>();
        possible[1].add(new FastFraction(60, 1));
        all.addAll(possible[1]);

        for (int i = 2; i <= SIZE; i++) {
            Set<FastFraction> poss = new HashSet<>();
            for (int j = 1; j <= i - j; j++) {
                for (FastFraction a : possible[j]) {
                    for (FastFraction b : possible[i - j]) {
                        poss.add(a.add(b));  // Parallel
                        poss.add(a.reciprocalAdd(b));  // Series
                    }
                }
            }
            possible[i] = poss;
            all.addAll(poss);
        }
        return Integer.toString(all.size());
    }



    // A fraction that uses int for storage and long for computation, but switches to BigInteger when necessary.
    private static final class FastFraction {

        public final int numerator;
        public final int denominator;
        public final Fraction bigFraction;


        public FastFraction(long num, long den) {
            if (den <= 0)
                throw new IllegalArgumentException();
            int n = (int)num;
            int d = (int)den;
            if (n == num && d == den) {
                int gcd = gcd(n, d);
                if (gcd > 1) {
                    n /= gcd;
                    d /= gcd;
                }
                numerator = n;
                denominator = d;
                bigFraction = null;
            } else {
                FastFraction temp = new FastFraction(new Fraction(BigInteger.valueOf(num), BigInteger.valueOf(den)));
                numerator = temp.numerator;
                denominator = temp.denominator;
                bigFraction = temp.bigFraction;
            }
        }


        public FastFraction(Fraction frac) {
            if (frac.numerator.bitLength() <= 31 && frac.denominator.bitLength() <= 31) {
                numerator = frac.numerator.intValue();
                denominator = frac.denominator.intValue();
                bigFraction = null;
            } else {
                numerator = 0;
                denominator = 0;
                bigFraction = frac;
            }
        }


        public Fraction toFraction() {
            if (bigFraction == null)
                return new Fraction(BigInteger.valueOf(numerator), BigInteger.valueOf(denominator));
            else
                return bigFraction;
        }


        public FastFraction add(FastFraction other) {
            if (bigFraction == null && other.bigFraction == null) {
                long num = (long)numerator * other.denominator + (long)other.numerator * denominator;
                long den = (long)denominator * other.denominator;
                return new FastFraction(num, den);
            } else
                return new FastFraction(toFraction().add(other.toFraction()));
        }


        // Returns 1 / (1/this + 1/other), also equal to (this * other) / (this + other).
        public FastFraction reciprocalAdd(FastFraction other) {
            if (bigFraction == null && other.bigFraction == null) {
                long num = (long)numerator * other.numerator;
                long den = (long)numerator * other.denominator + (long)other.numerator * denominator;
                return new FastFraction(num, den);
            } else {
                Fraction x = this.toFraction();
                Fraction y = other.toFraction();
                return new FastFraction(x.multiply(y).divide(x.add(y)));
            }
        }


        public boolean equals(Object obj) {
            if (!(obj instanceof FastFraction))
                return false;
            FastFraction other = (FastFraction)obj;
            if (bigFraction == null && other.bigFraction == null)
                return numerator == other.numerator && denominator == other.denominator;
            else
                return toFraction().equals(other.toFraction());
        }


        public int hashCode() {
            if (bigFraction == null)
                return numerator + denominator * 1204805;  // Some arbitrary constant to spread around the bits
            else
                return bigFraction.hashCode();
        }

    }

}

final class Fraction implements Comparable<Fraction> {

    public final BigInteger numerator;
    public final BigInteger denominator;

    public Fraction(BigInteger numer, BigInteger denom) {
        if (denom.signum() == 0)
            throw new ArithmeticException("Division by zero!");

        if (denom.signum() == -1) {
            numer = numer.negate();
            denom = denom.negate();
        }
        BigInteger gcd = numer.gcd(denom);
        if (!gcd.equals(BigInteger.ONE)) {
            numer = numer.divide(gcd);
            denom = denom.divide(gcd);
        }

        numerator = numer;
        denominator = denom;
    }

    public Fraction add(Fraction other) {
        return new Fraction(numerator.multiply(other.denominator).add(other.numerator.multiply(denominator)), denominator.multiply(other.denominator));
    }


    public Fraction subtract(Fraction other) {
        return new Fraction(numerator.multiply(other.denominator).subtract(other.numerator.multiply(denominator)), denominator.multiply(other.denominator));
    }


    public Fraction multiply(Fraction other) {
        return new Fraction(numerator.multiply(other.numerator), denominator.multiply(other.denominator));
    }


    public Fraction divide(Fraction other) {
        return new Fraction(numerator.multiply(other.denominator), denominator.multiply(other.numerator));
    }


    public boolean equals(Object obj) {
        if (!(obj instanceof Fraction))
            return false;
        Fraction other = (Fraction)obj;
        return numerator.equals(other.numerator) && denominator.equals(other.denominator);
    }


    public int compareTo(Fraction other) {
        return numerator.multiply(other.denominator).compareTo(other.numerator.multiply(denominator));
    }


    public int hashCode() {
        return numerator.hashCode() + denominator.hashCode();
    }


    public String toString() {
        return numerator + "/" + denominator;
    }
>>>>>>> PESolutions/master
}
