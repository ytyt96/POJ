#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

void flood(vector<vector<char>>& graph, int x, int y, int fuel, int u){
	if (x < 0 || y < 0 || x >= graph.size() || y >= graph.size() || fuel > u)
		return;

	if (graph[x][y] != '.' && graph[x][y] <= fuel + '0')
		return;

	graph[x][y] = fuel + '0';
	flood(graph, x - 1, y, fuel + 1, u);
	flood(graph, x + 1, y, fuel + 1, u);
	flood(graph, x, y - 1, fuel + 1, u);
	flood(graph, x, y + 1, fuel + 1, u);
}

int main(){
	int N;
	scanf("%d", &N);
	for (int s = 1; s <= N; s++){
		int u;
		scanf("%d", &u);
		printf("Scenario #%d:\n", s);
		int len = u * 2 + 1, fuel = u;
		bool midway = false;
		for (int i = 0; i < len; i++){
			printf("slice #%d:\n", i + 1);
			vector<vector<char>> graph(len, vector<char>(len, '.'));
			flood(graph, u, u, fuel, u);
			for (int j = 0; j < len; j++){
				for (int l = 0; l < len; l++)
					printf("%c", graph[j][l]);
				printf("\n");
			}
			if (!midway){
				fuel--;
				if (fuel == 0)
					midway = true;
			}
			else
				fuel++;
		}
		printf("\n");
	}
	return 0;
}
