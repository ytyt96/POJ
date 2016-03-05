#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(int x){
	for (int i = 2; i <= sqrt(x); i++)
		if (x % i == 0)
			return false;
	return true;
}
int hash(int x, int y){
	long long product = (x % 39989) * (y % 39989);
	return product % 39989; 
}

struct land_t{
	int x, y, value;
};

int findHash(vector<vector<int> >& hashTable, vector<land_t>& lands, int x, int y){
	int hashValue = hash(x, y);
	for (int i = 0; i < hashTable[hashValue].size(); i++){
		int index = hashTable[hashValue][i];
		if (lands[index].x == x && lands[index].y == y)
			return index;
	}
	return -1;
}

long long DPS(vector<vector<int> >& hashTable, vector<land_t>& lands, vector<bool>& visited, int curr){
	if (visited[curr])
		return 0;
	
	long long curr_answer = lands[curr].value;
	visited[curr] = true;

	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	for (int i = 0; i < 4; i++){
		int index = findHash(hashTable, lands, lands[curr].x + dir[i][0], lands[curr].y + dir[i][1]);
		if (index != -1)
			curr_answer += DPS(hashTable, lands, visited, index);
	}
	return curr_answer;
}

int main(){
	int N;

	while (scanf("%d", &N) == 1 && N != 0){
		vector<vector<int> > hashTable(40000);
		vector<land_t> lands(N);
		vector<bool> visited(N, false);
		long long answer = 0;

		for (int i = 0; i < N; i++){
			scanf("%d %d %d", &lands[i].x, &lands[i].y, &lands[i].value);
			lands[i].x += 70000;
			lands[i].y += 70000;
			hashTable[hash(lands[i].x, lands[i].y)].push_back(i);
		}

		for (int i = 0; i < N; i++)
			answer = max(answer, DPS(hashTable, lands, visited, i));
		
		printf("%lld\n", answer);
	}
	return 0;	
}
