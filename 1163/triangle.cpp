#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	vector<vector<int> > numbers(N, vector<int>(N, 0)), dp(numbers);
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= i; j++)
			scanf("%d", &numbers[i][j]);

	dp[0][0] = numbers[0][0];
	for (int i = 1; i < N; i++)
		for (int j = 0; j <= i; j++){
			if (j == 0)
				dp[i][0] = dp[i - 1][0] + numbers[i][j];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + numbers[i][j];
		}
	int ans = 0;
	for (int i = 0; i < N; i++)
		ans = max(ans, dp[N - 1][i]);
	printf("%d\n", ans);
	return 0;
}
