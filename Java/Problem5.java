public class Problem5 {
  void p5() {
    BigInteger LCM = BigInteger.ONE;

    for (int i = 1; i <= 20; i++) {
      LCM = calcLCM(BigInteger.valueOf(i), LCM);

    }

    return LCM.toString();
  }


  void BigInteger calcLCM (BigInteger x, BigInteger y) {
    return x.divide(x.gcd(y)).multiply(y);
  }
}
