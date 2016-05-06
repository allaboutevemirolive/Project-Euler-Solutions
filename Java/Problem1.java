public class Problem1 {
  public String run() {
    int total = 0;

    for (int i = 0; i < 1000; i++) {
      if (i % 5 == 0 || i % 3 == 0) {
        total += i;
      }

      return Integer.toString(total);
    }
  }
}
