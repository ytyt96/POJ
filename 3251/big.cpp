#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#define DIFF 0.0000000000001

using namespace std;

int my_round(double x){
	return floor(x + 0.5);
}

int main(){
	int N;
	scanf("%d", &N);
	char grid[110][110];
	int cows[11000][2];
	
	int count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++){
			scanf(" %c ", &grid[j][i]);
			if (grid[j][i] == 'J'){
				cows[count][0] = j, cows[count][1] = i;
				count++;
			}
		}
	long long length = 0;
	int upper_line = 0, lower_line = 0;
	bool found = false;
	for (int i = 0; i < count - 1; i++){
		if (found && (count + 8 - cows[i][1] < upper_line - lower_line))
			break;
		
		for (int j = count - 1; j > i; j--){
			if (found && (cows[j][1] - cows[i][1] + 8 < upper_line - lower_line))
				break;
			
			double mid_x = (cows[i][0] + cows[j][0]) / 2.0, mid_y = (cows[i][1] + cows[j][1]) / 2.0;
			double x1 = mid_x - (cows[j][1] - mid_y), x2 = mid_x + (cows[j][1] - mid_y),
				   y1 = mid_y + (cows[j][0] - mid_x), y2 = mid_y - (cows[j][0] - mid_x);
			if (my_round(x1) - x1 > DIFF)
				continue;
			if (my_round(y1) - y1 > DIFF)
				continue;
			if (my_round(x2) - x2 > DIFF)
				continue;
			if (my_round(y2) - y2 > DIFF)
				continue;
			if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
				continue;
			if (x1 >= N || x2 >= N	|| y1 >= N || y2 >= N)
				continue;
			if (grid[my_round(x1)][my_round(y1)] != 'B' && grid[my_round(x2)][my_round(y2)] != 'B')
				if (!(grid[my_round(x1)][my_round(y1)] == '*' && grid[my_round(x2)][my_round(y2)] == '*')){
					long long n_len = pow(x1 - x2, 2) + pow(y1 - y2, 2);
					if (n_len > length){
						length = n_len;
						found = true;
						lower_line = cows[i][1];
						upper_line = cows[j][1];
					}
				}
		}
	}
	printf("%lld\n", length / 2);
	return 0;
}
