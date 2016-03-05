#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct state_t{
	state_t():counts(2000, 0), sum(0){}
	vector<int> nums;
	vector<int> counts;
	int sum;
};

void output(const vector<int>& vec){
	printf("%d", vec[0]);
	for (int i = 1; i < vec.size(); i++)
		printf("+%d", vec[i]);
	printf("\n");
}
int main(){
	int t, n;
	while (scanf("%d %d", &t, &n) && n != 0){
		printf("Sums of %d:\n", t);
		queue<state_t> states;
		vector<int> nums;

		state_t initial_s;
		for (int i = 0; i < n; i++){
			int x;
			scanf("%d", &x);
			initial_s.counts[x]++;
			if (i == 0 || x != nums.back())
				nums.push_back(x);
		}

		bool printed = false;
		states.push(initial_s);

		vector<vector<int> > answer;
		while (!states.empty()){
			state_t curr_s = states.front();
			states.pop();
			if (curr_s.sum == t){
				printed = true;
				answer.push_back(curr_s.nums);
			}
			else{
				for (int i = 0; i < nums.size(); i++)
					if (curr_s.nums.empty() || curr_s.nums.back() >= nums[i])
						if (curr_s.sum + nums[i] <= t && curr_s.counts[nums[i]] > 0){
							state_t n_s = curr_s;
							n_s.nums.push_back(nums[i]);
							n_s.sum += nums[i];
							n_s.counts[nums[i]]--;
							states.push(n_s);
						}
			}
		}
		sort(answer.rbegin(), answer.rend());
		for (int i = 0; i < answer.size(); i++)
			output(answer[i]);
		if (!printed)
			printf("NONE\n");

	}
}
