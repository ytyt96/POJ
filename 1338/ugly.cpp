#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		vector<int> ugly(n);
		ugly[0] = 1;
		int two = 0, three = 0, five = 0;
		int counter = 1;
		while (counter < n) {
			int num = min(ugly[two] * 2, min(ugly[three] * 3, ugly[five] * 5));
			ugly[counter++] = num;
			if (num == ugly[two] * 2) 
				two++;
			if (num == ugly[three] * 3)
				three++;
			if (num == ugly[five] * 5)
				five++;
		}
		printf("%d\n", ugly[n - 1]);
	}
}
