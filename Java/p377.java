package com.company;

/**
 * Created by aa on 21/01/17.
 * 
 * 13th power of an 18x18 matrix repeated 17 times.
 */
public class p377 {

    public static void main(String[] args) {
        System.out.println(solve());
    }

    public static long solve() {
        long mat[][] = new long[18][18];

        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 18; j++) {
                mat[i][j] = 0;
            }
        }

        for (int i = 0; i < 9; i++) {
            mat[0][i] = 1;
            if (i > 0) mat[i][i - 1] = 1;
            mat[9][i] = i + 1;
            mat[9][i + 9] = 10;
            if (i > 0) mat[9 + i][8 + i] = 1;
        }

        long sum = 0;

        for (int n = 0; n < 17; n++) {

            long mat2[][] = new long[18][18];
            for (int i = 0; i < 18; i++) {
                for (int j = 0; j < 18; j++) {
                    mat2[i][j] = mat[i][j];
                }
            }

            for (int k = 2; k <= 13; k++) {
                long mat3[][] = new long[18][18];
                for (int i = 0; i < 18; i++) {
                    for (int j = 0; j < 18; j++) {
                        mat3[i][j] = 0;
                        for (int l = 0; l < 18; l++) {
                            mat3[i][j] += mat2[i][l] * mat[l][j];
                            mat3[i][j] %= 1000000000;
                        }
                    }
                }

                mat2 = mat3;
            }
            mat = mat2;
            sum += mat2[9][0];
            sum %= 1000000000;
        }

        return sum;
    }
}
