#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

int getCol(int index){
	return index % 9;
}

int getRow(int index){
	return index / 9;
}

int getGrid(int index){
	return getRow(index) / 3 * 3 + getCol(index) / 3;
}

typedef vector<vector<bool> > vbb;

bool solve(vector<int>& board, vbb& row, vbb& col, vbb& grid, int index, vector<pair<vector<int>, int> >& numbers){
	if (index >= 81){
		for (int i = 0; i < 81; i++)
			printf("%d", board[i]);
		printf("\n");
		return true;
	}

	int pos = numbers[index].second;

	if (board[pos] != 0)
		return solve(board, row, col, grid, index + 1, numbers);


	for (int j = 0; j < numbers[index].first.size(); j++){
		int i = numbers[index].first[j];
		if (!row[getRow(pos)][i] && !col[getCol(pos)][i] && !grid[getGrid(pos)][i]){
			board[pos] = i;
			row[getRow(pos)][i] = true;
			col[getCol(pos)][i] = true;
			grid[getGrid(pos)][i] = true;
			if (solve(board, row, col, grid, index + 1, numbers))
				return true;
			board[pos] = 0;
			row[getRow(pos)][i] = false;
			col[getCol(pos)][i] = false;
			grid[getGrid(pos)][i] = false;
		}
	}
	return false;
}

bool cmp(const pair<vector<int>, int>& lhs, const pair<vector<int>, int>& rhs){
	return lhs.first.size() < rhs.first.size();
}

int main(){
	string line;
	while (getline(cin, line) && line != "end"){
		vector<int> board(81, 0);
		vbb grid(10, vector<bool>(10, false));
		vbb row(grid), col(grid);
		
		vector<pair<vector<int>, int> > numbers(81);

		for (int i = 0; i < 81; i++)
			if (line[i] >= '0' && line[i] <= '9'){
				board[i] = line[i] - '0';
				row[getRow(i)][board[i]] = true;
				col[getCol(i)][board[i]] = true;
				grid[getGrid(i)][board[i]] = true;
			}
		for (int i = 0; i < 81; i++){
			numbers[i].second = i;
			for (int j = 1; j <= 9; j++)
				if (!row[getRow(i)][j] && !col[getCol(i)][j] && !grid[getGrid(i)][j])
					numbers[i].first.push_back(j);
		}

		sort(numbers.begin(), numbers.end(), cmp);

		for (int i = 0; i < numbers.size(); i++){
			cout << numbers[i].second << ":\n";
			for (int j = 0; j < numbers[i].first.size(); j++)
				cout << numbers[i].first[j] << " ";
			cout << "\n";
		}
		solve(board, row, col, grid, 0, numbers);
	}
}
