#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree{
private:
    vector<long long> A, st, lazy;
    int n;

    int left(int p) {return p << 1;}
    int right(int p) {return (p << 1) + 1;}

    void build(int p, int L, int R){
        if (L == R)
            st[p] = A[L];
        else{
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            st[p] = st[left(p)] + st[right(p)];
        }
    }

    long long rsq(int p, int L, int R, int i, int j){
        if (lazy[p]){
            st[p] += (R - L + 1) * lazy[p];
            
            if (L != R){
                lazy[left(p)] += lazy[p];
                lazy[right(p)] += lazy[p];
            }
            lazy[p] = 0;
        }

        if (i > R || j < L) return 0;
        if (L >= i && R <= j) return st[p];

        long long p1 = rsq(left(p), L, (L + R) / 2, i, j);
        long long p2 = rsq(right(p), (L + R) / 2 + 1, R, i, j);

        return p1 + p2;
    }
    
    void range_update(int p, int L, int R, int i, int j, int v){
        if (i > R || j < L) return;
        if (L >= i && R <= j){
            lazy[p] += v;
            return;
        }
        st[p] += (min(R, j) - max(i, L) + 1) * v;
        range_update(left(p), L, (L + R) / 2, i, j, v);
        range_update(right(p), (L + R) / 2 + 1, R, i, j, v);
    }

public:
    SegmentTree(const vector<long long>& _A){
        A = _A;
        n = A.size();
        lazy.assign(4 * n, 0);
        st.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    long long rsq(int i, int j){
        return rsq(1, 0, n - 1, i, j);
    }

    void range_update(int i, int j, int v){
        range_update(1, 0, n - 1, i, j, v);
    }

};

int main(){
    int N, Q;
    scanf("%d %d", &N, &Q);
    vector<long long> A(N);
    for (int i = 0; i < N; i++)
        scanf("%lld", &A[i]);

    SegmentTree st(A);

    for (int i = 0; i < Q; i++){
        char ch;
        scanf(" %c", &ch);
        if (ch == 'C'){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            st.range_update(a - 1, b - 1, c);
        }
        else if (ch == 'Q'){
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%lld\n", st.rsq(a - 1, b - 1));
        }
    }
}
