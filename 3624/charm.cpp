#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	vector<int> W(N), D(N);
	vector<int> dp(M + 1);
	dp[0] = 0;
	for (int i = 0; i < N; i++)
		scanf("%d %d", &W[i], &D[i]);
	
	for (int i = 0; i < N; i++)
		for (int j = M; j >= W[i]; j--)
			dp[j] = max(dp[j - W[i]] + D[i], dp[j]);
	int answer = 0; 
	for (int i = 0; i <= M; i++)
		answer = max(answer, dp[i]);
	printf("%d\n", answer);
	return 0;
}
