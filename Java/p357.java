package com.company;

import java.lang.Math;
import java.util.*;

import com.company.Math.AKSPrimeAlgorithm.AKSPrime;
import com.company.Math.PrimeUtils;

class p357 {

    public static void main(String[] args) {
        p357 p = new p357();

        // This is the variable where the sum will be stored
        int sum = 821796607;
        // Iterate from 1 to 100,000,000
        for (int i = 3764362; i <= 100000000; i++) {
            // Get the list of divisors of number i
            // Some of the elements might have -1 in them, this means that d + dividend/d is not a prime
            int[] array = p.getPrimalDividend(i);
            // For all elements d in array[], if d + dividend/d is a prime then...
            if (p.isPrimalDividend(array)) {
                sum += i;
                System.out.printf("Iteration %d: IS a primal dividend.\n", i);
                System.out.println(Arrays.toString(array));
                System.out.println("Sum: " + sum);
            } else {
                //System.out.println("Iteration " + i + ": NOT a primal dividend.");
            }
        }

        System.out.println("Sum: " + sum);

        //System.out.println(Arrays.toString(p.getPrimalDividend(30)));
    }

    /**
     * Checks to see if an integer is a prime
     * @param n the number being investigated
     * @return true if n is a prime, false otherwise
     */
    boolean isPrime(int n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        long sqrtN = (long) Math.sqrt(n) + 1;

        for (long i = 6L; i <= sqrtN; i += 6) {
            if (n % (i - 1) == 0 || n % (i + 1) == 0) return false;
        }
        return true;
    }

    /**
     * Checks if the divisor is completely divisible by the dividend
     * @param dividend the dividend
     * @param divisor the divisor
     * @return true if divisor is divisible by dividend
     */
    boolean isDivisor(int dividend, int divisor) {
        if (dividend % divisor == 0) {
            return true;
        }
        return false;
    }

    /**
     * Puts all the divisors of a number in an array
     * @param dividend the number whose divisors we're collecting
     * @return an integer array with divisors of the dividend
     */
    int[] collectDivisors(int dividend) {
        int[] array = new int[dividend];
        // Divisor index
        int i = 1;
        // Goes through 0 to dividend
        for (int x = 0; x <= dividend; x++) {
            // If i is divisible by dividend then add i to array[]
            if (isDivisor(dividend, i)) {
                array[x] = i;
            }
            // Increment divisor index
            i++;
        }
        // Removes the zeroes that the array will have because of non-divisors
        // Array is initialized with zeroes apparently and we're only changing
        // the non-zero elements so we need to remove the zeroes
        array = cleanArray(array);
        return array;
    }

    /**
     * Removes zeroes from an array
     * @param array the integer array which is to be "cleaned"
     * @return the "cleaned" array without zeroes
     */
    int[] cleanArray(int[] array) {
        // All the non-zero elements will be added to this list
        List<Integer> list = new ArrayList<>();

        // Go through each element of array[]
        for (int i = 0; i < array.length; i++) {
            // If array[i] has a zero then ignore it...
            if (array[i] == 0) {
                continue;
            }
            // ... Otherwise add the non-zero to a list
            list.add(array[i]);
        }
        // Convert the list into an integer array
        int[] cleanArray = new int[list.size()];
        for (int i = 0; i < cleanArray.length; i++) {
            cleanArray[i] = list.get(i);
        }
        return cleanArray;
    }

    /**
     * Checks if an array has -1 in it (has deeper meaning to it in this program)
     * @param primeArray the array being inspected
     * @return true if no -1's have been found in the array, false otherwise
     */
    boolean isPrimalDividend(int[] primeArray) {
        // Inspects the array for "-1" which means that *every* divisor d
        // of dividend where d + dividend/d is not prime. We don't need this.
        for (int i = 0; i < primeArray.length; i++) {
            if (primeArray[i] == -1) {
                return false;
            }
        }

        return true;
    }

    /**
     * Gets the divisors of a dividend and checks if every divisor
     * d of that dividend d + dividend/d is a prime. If it is then they are
     * add to an array, if the divisor d is not then "-1" is added
     * in the array
     * @param dividend the dividend whose divisors we will examine
     * @return an integer array with "-1"'s and divisor d where d + dividend/d is prime
     */
    int[] getPrimalDividend(int dividend) {

        // Gets all the divisors of dividend
        int[] array = collectDivisors(dividend);
        // This is where all the divisor d where d + dividend/d is prime will be stored
        List<Integer> primalDividends = new ArrayList<>();
        // Iterate through all of array[]'s elements - 1
        for (int i = 0; i <= array.length - 1; i++) {
            int d = array[i]; // Gets the array element d
            int dx = d + (dividend / d); // Calculates what d + dividend/d is

            //PrimeUtils.Context c = new PrimeUtils.Context();

            // If that value is a prime then...
            if (isPrime(dx)) {
                primalDividends.add(dx); // Add it to the list
            } else {
                primalDividends.add(-1); // Otherwise add -1 to the list
            }
        }
        // Convert the list to an integer array
        int[] primes = new int[primalDividends.size()];
        for (int i = 0; i < primes.length; i++) {
            primes[i] = primalDividends.get(i);
        }

        return primes;
    }

}