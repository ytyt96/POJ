#include <vector>
#include <utility>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

int K, C, M, N;
int adjmat[250][250];
int s, t;

vector<vector<int> > adjlist;

int residue[250][250];
int max_flow, flow;
vector<int> parent;

void augment(int v, int min_edge) {
    if (v == s) {
        flow = min_edge;
        return;
    }
    else if (parent[v] != -1) {
        int u = parent[v];
        augment(u, min(min_edge, residue[u][v]));
        residue[u][v] -= flow;
        residue[v][u] += flow;
    }
}

void Dinic() {
    max_flow = 0;
    while (true) {
        parent.assign(N, -1);
        vector<bool> visited(N, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t)
                break;
            for (int i = 0; i < adjlist[u].size(); i++) {
                int v = adjlist[u][i];
                if (!visited[v] && residue[u][v] > 0) {
                    parent[v] = u;
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        int new_flow = 0;
        for (int i = 0; i < adjlist[t].size(); i++) {
            int u = adjlist[t][i];
            if (residue[u][t] <= 0)
                continue;
            flow = 0;
            augment(u, residue[u][t]);
            residue[u][t] -= flow;
            residue[t][u] += flow;
            new_flow += flow;
        }
        if (new_flow == 0)
            break;
        max_flow += new_flow;
    }
}


int main() {
    scanf("%d %d %d", &K, &C, &M);

    for (int i = 0; i < K + C; i++) {
        for (int j = 0; j < K + C; j++) {
            int dist;
            scanf("%d", &dist);
            if (dist == 0)
                dist = INT_MAX / 4;
            adjmat[i][j] = adjmat[j][i] = dist;
        }
    }

    for (int i = 0; i < K + C; i++)
        adjmat[i][i] = 0;

    int lower = INT_MAX, upper = 0;
    for (int k = 0; k < K + C; k++)
        for (int i = 0; i < K + C; i++)
            for (int j = 0; j < K + C; j++) {
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                adjmat[j][i] = adjmat[i][j];
                lower = min(lower, adjmat[i][j]);
                upper = max(upper, adjmat[i][j]);
            }

    s = 0;
    t = K + C + 1;
    N = K + C + 2;

    while (lower <= upper) {
        int mid = (lower + upper) >> 1;

        memset(residue, 0, sizeof residue);
        adjlist.assign(N, vector<int>());
       
        for (int i = 0; i < K; i++) {
            adjlist[s].push_back(i + 1);
            adjlist[i + 1].push_back(s);
            residue[s][i + 1] = M;
        }
        for (int i = 0; i < K; i++)
            for (int j = K; j < K + C; j++)
                if (adjmat[i][j] <= mid) {
                    adjlist[i + 1].push_back(j + 1);
                    adjlist[j + 1].push_back(i + 1);
                    residue[i + 1][j + 1] = 1;
                }
        for (int i = K; i < K + C; i++) {
            adjlist[i + 1].push_back(t);
            adjlist[t].push_back(i + 1);
            residue[i + 1][t] = 1;
        }

        Dinic();
        if (max_flow >= C)
            upper = mid - 1;
        else
            lower = mid + 1;
    }
    printf("%d\n", upper + 1);

    return 0;
}
