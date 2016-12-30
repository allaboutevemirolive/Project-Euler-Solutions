/**
 * Created by aa on 13/12/16.
 */
public class p119v2 {

    private final long[] power = new long[100];

    private int nextMinPower() {
        int minIndex = 2;

        for (int i = 3; i < power.length; i++) {
            if (power[i] < power[minIndex]) {
                minIndex = i;
                break;
            }

        }
        return minIndex;
    }

    private int sumOfDigits(long n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;

    }

    public static void main(String[] args) {
        p119v2 xd = new p119v2();

        for (int i = 2; i < xd.power.length; i++) {
            xd.power[i] = i;
            while (xd.power[i] < 10) {
                xd.power[i] *= i;
            }
        }

        int a = 0, i = 0;
        while (a < 30) {
            i = xd.nextMinPower();
            if (xd.sumOfDigits(xd.power[i]) == i) {
                a++;
            }
            xd.power[i] *= i;
        }

        System.out.println(xd.power[i] / i);
    }
}
