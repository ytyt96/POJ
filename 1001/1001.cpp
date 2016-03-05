#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int main(){
	string line;
	while (getline(cin, line)){
		vector<int> product(210, 0), answer(210, 0);
		int afterDecimal = 0, exp = 0, index = 0;
		bool atPoint = false;
		for (int i = 5; i >= 0; i--)
			if (line[i] == '.')
				atPoint = true;
			else if (line[i] >= '0' && line[i] <= '9'){
				product[index++] = static_cast<int>(line[i] - '0');
				if (!atPoint)
					afterDecimal++;
			}
		if (!atPoint)
			afterDecimal = 0;
		for (int i = 7; i < 9; i++)
			if (line[i] >= '0' && line[i] <= '9')
				exp = exp * 10 + static_cast<int>(line[i] - '0');
		afterDecimal *= exp;

		bool zero = true;
		for (int i = 0; i < 10; i++)
			if (product[i] != 0)
				zero = false;
		if (exp == 0){
			printf("1\n");
			continue;
		}
		if (zero){
			printf("0\n");
			continue;
		}
		answer[0] = 1;
		while (exp--){
			vector<int> temp(210, 0);
			for (int i = 0; i < 200; i++)
				for (int j = 0; j < 200; j++)
					temp[i + j] += answer[i] * product[j];


			for (int i = 0; i < 200; i++){
				temp[i + 1] += temp[i] / 10;
				temp[i] %= 10;
			}
			
			answer = temp;
		}
		
		bool point = false;
		index = 200;
		while (index >= 0 && answer[index] == 0)
			index--;
		int head = 0;
		while (head < 200 && answer[head] == 0 && afterDecimal > 0)
			head++, afterDecimal--;
		if (afterDecimal > index - head + 1)
			printf("."), point = true;
		while (afterDecimal > index - head + 1){
			printf("0");
			afterDecimal--;
		}
		while (head <= index){
			if (!point && (index - head + 1 == afterDecimal))
				printf(".");
			printf("%d", answer[index--]);
		}
		printf("\n");
	}
	return 0;
}
