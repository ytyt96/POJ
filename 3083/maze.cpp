#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);

	while (N--){
		int w, h;
		scanf("%d %d", &w, &h);
		vector<vector<char> > maze(w, vector<char>(h));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				scanf(" %c", &maze[j][i]);

		
	}
	return 0;
}
