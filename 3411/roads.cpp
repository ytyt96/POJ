#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

struct edge_t{
	int a, b, c, P, R;
};

struct state_t{
	state_t(int n_state, int n_city): state(n_state), city(n_city){}
	int state;
	int city;
};

int main(){
	int N, m;
	scanf("%d %d", &N, &m);
	vector<vector<edge_t> > cities(N);
	for (int i = 0; i < m; i++){
		edge_t edge;
		scanf("%d %d %d %d %d", &edge.a, &edge.b, &edge.c, &edge.P, &edge.R);
		edge.a--, edge.b--,	edge.c--;
		cities[edge.a].push_back(edge);
	}
		
	vector<bool> inQueue(N, false);
	queue<state_t> Queue;
	
	inQueue[0] = true;
	vector<vector<int> > cost(N, vector<int>(1 << m, INT_MAX));
	
	Queue.push(state_t(1, 0));
	cost[0][1] = 0;
		
	while (!Queue.empty()){
		state_t curr = Queue.front();
		Queue.pop();
		inQueue[curr.city] = false;

		for (int i = 0; i < cities[curr.city].size(); i++){
			edge_t& edge = cities[curr.city][i];

			int payment = edge.R;
		
			if (curr.state & (1 << edge.c))
				payment = edge.P;

			int n_state = curr.state | (1 << edge.b);

			if (payment + cost[curr.city][curr.state] < cost[edge.b][n_state]){
				cost[edge.b][n_state] = payment + cost[curr.city][curr.state];
				if (!inQueue[edge.b]){
					inQueue[edge.b] = true;
					Queue.push(state_t(n_state, edge.b));
				}
			}
		}
	}

	int min = INT_MAX;
	for (int i = 1; i < (1 << m); i++)
		if (cost[N - 1][i] < min)
			min = cost[N - 1][i];
	if (min != INT_MAX)
		printf("%d\n", min);
	else
		printf("impossible\n");
	return 0;
}
