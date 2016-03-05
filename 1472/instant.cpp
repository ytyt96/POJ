#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

vector<int> runLoop(int);

int toNumber(string word){
	int ret = 0;
	for (int i = 0; i < word.size(); i++){
		int digit = word[i] - '0';
		ret = ret * 10 + digit;
	}
	return ret;
}

void vecAdd(vector<int>& lhs, const vector<int>& rhs){
	for (int i = 0; i < lhs.size(); i++)
		lhs[i] += rhs[i];
}

vector<int> runStatement(){
	vector<int> ret(15, 0);
	string word;
	
	while (cin >> word){
		if (word == "LOOP"){
			cin >> word;
			if (word == "n")
				vecAdd(ret, runLoop(-1));
			else
				vecAdd(ret, runLoop(toNumber(word)));
		}
		else if (word == "OP"){
			int num;
			cin >> num;
			ret[0] += num;
		}
		else if (word == "END")
			return ret;	
	}
}

vector<int> runLoop(int n){
	vector<int> ret = runStatement();
	if (n == -1){
		for (int i = 14; i > 0; i--)
			ret[i] = ret[i - 1];
		ret[0] = 0;
	}
	else
		for (int i = 0; i < 15; i++)
			ret[i] *= n;
	return ret;
}

int main(){
	int k;
	scanf("%d", &k);
	vector<int> answer(15, 0);
	for (int tc = 1; tc <= k; tc++){
		printf("Program #%d\n", tc);
		string word;
		cin >> word;
		answer = runStatement();	
		printf("Runtime = ");
		bool zero = true;
		for (int i = 14; i >= 0; i--){
			if (answer[i] != 0){
				if (zero)
					zero = false;
				else
					printf("+");
				
				if (i != 0){
					if (answer[i] != 1)
						printf("%d*", answer[i]);
					if (i != 1)
						printf("n^%d", i);
					else
						printf("n");
				}
				else
					printf("%d", answer[i]);
			}
		}
		if (zero)
			printf("0");
		cout << "\n\n";
	}
	return 0;
}
