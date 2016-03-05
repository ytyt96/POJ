#include <iostream>
#include <cstdio>

using namespace std;

int main(){
	double length;
	while (scanf("%lf", &length) == 1 && length >= 0.01){
		double sum = 0.0;
		int count = 0;
		while (sum < length)
			sum += 1.0 / (count++ + 2);
		printf("%d card(s)\n", count);
	}
	return 0;
}
