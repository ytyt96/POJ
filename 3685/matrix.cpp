#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

long long calc(long long i, long long j) {
    return i * i + 100000 * i + j * j - 100000 * j + i * j;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long lower = LLONG_MIN / 2, upper = LLONG_MAX / 2;
        long long N, K;
        scanf("%lld %lld", &N, &K);

        while (lower <= upper) {
            long long mid = (lower + upper) >> 1;
            long long rank = 0;
            for (int i = 0; i < N; i++) {
                int lo = 0, hi = N - 1;
                while (lo <= hi) {
                    int mi = (lo + hi) >> 1;
                    if (calc(mi + 1, i + 1) > mid)
                        hi = mi - 1;
                    else
                        lo = mi + 1;
                }
                rank += hi + 1;
            }
            if (rank >= K)
                upper = mid - 1;
            else
                lower = mid + 1;
        }

        printf("%lld\n", upper + 1);
    }
}
