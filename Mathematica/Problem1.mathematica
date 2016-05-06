(* Quite easy to do since Mathematica already has these tools!*)

Total[Select[Range[999], Function[x, Mod[x, 5] == 0 || Mod[x, 3] == 0]]]
