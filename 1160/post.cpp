#include <iostream>
#include <cstdio>
#include <vector>
#include <climits>

using namespace std;

int main(){
	int V, P;
	scanf("%d %d", &V, &P);
	vector<int> positions(V);
	for (int i = 0; i < V; i++)
		scanf("%d", &positions[i]);
	vector<int> dist(V + 1);
	dist[0];
	for (int i = 0; i < V; i++)
		dist[i + 1] = dist[i] + positions[i];

	vector<vector<int>> dp(V + 1, vector<int>(P + 1, INT_MAX));
	dp[0][0] = 0;

	for (int i = 1; i <= V; i++)
		for (int j = 1; j <= P; j++)
			if (j <= i)
				for (int k = 0; k < j; k++){
					int dist_sum = 0;
					for (int l = k; l < i; l++){
						dist_sum += 
					}
					dp[i][j] = min(dp[i][j], dp[k][j - 1] + 
}
