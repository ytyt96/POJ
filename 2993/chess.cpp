#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void readData(vector<vector<char> >& board, string line, bool white){
	line = line.substr(7);
	char t, c, r;
	int index = 0;
	while (index < line.size()){
		if (index + 2 < line.size() && line[index + 2] != ','){
			t = line[index];
			c = line[index + 1];
			r = line[index + 2];
			index += 4;
		}else{
			t = 'P';
			c = line[index];
			r = line[index + 1];
			index += 3;
		}
		int col = c - 'a', row = r - '0' - 1;	
		if (!white)
			t = t + ('a' - 'A');
		board[col][row] = t;
	}
}

void printH(){
	printf("+");
	for (int i = 0; i < 8; i++)
		printf("---+");
	printf("\n");
}

int main(){
	string line;
	vector<vector<char> > board(8, vector<char>(8, ' '));
	
	getline(cin, line);
	readData(board, line, true);
	getline(cin, line);
	readData(board, line, false);
	
	for (int row = 7; row >= 0; row--){
		if (row == 7)
			printH();
		for (int col = 0; col < 8; col++){
			if (col == 0)
				printf("|");
			char fill = ((col + row) % 2 == 1 ? '.' : ':');
			if (board[col][row] == ' ')
				board[col][row] = fill;
			printf("%c%c%c|", fill, board[col][row], fill);
		}
		printf("\n");
		printH();
	}
	return 0;	
}
