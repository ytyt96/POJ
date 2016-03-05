#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	while (N--){
		string s1, s2;
		cin >> s1 >> s2;
		int cap = max(s1.size(), s2.size());
		vector<int> num1(cap), num2(cap);
		for (int i = 0; i < s1.size(); i++)
			num1[cap - 1 - i] = s1[i] - '0';
		for (int i = 0; i < s2.size(); i++)
			num2[cap - 1 - i] = s2[i] - '0';

		vector<int> num3(cap + 5);
		for (int i = 0; i < cap; i++){
			num3[i] += (num1[cap - 1 - i] + num2[cap - 1 - i]);
			num3[i + 1] += num3[i] / 10;
			num3[i] %= 10;
		}
		int start = 0, end = cap + 4;
		while (num3[start] == 0)
			start++;
		while (num3[end] == 0)
			end--;
		for (int i = start; i <= end; i++)
			printf("%d", num3[i]);
		printf("\n");
	}
	return 0;
}
