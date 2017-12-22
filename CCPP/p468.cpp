#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

struct Factor {
    int p;
    int e;
};

typedef vector<Factor> Factors;
typedef pair<int, int> P;

const int D = 1000000993;

vector<int> invs(1, 0);

P linear_diophantine(int a, int b, int c) {
    if (a == 1) return P(b + c, 1);
    else if (a == -1) return P(-b - c, 1);

    const int d = b / a;
    const int r = b % a;
    const P t = linear_diophantine(r, a, -c);

    return P(t.second + d * t.first, t.first);
}

int inverse(int n, int p) {
    const P t = linear_diophantine(n, p, 1);

    return t.first % p;
}

ll pow(ll n, int e, int d) {
    if (e == 0) return 1L;
    else if (e % 2 == 1)
        return n * pow(n, e - 1, d) % d;
    else {
        ll m = pow(n, e - 1, d) % d;
        return m * m % d;
    }
}

template<typename T> ostream& operator <<(ostream& os, const vector<T>& v) {
    if (!v.empty()) {
        os << v.front();
        for (auto p = v.begin() + 1; p != v.end(); ++p)
            os << " " << *p;
    }
    return os;
}

ostream& operator <<(ostream& os, const Factor& f) {
    os << f.p << "^" << f.e;
    return os;
}

#if 1
vector<Factors> make_factors_table(int N) {
    vector<int> a(N + 1);
    
    for (int k = 0; k <= N; ++k) a[k] = k;
    for (int p = 2; p * p <= N; ++p) {
        if (a[p] != p) continue;
        for (int m = p; m <= N; m += p) {
            if (a[m] == m) a[m] = p;
        }
    }

    vector<Factors> b(N + 1);

    for (int n = 2; n <= N; ++n) {
        const int p = a[n];
        int m = n / p;
        int e = 1;
        while (m % p == 0) {
            ++e;
            m /= p;
        }
        b[n].resize(b[m].size() + 1);
        Factor f = { p, e };
        b[n][0] = f;
        copy(b[m].begin(), b[m].end(), b[n].begin() + 1);
    }

    return b;
}

#else

vector<Factors> make_factors_table(int N) {
    vector<int> a(N + 1);
    for (int k = 0; k <= N; ++k) a[k] = k;

    vector<Factors> b(N + 1);
    for (int p = 2; p * p <= N; ++p) {
        if (a[p] != p) continue;
        for (int m = p; m <= N; m += p) {
            int e = 0;
            while (a[m] % p == 0) {
                ++e;
                a[m] /= p;
            }
            Factor f = { p, e };
            b[m].push_back(f);
        }
    }

    for (int n = 2; n <= N; ++n) {
        if (a[n] != 1) {
            Factor f = { a[n], 1 };
            b[n].push_back(f);
        }
    }

    return b;
}

#endif

template<typename T> int bin_search(double y0, int first, int last, const vector<T>& a) {
    if (first == last - 1) return first;

    const int mid = (first + last) / 2;
    const T y = a[mid];
    if (y < y0) return bin_search(y0, mid, last, a);
    else return bin_search(y0, first, mid, a);
}

int calc_mid(int first, int last, const vector<int>& ps) {
    if (first >= last - 2) return first;

    const double y2 = log(log((double)ps[last - 1]));
    const double y1 = first == 0 ? -1.0 : log(log((double)ps[first]));
    const double y3 = exp(exp((y1 + y2) / 2));

    return bin_search(y3, first, last, ps);
}

class Node {
    int p;
    ll m;
    ll num;
    ll sum;
    int count;
    Node *left;
    Node *right;

public:
    Node(const vector<int>& ps, int first, int last, int N) {
        const int mid = calc_mid(first, last, ps);
        p = ps[mid];
        m = 1;
        num = 1;

        if ((int)ps.size() == mid + 1)
            count = N - ps[mid] + 1;
        else
            count = ps[mid + 1] - ps[mid];

        if (first == mid)
            left = NULL;
        else 
            left = new Node(ps, first, mid, N);
        if (mid == last - 1)
            right = NULL;
        else
            right = new Node(ps, mid + 1, last, N);

        update_sum();
    }

    ~Node() {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
    }

    ll get_sum() const {
        return sum;
    }

    void mul(int q, int f) {
        num = num * f % D;
        if (q == p)
            m = m * f % D;
        else if (q < p)
            left->mul(q, f);
        else
            right->mul(q, f);
        update_sum();
    }

private:
    void update_sum() {
        const ll sum_left = left != NULL ? left->sum : 0L;
        const ll sum_right = right != NULL ? right->sum : 0L;
        const ll num_left = left != NULL ? left->num : 1L;
        sum = (sum_left + num_left * m % D * (count + sum_right)) % D;
    }
};

void update(Node * tree, int N, int r, const vector<Factors>& fss) {
    const Factors& fs1 = fss[N - r + 1];
    for (auto p = fs1.begin(); p != fs1.end(); ++p) {
        const int f = pow(p->p, p->e, D);
        tree->mul(p->p, f);
    }
    
    if (r == 1) return;
    const Factors& fs2 = fss[r];
    for (auto p = fs2.begin(); p != fs2.end(); ++p) {
        const int f = pow(invs[p->p], p->e, D);
        tree->mul(p->p, f);
    }
}

ll F(int N) {
    vector<Factors> fss = make_factors_table(N);
    vector<int> primes(1, 1);

    for (auto p = fss.begin(); p != fss.end(); ++p) {
        if (p->size() == 1 && p->front().e == 1)
            primes.push_back(p->front().p);
    }

    Node *tree = new Node(primes, 0, (int)primes.size(), N);
    ll s = tree->get_sum();

    for (int r = 1; r <= (N - 1) / 2; ++r) {
        update(tree, N, r, fss);
        s += tree->get_sum();
    }

    s *= 2;
    if (N % 2 == 0) {
        update(tree, N, N / 2, fss);
        s += tree->get_sum();
    }

    delete tree;
    return (s % D + D) % D;
}

int main() {
    const int N = 11111111;
    invs.reserve(N + 1);

    for (int i = 1; i <= N; ++i)
        invs.push_back(inverse(i, D));
    cout << F(N) << endl;

    return 0;
}
