#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
	int count[26];
	memset(count, 0, sizeof(count));
	char ch;
	int line = 0;
	while (scanf(" %c ", &ch) == 1)
		if (ch >= 'A' && ch <= 'Z'){
			count[ch - 'A']++;
			if (count[ch - 'A'] > line)
				line = count[ch - 'A'];
		}
	while (line){
		int blanks = 0;
		for (int i = 0; i < 26; i++){
			if (count[i] >= line){
				for (int j = 0; j < blanks; j++)
					printf(" ");
				printf("*");
				blanks = 1;
			}
			else
				blanks += 2;
		}
		printf("\n");
		line--;
	}
	for (ch = 'A'; ch <= 'Z'; ch++){
		printf("%c", ch);
		if (ch != 'Z')
			printf(" ");
	}
	printf("\n");
	return 0;
}
