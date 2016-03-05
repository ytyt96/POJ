#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	vector<string> DNA(m);
	for (int i = 0; i < m; i++)
		cin >> DNA[i];
	vector<pair<int, int>> label(m);
	for (int i = 0; i < m; i++){
		label[i].second = i;
		for (int j = 0; j < n - 1; j++)
			for (int k = j + 1; k < n; k++)
				if (DNA[i][j] > DNA[i][k])
					label[i].first++;
	}
	sort(label.begin(), label.end());
	for (int i = 0; i < m; i++)
		printf("%s\n", DNA[label[i].second].c_str());
	return 0;
	
}
