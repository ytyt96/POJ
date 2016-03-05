#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

bool isPrime(int a){
	double limit = sqrt(double(a));
	for (int i = 2; i <= limit; i++)
		if (a % i == 0)
			return false;
	return true;
}

void generatePrime(vector<int>& primes){
	primes.push_back(1); // 1 is not a prime number... this statement is in place only for special case handling!
	primes.push_back(2);

	for (int i = 1; i < 10000; i++)
		if (isPrime(i * 2 + 1))
			primes.push_back(i * 2 + 1);
}

int main(){
	vector<int> primes;
	primes.reserve(3000);
	generatePrime(primes);
	int N;
	scanf("%d", &N);
	int largest = 0, num = 0;
	while (N--){
		int x;
		scanf("%d", &x);
		for (int i = primes.size() - 1; i >= 0; i--)
			if (primes[i] <= largest)
				break;
			else
				if (x % primes[i] == 0){
					largest = primes[i];
					num = x;
				}
	}
	printf("%d\n", num);
	return 0;
}
