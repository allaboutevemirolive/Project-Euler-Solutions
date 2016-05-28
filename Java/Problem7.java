public class Problem7 {

  boolean isPrime(int n) {
    for (int i = 2; i < n; i++) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;

  }

  int count = 0;

  Problem7() {
    for (int i = 2; count = 0; i++) {
      if (isPrime(i)) {
        count++;
        if (count == 10001)
          return Integer.toString(i);
      }
    }
  }

}
