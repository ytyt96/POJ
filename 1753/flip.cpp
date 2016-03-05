#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>

#define setBit(S, j) (S |= (1 << j))
#define toggleBit(S, j) (S ^= (1 << j))

using namespace std;

struct state_t{
	state_t(unsigned int n_state, int n_step):state(n_state), step(n_step){}
	unsigned int state;
	int step;
};

int flip(unsigned orig, int pos){
	toggleBit(orig, pos);
	if (pos % 4 != 0)
		toggleBit(orig, pos - 1);
	if ((pos + 1) % 4 != 0)
		toggleBit(orig, pos + 1);
	if (pos - 4 >= 0)
		toggleBit(orig, pos - 4);
	if (pos + 4 < 16)
		toggleBit(orig, pos + 4);
	return orig;
}

int main(){
	unsigned int input = 0;
	for (int i = 0; i < 16; i++){
		char ch;
		scanf(" %c ", &ch);
		if (ch == 'b')
			setBit(input, i);
	}
	queue<state_t> states;
	states.push(state_t(input, 0));
	bool visited[66000];
	memset(visited, false, sizeof(visited));
	visited[input] = true;
	
	bool possible = false;
	while (!states.empty()){
		state_t curr = states.front();
		states.pop();
		if (curr.state == 0 || curr.state == (1 << 16) - 1){
			printf("%d\n", curr.step);
			possible = true;
			break;
		}

		for (int i = 0; i < 16; i++){
			unsigned int flipped = flip(curr.state, i);
			if (!visited[flipped]){
				visited[flipped] = true;
				states.push(state_t(flipped, curr.step + 1));
			}
		}
	}
	if (!possible)
		printf("Impossible\n");
	return 0;
}
