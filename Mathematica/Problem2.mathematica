(* Quite easy to do since Mathematica already has these tools!*)

const = 0;
For[i = 0, (f = Fibonacci[i]) <= 4000000, i++,
  If[EvenQ[f],
    const += f]]
const 
