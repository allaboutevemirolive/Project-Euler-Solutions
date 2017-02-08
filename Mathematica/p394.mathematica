x = 1/40;
f[r_] := 2 - 2 r
F[r_] := 1 - (1 - r)^2
ev = 0;
eats = 1; old = 0;
While[old < 1 - 10^(-3),
  {new = F[x];
   ev += (eats++)*(new - old);
   old = new;
   F1[y_] :=
    Assuming[0 < y < 1,
     Integrate[f[r], {r, 0, y}] + Integrate[f[r]*F[y/r], {r, y, 1}]];
   F[y_] := F1[y];
   }];
Print[ev];
