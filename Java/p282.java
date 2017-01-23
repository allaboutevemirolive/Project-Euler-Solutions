import java.math.BigInteger;

/**
 * Created by aa on 06/11/16.
 */
public class p282 {

    public static void main(String[] args) {

        /*BigInteger x = ackermann(BigInteger.valueOf(1), BigInteger.valueOf(1000000));
        System.out.println("ackermann(1, 10000) = " + x);
*/
        for (BigInteger i = BigInteger.valueOf(0); i.compareTo(BigInteger.valueOf(6)) <= 0; i = i.add(BigInteger.ONE)) {
            BigInteger x = ackermann(i, i);

            System.out.println("Iteration " + i + ": x = " + x);
        }
    }

    /**
     * nigga
     * @param m
     * @param n
     * @return
     */
    public static BigInteger ackermann(BigInteger m, BigInteger n) {
        BigInteger r = null;

        if (m.compareTo(BigInteger.ZERO) == 0) {

            r = n.add(BigInteger.ONE);
            //System.out.println("r = " + r);

        }

        else if (m.compareTo(BigInteger.ZERO) > 0 && n.compareTo(BigInteger.ZERO) == 0) {

            r = ackermann(m.subtract(BigInteger.ONE), BigInteger.ONE);
            //System.out.println("r = " + r);

        }

        else if (m.compareTo(BigInteger.ZERO) > 0 && n.compareTo(BigInteger.ZERO) > 0) {

            r = ackermann(m.subtract(BigInteger.ONE), ackermann(m, n.subtract(BigInteger.ONE)));
            //System.out.println("r = " + r);

        }
        return r;
    }

    public static BigInteger ack(BigInteger m, BigInteger n) {
        return m.equals(BigInteger.ZERO)
                ? n.add(BigInteger.ONE)
                : ack(m.subtract(BigInteger.ONE),
                n.equals(BigInteger.ZERO) ? BigInteger.ONE : ack(m, n.subtract(BigInteger.ONE)));
    }
}

