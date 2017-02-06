For[s = b = 0, b < 8,
  c = b;
  For[x = 2, c > 0,
   c = FromDigits[IntegerDigits[c, x], x + 1] - 1;
   x++];
  s += x - 2;
  a = x + 1;
  For[y = 0, y <= x,
   a = Mod[PowerMod[2, a, 10^9] a, 10^9];
   y++];
  s += a - 3;
  b++];
Mod[s, 10^9]
