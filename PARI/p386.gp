a(n)={
p=1;
v=factor(n)[,2]~;
for(i=1,#v,p=p*(1-x^(v[i]+1))/(1-x));
k=floor(bigomega(n)/2);
polcoeff(p,k)
}
sum(n=1,10000000000,a(n))