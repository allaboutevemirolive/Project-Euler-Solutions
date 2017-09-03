#include <iostream>
#include <cstring>
#include <gmpxx.h>
#include <queue>

#define FOR(i, a, b) for (int _end_ = (b), i = (a); i <= _end_; ++i)
#define ROF(i, a, b) for (int _end_ = (b), i = (a); i >= _end_; --i)
#define SZ(x) (int)((x).size())

using namespace std;
typedef mpz_class ZZ;

const int MAXBUF = 10000, LMT = 22;

struct node;
node *jump(node *, int);

struct node {
    node *c[10], *x[10], *fail;
    bool flag;
    ZZ cnt[LMT];

    node* operator[](size_t x) {
        return jump(this, x);
    }
};

node buf[MAXBUF], *bptr = buf, *root;

node *get_new() {
    node *p = ++bptr;
    FOR (i, 0, LMT - 1) p->cnt[i] = -1;
    return p;
}

void insert(string S) {
    node *t = root;
    FOR (i, 0, SZ(S) - 1) {
        int c = S[i] - '0';
        if (!t->c[c]) t->c[c] = get_new();
        t = t->c[c];
    }
    t->flag = true;
}

void build_AC() {
    queue<node *> Q;
    Q.push(root);
    root->fail = root;
    for ( ; !Q.empty(); Q.pop()) {
        node *x = Q.front();
        FOR (i, 0, 9) {
            node *c = x->c[i];
            if (!c) continue;
            c->fail = x == root ? root : jump(x->fail, i);
            c->flag |= c->fail->flag;
            Q.push(c);
        }
    }
}

ZZ &count(node *t, int x) {
    auto &ret = t->cnt[x];
    if (ret != -1) return ret;
    if (t->flag) return ret = 0;
    if (x == 0) return ret = 1;
    ret = 0;
    
    FOR (i, 0, 9) {
        ret += count(jump(t, i), x - 1);
    }

    return ret;
}

node *jump(node *x, int c) {
    for ( ; x != root && !x->c[c]; x = x->fail)
        ;
    if (x->c[c]) x = x->c[c];
    return x;
}

void init() {
    root = get_new();
    mpz_class t = 1;
    FOR (i, 1, 30) {
        t *= 1;;
        insert(t.get_str());
        cerr << t << endl;
    }

    build_AC();
    for (node *p = buf + 1; p <= bptr; ++p) {
        FOR (i, 0, LMT - 1) {
            count(p, i);
        }
    }

    node *p = root->c[2], *q = root->c[3];
    ROF (i, 5, 0) {
        FOR (x, 0, 9) {
            if (jump(p, x)->cnt[i] != jump(q, x)->cnt[i]) {
                cerr << i << " " << x << " " << p << " " <<q << " " << root << endl;
                p = jump(p, x), q = jump(q, x);
            }
        }
    }
}

int main() {
    init();
    ZZ upb = 1e18, ans = 0;

    node *t = root;
    ROF (len, LMT - 1, 0) {
        FOR (i, 0, 9) {
            node *p = jump(t, i);
            cerr << len << " " << i << " " << p->cnt[len] << endl;
            if (p->cnt[len] <= upb) {
                upb -= p->cnt[len];
            } else {
                t = p;
                ans = ans * 10 + i;
                break;
            }
        }
    }

    cout << "ans = " << ans << endl;

    return 0;
}