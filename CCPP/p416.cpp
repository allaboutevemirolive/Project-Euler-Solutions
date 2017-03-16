/*
Dynamic Programming.
Considering M=2m sequences of {0,1} of length n with no more than
2 consecutive zeros. Each state consists of the number a of sequences
ending in 1, the number b of sequences ending in 10 ( => number c of
sequences ending in 100 equals M-a-b ) and whether we had already passed
some index where all sequences had been zero. Then fast exponentiation
of modded (M+1)*(M+2) x (M+1)*(M+2) matrix.
But that isn't fast enough. So...

I tried another approach. The transition matrix T is a block
matrix ( A 0 ; B A ), with equal diagonal blocks and upper right block
all zeros. So every power of it is a block matrix of same structure too.
The matrix multiplication algorithm can be slightly modified, to deal
with such block matrices

|A 0| x |C 0| = |   AC     0|
|B A|   |D C|   |BC + AD  AC|

So it only takes 3/8 of time.

*/

#include<iostream>
using namespace std;
typedef long long LL;

#define m 10
#define n 1000000000000ll

#define M (2*m)
#define D ((M+1)*(M+2)/2)

#define MOD 1000000000
#define MOD2 (LL(MOD)*MOD)

struct Matrix{
  LL v[D][D];
  Matrix() {}
  Matrix(int a) {
	  fill_n((LL*)v, D * D, 0); for(int i=0;i<D;i++) v[i][i]=a;
  }

  LL* operator[](int i) {
	  return v[i];
  }
  const LL* operator[](int i) const {
	  return v[i];
  }
};

Matrix operator+(const Matrix &a, const Matrix &b) {
  Matrix c;
  for(int i = 0; i < D; i++) for(int j = 0; j < D; j++)
    if((c[i][j] = a[i][j] + b[i][j]) >= MOD) c[i][j] -= MOD;
  return c;
}
Matrix operator*(Matrix &a, Matrix &b) {
  Matrix c;
  for(int i=0;i<D;i++) for(int j=0;j<D;j++) {
    LL s=0;
    for(int k=0;k<D;k++) {
      s+=a[i][k]*b[k][j];
      if(s>=MOD2) s-=MOD2;
    }
    c[i][j]=s%MOD;
  }
  return c;
}

struct MatrixAB{
  Matrix A,B;
  MatrixAB(int a):A(a),B(0) {};
  MatrixAB(const Matrix &A,const Matrix &B):A(A),B(B) {}
};
MatrixAB operator*(MatrixAB &a, MatrixAB &b) {
  return MatrixAB( a.A*b.A,  a.B*b.A + a.A*b.B );
}
MatrixAB operator^(MatrixAB &a, LL k) {
  MatrixAB x(1),p(a);
  for(;k; k>>=1, p=p*p) if(k&1) x=x*p;
  return x;
}

int idx(int a,int b) { return a*(M+1)-a*(a-1)/2+b; }  // index in transition T
int add(Matrix &A, int i,int j, int a) { if((A[i][j]+=a)>=MOD) A[i][j]-=MOD; }

int main() {

  MatrixAB T(0);
  int C[M+1][M+1], i,j, a,b, d,e, a_,b_, k;

  for(i=0;i<=M;i++) {
    C[i][0]=C[i][i]=1;
    for(j=1;j<i;j++)  C[i][j] = C[i-1][j-1] + C[i-1][j];
  }

  for(a=0;a<=M;a++) for(b=0;b<=M-a;b++)
    for(d=0;d<=a;d++) for(e=0;e<=b;e++) {
      k = LL(C[a][d])*C[b][e]%MOD;
      a_ = (M-a-b)+d+e;
      b_ = a-d;
      add(a_?T.A:T.B, idx(a_,b_),idx(a,b), k);
    }

  T=T^n;

  LL result = T.A[D-1][0] + T.B[D-1][0];
  if(result>=MOD) result-=MOD;
  cout<<result<<endl;
}
