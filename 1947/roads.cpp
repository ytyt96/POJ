#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int N, P;
vector<vector<int> > adj_list;
vector<vector<int> > dp;

void dp_solve(int u, int p) {
    bool leaf = true;
    for (int i = 0; i < adj_list[u].size(); i++) {
        int v = adj_list[u][i];
        if (v != p) {
            leaf = false;
            dp_solve(v, u);
            for (int j = P; j >= 1; j--) {
                for (int k = 1; k < j; k++)
                    dp[u][j] = min(dp[u][j], dp[v][k] + dp[u][j - k] - 1);
            }
        }
    }
    if (leaf)
        dp[u][1] = 0;
}

int main() {
    scanf("%d %d", &N, &P);
    adj_list.assign(N, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dp.assign(N, vector<int>(P + 1, INT_MAX / 4));

    dp[0][1] = adj_list[0].size();
    for (int i = 1; i < N; i++) {
        dp[i][1] = adj_list[i].size() - 1;
    }
    dp_solve(0, -1);

    int ans = dp[0][P];
    for (int i = 1; i < N; i++)
        ans = min(ans, dp[i][P] + 1);
    printf("%d\n", ans);
    return 0;
}
