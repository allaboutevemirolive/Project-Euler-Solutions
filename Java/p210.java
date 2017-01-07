/**
 * Created by aa on 28/10/16.
 */
public class p210 {
    public static void main(String[] args) {

        long r = 1000000000, result = 0;
        result += 2 * r * (r + 1) + 1;
        result -= (2 * r + 1) * r / 4 + r + 1;
        result -= r / 2 + r / 4;
        result += countCircle(r * r / 32);
        result -= r / 4 - 1;

        System.out.println(result);

    }

    private static long countCircle(long r2) {
        long x = 0, x2 = 1;

        while (x2 < r2) {
            x2 += x + x + 1;
            x++;
        }

        long total = 0, y = 0, y2next = 1;

        while (true) {
            x--;
            x2 -= x + x + 1;

            while (x2 + y2next < r2) {
                y++;
                y2next += y + y + 1;
            }

            if (x < y) {
                break;
            }

            total += 8 * y + 4;
        }

        total += (2 * x + 1) * (2 * x + 1);

        return total;
    }

}
