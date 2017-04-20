using System;

class p9 {
    static void Main() {
        for (int a = 1; a < 500; a++) {
            for (int b = 1; b < 500; b++) {
                if (a*a + b*b == (1000 - a - b) * (1000 - a - b)) {
                    Console.WriteLine(a*b*(1000-a-b));
                }
            }
        }
    }
}
