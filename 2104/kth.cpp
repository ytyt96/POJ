#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<int>::iterator vit;
vector<int> A;

struct segment_tree {
    size_t n;
    vector<vector<int> > st;

    int left(int p) {
        return p << 1;
    }

    int right(int p) {
        return (p << 1) + 1;
    }

    void merge(int p, int lchild, int rchild) {
        st[p].assign(st[lchild].size() + st[rchild].size(), 0);
        size_t lpos = 0, rpos = 0, pos = 0;
        while (lpos < st[lchild].size() && rpos < st[rchild].size()) {
            if (st[lchild][lpos] < st[rchild][rpos]) 
                st[p][pos++] = st[lchild][lpos++]; 
            else
                st[p][pos++] = st[rchild][rpos++]; 
        }

        while (lpos < st[lchild].size())
            st[p][pos++] = st[lchild][lpos++]; 
        while (rpos < st[rchild].size())
            st[p][pos++] = st[rchild][rpos++]; 
    }

    void build(int p, int L, int R) {
        if (L == R) 
            st[p].push_back(A[L]);
        else {
            int lchild = left(p), rchild = right(p);
            build(lchild, L, (L + R) / 2);
            build(rchild, (L + R) / 2 + 1, R);
            merge(p, lchild, rchild);
        }
    }

    pair<int, bool> query(int p, int L, int R, int i, int j, int val) {
        if (i > R || j < L)
            return make_pair(-1, false);
        if (L >= i && R <= j) {
            vit it = lower_bound(st[p].begin(), st[p].end(), val);
            if (it != st[p].end() && *it == val)
                return make_pair(it - st[p].begin(), true);
            else
                return make_pair(it - st[p].begin(), false);
        }

        pair<int, bool> p1 = query(left(p), L, (L + R) / 2, i, j, val);
        pair<int, bool> p2 = query(right(p), (L + R) / 2 + 1, R, i, j, val);
        if (p1.first == -1)
            return p2;
        if (p2.first == -1)
            return p1;
        if (p1.second || p2.second)
            return make_pair(p1.first + p2.first, true);
        else
            return make_pair(p1.first + p2.first, false);
    }

    segment_tree() {
        n = A.size();
        st.assign(n * 4, vector<int>());
        build(1, 0, n - 1);
    }

    pair<int, bool> query(int i, int j, int val) {
        return query(1, 0, n - 1, i, j, val);
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    A.assign(n, 0);
    for (int i = 0; i < n; i++) 
        scanf("%d", &A[i]);
    segment_tree st;
    sort(A.begin(), A.end());
    while (m--) {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        i--, j--;
        int lower = 0, upper = n - 1, result;
        while (lower <= upper) {
            int mid = (lower + upper) >> 1;
            pair<int, bool> p = st.query(i, j, A[mid]);
            if (p.first == k - 1 && p.second) {
                result = A[mid];
                break;
            }

            if (p.first <= k - 1)
                lower = mid + 1;
            else
                upper = mid - 1;
        }
        printf("%d\n", result);
    }
    return 0;
}
