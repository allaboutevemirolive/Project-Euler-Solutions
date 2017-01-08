srange(where,start,end,lim)=end-=max(0,where+end-start-lim);\
if(end<start,0,end*(end+1)/2-start*(start-1)/2);

f(n,lim)=local(res=0,where=fibonacci(n),start=0,end=(fibonacci(n)-1)\2);\
while(n>1,res+=srange(where,start,end,lim);n-=2;where+=end-start+1;\
start=end+1-fibonacci(n);end=(fibonacci(n)-1)\2);res

N=10^18;M=10^8;res=Mod(0,M);i=0;while(fibonacci(i)<=N,res+=f(i,N);i++);lift(res)
print(res)