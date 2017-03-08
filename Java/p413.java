package com.company;

import java.util.Arrays;

/**
 * Created by aa on 08/03/17.
 *
 * Building strings from left to right, where my state consists of the
 * suffices modulo d (because we're only interested in if this is 0, 1, or
 * more, so I just used 2 bitmasks), and whether we have had a substring divisible by
 *
 * Each number has (d+1)*d/2 substrings
 *
 * Don't need to worry about powers of 10 because they have multiple 0s.
 *
 * If they hit the same modulus twice, does that imply a child?
 * Consider 10 digits.  Mod is the same after the first digit,
 * but that says nothing about how many strings have mod 0.
 *
 * 1 digit:   all 9
 * 2 digits:  (even)(odd); 4*5 = 20
 * 3 digits:  101,110,111,112,122,202,220,222,221,211,311,322
 * 4 digits:
 */
public class p413 {
    public static void main(final String[] args) {
        long sum = 0L;
        sum += f(1, 0);
        sum += f(2, 1);
        sum += f(3, 1);
        sum += f(4, 1);
        sum += f(5, 3);
        sum += f(6, 5);
        sum += f(7, 5);
        sum += f(8, 5);
        sum += f(9, 1);
        sum += f(10, 1);
        sum += f(11, 10);
        sum += f(12, 5);
        sum += f(13, 4);
        sum += f(14, 3);
        sum += f(15, 8);
        sum += f(16, 13);
        sum += f(17, 12);
        sum += f(18, 11);
        sum += f(19, 2);
        System.out.println(String.valueOf(sum));
    }

    public static long f(final int n, final int u) {
        final boolean m2 = n % 2 == 0;
        final boolean m5 = n % 5 == 0;

        if ((u * (m2 ? (m5 ? 1 : 5) : (m5 ? 2 : 10))) % n != 1 % n)
            throw new IllegalArgumentException();

        final long[][][] caches = new long[n + 1][2][1 << n];
        for (int i = 1; i <= n; i++) {
            Arrays.fill(caches[i][0], -1L);
            Arrays.fill(caches[i][1], -1L);
        }

        final long count = count(n, u, m2, m5, caches, n, 1, 1, 0, false, 1);
        System.out.println(String.valueOf(count));
        return count;
    }

    private static long count(final int n, final int u, final boolean m2, final boolean m5, final long[][][] caches, final int depth, final int power, final int bits, final int overBits, final boolean gotChild, final int start) {
        if (depth == 0) {
            return gotChild ? 1L : 0L;
        }
        else {
            int foldedBits = bits;
            int foldedOverBits = overBits;
            int a = n;
            if (m2) {
                a /= 2;
                for (int i = 0; i < 2*a; i += a) {
                    foldedOverBits |= (foldedBits & ((1 << a) - 1)) & (foldedBits >> a);
                    foldedBits = (foldedBits & ((1 << a) - 1)) | (foldedBits >> a);
                    foldedOverBits = (foldedOverBits & ((1 << a) - 1)) | (foldedOverBits >> a);
                }
            }
            if (m5) {
                a /= 5;
                for (int i = 0; i < 5*a; i += a) {
                    foldedOverBits |= (foldedBits & ((1 << a) - 1)) & (foldedBits >> a);
                    foldedBits = (foldedBits & ((1 << a) - 1)) | (foldedBits >> a);
                    foldedOverBits = (foldedOverBits & ((1 << a) - 1)) | (foldedOverBits >> a);
                }
            }

            final int key = foldedOverBits * (1 << a) + foldedBits;
            if (caches[depth][gotChild ? 1 : 0][key] < 0) {
                long count;
                count = 0L;
                for (int digit = start; digit < 10; digit ++) {
                    int nextBits = foldedBits;
                    int nextOverBits = foldedOverBits;
                    if (m2) {
                        nextBits = explodeBits2(n, nextBits);
                        nextOverBits = explodeBits2(n, nextOverBits);
                    }
                    if (m5) {
                        nextBits = explodeBits5(nextBits);
                        nextOverBits = explodeBits5(nextOverBits);
                    }
                    nextBits = shiftBits(n, nextBits, (digit * power) % n);
                    nextOverBits = shiftBits(n, nextOverBits, (digit * power) % n);
                    if ((nextBits & 1) == 0)
                        count += count(n, u, m2, m5, caches, depth - 1, (u * power) % n, nextBits | 1, nextOverBits, gotChild, 0);
                    else if (!gotChild && (nextOverBits & 1) == 0)
                        count += count(n, u, m2, m5, caches, depth - 1, (u * power) % n, nextBits, nextOverBits, true, 0);
                }
                caches[depth][gotChild ? 1 : 0][key] = count;
            }
            return caches[depth][gotChild ? 1 : 0][key];
        }
    }

    private static int shiftBits(final int n, final int bits, final int shift) {
        long nextBits = (long)bits << (long)shift;
        nextBits |= (nextBits >> (long)n);
        nextBits &= (1L << (long)n) - 1L;
        return (int)nextBits;
    }

    private static int explodeBits5(int bits) {
        return explode5[bits & 15];
    }

    private static final int[] explode5 = new int[] {
            0x000000, 0x000001, 0x000020, 0x000021, 0x000400, 0x000401, 0x000420, 0x000421,
            0x008000, 0x008001, 0x008020, 0x008021, 0x008400, 0x008401, 0x008420, 0x008421 };

    private static int explodeBits2(final int n, final int bits) {
        return (explode2[(bits) & 31]) | (explode2[(bits >> 5) & 31] << 10);
    }

    private static final int[] explode2 = new int[] {
            0x000000, 0x000001, 0x000004, 0x000005, 0x000010, 0x000011, 0x000014, 0x000015,
            0x000040, 0x000041, 0x000044, 0x000045, 0x000050, 0x000051, 0x000054, 0x000055,
            0x000100, 0x000101, 0x000104, 0x000105, 0x000110, 0x000111, 0x000114, 0x000115,
            0x000140, 0x000141, 0x000144, 0x000145, 0x000150, 0x000151, 0x000154, 0x000155 };
}
