allocatemem(128*2^20);

Q=1 000 000 007;

M=[-1-x,x;x,1-x];
m=[x,1-x]~;

/* easier part */
u(w,n)=Mod(Mod(1,Q)*M,x^(w+1))^n*m;
v(w,n)={local(t=u(w,n));polcoeff(lift(t[1]/t[2]),w)};
t(w,n)=Mod(n+1,Q)^w-v(w,n);
F(w,h)=(t(w,h-1)-t(w,h-2))/2;

result=F(100,10^12)+F(10000,10000);

/* now harder part */
u(n)=(Mod(1,Q)*M)^n*m;
v(n)={local(t=u(n));t[1]/t[2]};

R=v(99)-v(98);
M=matrix(199,199,i,j,if(i==1,-polcoeff(denominator(R),j),j==i-1));

w=10^12;

result-=(M^(w-198)*(Vec(lift(Mod(R,x^199)))~))[1]/2;
result+=(Mod(100,Q)^w-Mod(99,Q)^w)/2;

print(lift(result));

\q