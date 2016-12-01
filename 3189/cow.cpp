#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <climits>

using namespace std;

int max_flow;
int residue[1100][1100];
int level[1100];

int V, s, t;

int augment(int u, int min_edge) {
    if (u == t) 
        return min_edge;

    int flow = 0;

    for (int v = 0; v < V; v++) {
        if (level[v] == level[u] + 1 && residue[u][v]) {
            flow = augment(v, min(min_edge, residue[u][v]));
            if (!flow)
                continue;
            residue[u][v] -= flow;
            residue[v][u] += flow;
            return flow;
        }
    }
    level[u] = -1;
    return flow;
}

void dinic() {
    max_flow = 0;
    while (true) {
        memset(level, -1, sizeof level);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < V; v++) {
                if (residue[u][v] && level[v] == -1) {
                    level[v] = level[u] + 1; 
                    q.push(v);
                }
            }
        }

        if (level[t] == -1)
            break;
        
        int new_flow = 0;
        while (true) {
            int flow = augment(s, INT_MAX);
            if (!flow)
                break;
            new_flow += flow;
        }
        if (new_flow == 0)
            break;
        max_flow += new_flow;
    }
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    vector<vector<int> > ranking(N, vector<int>(B));
    vector<int> capacity(B);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < B; j++) {
           scanf("%d", &ranking[i][j]);
           ranking[i][j]--;
        }

    for (int i = 0; i < B; i++)
        scanf("%d", &capacity[i]);

    s = N + B;
    t = N + B + 1;
    V = 2 + N + B;

    int lower = 1, upper = B, answer = B;
    while (lower <= upper) {
        int mid = (lower + upper) >> 1;

        for (int i = 0; i <= B - mid; i++) {
            memset(residue, 0, sizeof(residue));
            for (int j = 0; j < N; j++) 
                residue[s][j] = 1;
            for (int j = 0; j < N; j++) {
                for (int k = i; k <= i + mid - 1; k++)
                    residue[j][N + ranking[j][k]] = 1;
            }
            for (int j = 0; j < B; j++)
                residue[N + j][t] = capacity[j];
            dinic();  
            if (max_flow == N)
                break;
        }

        if (max_flow == N) {
            answer = mid;
            upper = mid - 1;
        }
        else
            lower = mid + 1;
    }
    printf("%d\n", answer);
}
