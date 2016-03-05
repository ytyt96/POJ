#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int do_dp(const vector<int>& numbers){
	int n = numbers.size();
	vector<vector<int> > dp(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		dp[i][i] = numbers[i];
	
	for (int i = 0; i < n - 1; i++)
		dp[i][i + 1] = max(numbers[i], numbers[i + 1]);

	for (int i = 3; i <= n; i++)
		for (int j = 0; j <= n - i; j++){
			int left = numbers[j];
			if (numbers[j + 1] >= numbers[j + i - 1])
				left += dp[j + 2][j + i - 1];
			else 
				left += dp[j + 1][j + i - 2];
			int right = numbers[j + i - 1];
			if (numbers[j] >= numbers[j + i - 2])
				right += dp[j + 1][j + i - 2];
			else
				right += dp[j][j + i - 3];
			dp[j][j + i - 1] = max(left, right);
		}

	return dp[0][n - 1];
}

int game(const vector<int>& numbers){
	int result = do_dp(numbers);
	int sum = 0;
	for (int i = 0; i < numbers.size(); i++)
		sum += numbers[i];
	return result - (sum - result);
}

int main(){
	int n, count = 0;
	while (scanf("%d", &n) && n){
		vector<int> numbers(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &numbers[i]);
		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++count, game(numbers));
	}
	return 0;
}
