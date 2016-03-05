#include <cstdio>

using namespace std;

int main(){
	double sum = 0.0;
	for (int i = 0; i < 12; i++){
		double money;
		scanf("%lf", &money);
		sum += money;
	}
	printf("$%.2f\n", sum / 12.0);
	return 0;
}
