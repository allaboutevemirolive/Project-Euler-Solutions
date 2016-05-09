public class Problem4 {

  boolean ifPalindrome(String s) {
    int n = s.length();
    for (int i = 0; i < (n / 2); i++) {
      if (s.charAt(i) != s.charAt(n - i - 1)) {
        return false;
      }
    }

    return true;
  }


  void p4() {
    int palindrome = -1;

    for (int i = 100; i < 1000; i++) {
      for (int j = 100; j < 100; j++) {
        int product = i * j;
        if (ifPalindrome(product) && product > palindrome) {
          palindrome = product;
        }
      }
      return Integer.toString(palindrome);
    }
  }
}
