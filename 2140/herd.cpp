#include <iostream>
#include <cstdio>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int sum = 0, count = 0, head = 1;
	for (int i = 1; i <= N; i++){
		sum += i;
		while (sum > N){
			sum -= head;
			head++;
		}
		if (sum == N)
			count++;
	}
	printf("%d\n", count);
	return 0;
}
