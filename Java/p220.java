/**
 * Created by aa on 29/10/16.
 */
public class p220 {

    public static void main(String[] args) {
        long start = System.nanoTime();

        long[] res = getDisplacement(1000000000000L, 50);
        String result = res[2] + "," + res[3];

        long end = System.nanoTime();
        long runtime = end - start;
        System.out.println(result);
        System.out.println("Runtime: " + runtime / 1000000 + "ms (" + runtime
                + "ns)");
    }

    private static long[] getDisplacement(long distance, int generation) {
        if (generation == 0) {
            if (distance == 0) {
                return new long[] { 0, 1, 0, 0 };
            } else if (distance == 1) {
                return new long[] { 0, 1, 0, 1 };
            } else {
                throw new RuntimeException("Travel past end");
            }
        }

        long halflen = 1L << (generation - 1);
        boolean secondHalf = distance > halflen;

        if (secondHalf) {
            distance = halflen + halflen - distance;
        }

        long[] ret = getDisplacement(distance, generation - 1);
        long ex = ret[0], ey = ret[1];
        ret[0] = ex + ey;
        ret[1] = ey - ex;

        if (secondHalf) {
            long px = ret[2], py = ret[3];
            ret[2] = ex + ey - py;
            ret[3] = ey - ex + px;
        }

        return ret;
    }

}
