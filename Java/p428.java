import java.util.*;

public class p428 {
    static int N = 1000000;
    static int window = 10000;

    static long twoPower(long index) {
        long power = 1;
        while (index-- > 0)
            power *= 2;
        return power;
    }

    public static void main(String[] args) {
        int limit = (int) (Math.sqrt(N) + 1);
        int[] primes = new int[(limit / 3) + 4];
        int numPrimes = 1;
        primes[0] = 2;
        int p = 3;
        // No sieve needed
        while (p <= limit) {
            boolean prime = true;
            for (int f = 0; f < numPrimes; f++) {
                if (p % primes[f] == 0) {
                    prime = false;
                    break;
                }
            }
            if (prime)
                primes[numPrimes++] = p;
        }
        System.out.println("Prime found");

        long sum = 0;
        int end = 1;
        int start;
        // Windowed sieve for counting prime factors
        while (end < N) {
            start = end;
            end = start + window;
            int[] numFactors = new int[window];
            int[] nums = new int[window];
            for (int i = start; i < end; i++) {
                numFactors[i - start] = 0;
                nums[i - start] = i;
            }

            for (int j = 0; j < numPrimes; j++) {
                int first = primes[j] * (int) Math.ceil((double) start / primes[j]);
                int last = primes[j] * (int) Math.ceil((double) end / primes[j]);
                int i = first;
                while (i < last) {
                    numFactors[i - start]++;
                    while (nums[i - start] % primes[j] == 0)
                        nums[i - start] /= primes[j];
                    i += primes[j];
                }
            }

            for (int i = start; i < end; i++) 
                if (nums[i - start] > 1)
                    numFactors[i - start]++;

            int st = start;
            // Steiner chain
            while (st < end && st <= N) {
                long m = twoPower(numFactors[st - start] - 1);
                int sub2 = 1;
                if (st % 3 == 2) 
                    sub2++;
                int sub1 = 1;
                if (st % 3 > 0)
                    sub1 *= 2;
                int sub3 = 0;
                if (st % 3 < 2)
                    sub3++;
                if (st % 2 > 0) {
                    sub2 *= 2;
                    sub1 *= 3;
                    if (st % 3 == 1)
                        sub2++;
                    sub3 *= 2;
                    if (st % 3 != 1)
                        sub3++;
                }

                int total = (sub1 + sub2) * (N / st) + sub3 * (N / (3 * st));
                if (st == 1) 
                    sum += total / 2;
                else 
                    sum += total * m;
                st++;
            }
        }
        System.out.println(2 * sum);
    }
}
