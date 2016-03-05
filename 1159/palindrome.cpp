#include <iostream>
#include <vector>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d\n", &N);
	vector<char> line(N);
	for (int i = 0; i < N; i++)
		scanf(" %c", &line[i]);

	vector<int> dp(N, INT_MAX), old(dp), old2(dp);
	for (int i = 0; i < N; i++)
		old[i] = 0;

	for (int i = 2; i <= N; i++){
		dp.assign(N, INT_MAX);
		for (int j = 0; j <= N - i; j++){
			int k = j + i - 1;
			if (line[j] == line[k]){
				if (j + 1 == k)
					dp[j] = 0;
				else
					dp[j] = min(dp[j], old2[j + 1]);
			}
			dp[j] = min(dp[j], old[j + 1] + 1);
			dp[j] = min(dp[j], old[j] + 1);
		}
		old2 = old;
		old = dp;
	}
	printf("%d\n", dp[0]);
	return 0;
}
