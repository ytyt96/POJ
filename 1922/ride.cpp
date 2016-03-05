#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <climits>
#include <cfloat>
#include <cmath>

using namespace std;

int main(){
	int N;
	while (scanf("%d", &N) && N){
		vector<pair<long long, double> > riders;
		riders.reserve(N);
		for (int i = 0; i < N; i++){
			int speed;
			long long time;
			scanf("%d %I64d", &speed, &time);
			if (time >= 0)
				riders.push_back(make_pair(time, speed / 3600.0));
		}

		vector<double> times(riders.size(), 0);
		for (int i = 0; i < riders.size(); i++)
			times[i] = 4.5 / riders[i].second + riders[i].first; 
		double min_time = DBL_MAX;
		for (int i = 0; i < riders.size(); i++)
			if (min_time > times[i])
				min_time = times[i];
		printf("%I64d\n", static_cast<long long>(ceil(min_time)));
	}
	return 0;
}
