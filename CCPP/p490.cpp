#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000000LL;

ll f[130],  init[121];
ll c[9] = {0, 2, -1, 2, 1, 1, 0, -1, -1};

template<class T>
class Matrix {
    public:
        int m, n;
        ll *data;
        Matrix(int m, int n);
        Matrix(const Matrix<T> &matrix);
        const Matrix<T> &operator=(const Matrix<T> &A);
        const Matrix<T> operator*(const Matrix<T> &A);
        const Matrix<T> operator^(ll P);
        ~Matrix();
};

template<class T>
Matrix<T>::Matrix(int m, int n) {
    this -> m = m;
    this -> n = n;
    data = new T[m * n];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &A) {
    this -> m = A.m;
    this -> n = A.n;
    data = new T[m * n];
    for (int i = 0; i < m * n; i++) {
        data[i] = A.data[i];
    }
}

template<class T>
Matrix<T>::~Matrix() {
    delete [] data;
}

template<class T>
const Matrix<T> &Matrix<T>::operator=(const Matrix<T> &A) {
    if (&A != this) {
        delete [] data;
        m = A.m;
        n = A.n;
        data = new T[m * n];
        for (int i = 0; i < m * n; i++) {
            data[i] = A.data[i];
        }
    }
    return *this;
}

template<class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> &A) {
    Matrix C(m, A.n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < A.n; j++) {
            C.data[i * C.n + j] = 0;
            for (int k = 0; k < n; k++) {
                C.data[i * C.n + j] = C.data[i * C.n + j] + data[i * n + k] * A.data[k * A.n + j] % mod;
                C.data[i * C.n + j] %= mod;
            }
        }
    }
    return C;
}

template<class T>
const Matrix<T> Matrix<T>::operator^(ll P) {
    if (P == 1) return (*this);
    if (P % 2 == 1) return (*this) * ((*this) ^ (P - 1));
    Matrix B = (*this) ^ (P / 2);
    return B * B;
}

ll modpow(ll a, ll p, ll n) {
    ll r = a % n;
    if (p == 0) return ll(1);
    if (p == 1) return r;
    if (p % 2 == 1) {
        r = modpow(a, p / 2, n);
        r = r * r % n;
        return r * a % n;
    } else {
        r = modpow(a, p / 2, n);
        r = r * r % n;
        return r;
    }
}

int main() {
    f[0] = 0; f[1] = 1; f[2] = 1; f[3] = 1; f[4] = 2; f[5] = 6; f[6] = 14; f[7] = 28; f[8] = 56;
    for (int i = 9; i < 130; ++i) {
        f[i] = 0;
        for (int j = 1; j <= 8; ++j) {
            f[i] += (c[j] * f[i - j] % mod);
            f[i] %= mod;
        }
    }
    ll sum = 0;
    for (int i = 1; i < 130; ++i) {
        ll temp = modpow(f[i], 3L, mod);
        sum += temp;
        sum %= mod;
        f[i] = sum;
    }
    for (int i = 0; i < 121; i++) init[i] = f[121 - i];
    ll D[121] = {
                    7, 3, 110, 657, 2152, 999996931, 999947365, 999738698, 999846304, 1473808, 
                    2397069, 999688572, 15762353, 23085711, 952899689, 129068460, 562670682, 
                    851932061, 925364934, 130031754, 181205288, 87686835, 964000280, 496768346, 
                    949378103, 592790453, 984066471, 461616023, 493682996, 534003358, 117858828, 
                    848972716, 31578551, 893052564, 759018316, 522452116, 98186233, 564905872, 
                    978306373, 389103879, 508084833, 289490976, 748256014, 819373591, 686017061, 
                    776860091, 899843246, 328340796, 386233244, 314941444, 640807504, 678894846,
                    621474664, 314244247, 891948320, 69529805, 853017229, 358240235, 925156626,
                    746410706, 277606439, 297678410, 459762979, 506257373, 178806664, 334164340,
                    445924806, 601315661, 712591350, 723689155, 411068672, 74240988, 489231468, 
                    76239551, 638786462, 570675476, 566239663, 638513260, 790540872, 923844512, 
                    269402905, 120448364, 53308828, 574845412, 691863656, 727545828, 172412506,
                    397792876, 855112573, 789562138, 195771570, 236383884, 190641463, 572758925, 
                    51495474, 504302298, 760716994, 519113670, 299865824, 871977055, 40583768,
                    982079079, 6498090, 997737642, 2082694, 997996834, 925167, 999889150, 4595,
                    999996401, 902, 999997375, 3642, 999997641, 285, 999999999, 999999993, 
                    999999999, 2, 999999999, 1
                };
    ll A[121][121];
    for (int i = 0; i < 121; ++i) A[0][i] = D[i];
    for (int i = 1; i < 121; ++i) {
        for (int j = 0; j < 121; ++j) {
            if (i - 1 == j) A[i][j] = 1;
            else A[i][j] = 0;
        }
    }
    Matrix<ll> M(121, 121);
    for (int i = 0; i < 121; ++i) {
        for (int j = 0; j < 121; ++j) {
            int idx = 121 * i + j;
            M.data[14641 - idx - 1] = A[i][j];
        }
    }
    ll N = 100000000000000LL;
    if (N <= 121) {
        printf("S(%lli) mod %lli = %lli\n", N, mod, f[(int)N]);
    } else {
        Matrix<ll> res = M ^ (N - 121);
        ll ans = 0;
        for (int i = 0; i < 121; ++i) {
            int idx = 14641 - i - 1;
            ans += (res.data[idx] % mod * init[i] % mod);
        }
        ans %= mod;
        printf("S(%lli) mod %lli = %lli\n", N, mod, ans);
    }
    return 0;
}
