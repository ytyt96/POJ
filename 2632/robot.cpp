#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

const int move[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct robot_t{
	int face;
	int x, y;
};

struct order_t{
	int robot, repeat;
	char action;
};

int hash(char face){
	if (face == 'N')
		return 0;
	if (face == 'E')
		return 1;
	if (face == 'S')
		return 2;
	else
		return 3;
}

void readData(vector<vector<pair<bool, int> > >& grid, vector<robot_t>& robots, vector<order_t>& orders, int N, int M){
	for (int i = 0; i < N; i++){
		int x, y;
		char face;
		scanf("%d %d %c", &x, &y, &face);
		x--;
		y--;
		robots[i].x = x;
		robots[i].y = y;
		grid[x][y] = make_pair(true, i);
		robots[i].face = hash(face);
	}
	for (int i = 0; i < M; i++){
		int robot, repeat;
		char action;
		scanf("%d %c %d", &robot, &action, &repeat);
		robot--;
		orders[i].robot = robot;
		orders[i].action = action;
		orders[i].repeat = repeat;
	}
}

int main(){
	int K;
	scanf("%d", &K);
	while (K--){
		int A, B, N, M;
		scanf("%d %d", &A, &B);
		scanf("%d %d", &N, &M);
		vector<robot_t> robots(N);
		vector<order_t> orders(M);
		vector<vector<pair<bool, int > > > grid(A, vector<pair<bool, int> >(B, make_pair(0, false)));
		readData(grid, robots, orders, N, M);

		bool wall_crash = false, robot_crash = false;
		int crash1, crash2;
		for (int i = 0; i < M; i++){
			const order_t& order = orders[i];
			robot_t& robot = robots[orders[i].robot];
			if (order.action == 'L')
				robot.face = (robot.face + 4 -( order.repeat % 4)) % 4;
			if (order.action == 'R')
				robot.face = (robot.face + (order.repeat % 4)) % 4;
			if (order.action == 'F'){
				int &x = robot.x, &y = robot.y;
				grid[x][y].first = false;
				grid[x][y].second = 0;
				for (int j = 0; j < order.repeat; j++){
					x += move[robot.face][0];
					y += move[robot.face][1];
					if (x < 0 || y < 0 || x >= A || y >= B){
						crash1 = order.robot;
						wall_crash = true;
						break;
					}
					if (grid[x][y].first){
						crash1 = order.robot;
						crash2 = grid[x][y].second;
						robot_crash = true;
						break;
					}
				}	
				if (wall_crash || robot_crash)
					break;
				grid[x][y].first = true;
				grid[x][y].second = order.robot;
			}			
			
		}
		if (wall_crash)
			printf("Robot %d crashes into the wall\n", crash1 + 1);
		else if (robot_crash)
			printf("Robot %d crashes into robot %d\n", crash1 + 1, crash2 + 1);
		else
			printf("OK\n");
	}
	return 0;
}
