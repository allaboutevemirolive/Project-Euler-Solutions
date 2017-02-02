F(x)={
  b=x; d=1; A=x;
  for(i=1,N/2, 
    e=d; d=sqrt(1-b*b); 
    a=b; b=2*b+(d*e-1)/b;  
    A+=(b-a)*d; 
    if(b>1,break());
  );
  b
}

\p 70 
{
  N=400; 
  solve(x=1/N,.8,F(x)-1);
  4*A
}