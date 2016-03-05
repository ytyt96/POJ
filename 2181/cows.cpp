#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
	int P;
	scanf("%d", &P);
	vector<int> potions(P);
	for (int i = 0; i < P; i++)
		scanf("%d", &potions[i]);
	int cap = 0;
	bool odd = true;
	for (int i = 0; i < P; i++){
		if (odd && (i == P - 1 || potions[i] > potions[i + 1])){
			cap += potions[i];
			odd = !odd;
		}
		if (!odd && i != P - 1 && potions[i] < potions[i + 1]){
			cap -= potions[i];
			odd = !odd;
		}
	}
	printf("%d\n", cap);
	return 0;
}
