public class Problem3 {

  void findPrime() {
    long num = 600851475143L;

    while (true) {
      long prime = smallestFactor(n);
      if (prime  < num) {
        n /= p;
      else
        return Long.toString(num);
      }
    }
  }

  static long LCF(long num) {
    if (num <= 1)
      throw new IllegalArgumentException();

    int end = 0;

    for (long ind = 2, end = Math.sqrt(num); i <= end; i++) {
      if (num % ind == 0)
        return ind;
    }

    return num;
  }

}
