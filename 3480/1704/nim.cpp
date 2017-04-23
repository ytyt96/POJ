#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        vector<int> positions(N); 
        for (int i = 0; i < N; i++)
            scanf("%d", &positions[i]);
        sort(positions.begin(), positions.end());
        int sum = 0;
        if (N % 2 == 1) {
            sum = positions[0] - 1;
            for (int i = 1; i < positions.size(); i += 2)
                sum ^= positions[i + 1] - positions[i] - 1;
        }
        else {
            for (int i = 0; i < positions.size(); i += 2)
                sum ^= positions[i + 1] - positions[i] - 1;
        }
        if (sum == 0)
            printf("Bob will win\n");
        else
            printf("Georgia will win\n");
    }
}
