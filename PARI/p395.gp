\\ Finds touching points of any tangent to any precision
\\ in O(prec * log(prec))

{
  prec=70;
  default(realprecision,prec);
  prec=.1^prec;

  C=[1-I;I]; D=[-I;1+I]; E=[9-37*I;16+37*I]/25;

  L=concat(C,E)~;
  R=concat(E,D)~;

  l=asin(3/5); r=asin(4/5); phi=l-r;

  dirs=[0,-Pi/2,Pi,Pi/2];  \\ top,right,bottom,left
  p=vector(4);

  for(i=1,#dirs,
    d=dirs[i];
    x=[0,1.]~;
      
    while(abs(x[2]-x[1])>prec,
      if(d<phi,
        x=R*x; d+=r; print1("R"),
        x=L*x; d-=l; print1("L")
      )
    );

    print("\n"x[1]);
    p[i]=x[1]
  );
    
  print((imag(p[1])-imag(p[3]))*(real(p[2])-real(p[4])));
}