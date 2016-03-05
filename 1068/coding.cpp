#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		int n;
		scanf("%d", &n);
		vector<int> P(n + 1), left(n);
		P[0] = 0;
		for (int i = 0; i < n; i++){
			scanf("%d", &P[i + 1]);
			left[i] = P[i + 1] - P[i];
			int w = 1, c = i;
			while (left[c] == 0){
				w++;
				c--;
			}	
			left[c]--;
			if (i != 0)
				printf(" ");
			printf("%d", w);
		}
		printf("\n");
	}
	return 0;
}
