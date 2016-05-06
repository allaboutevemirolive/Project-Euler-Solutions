(* Quite easy to do since Mathematica already has these tools!*)

Unprotect[PalindromeQ[x_]] :=
  IntegerDigits[x] == Reverse[IntegerDigits[x]]
Max[Select[Flatten[Table[i*j, {i, 100, 999}, {j, 100, 999}]],
  PalindromeQ]]

(*The compiler does spew out telling us that some instances are protected but next output shows the result.*)
