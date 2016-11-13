#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        int N;
        scanf("%d", &N);
        int A[N];
        bool greaterThanOne = false;
        for (int i = 0; i < N; i++){
            scanf("%d", &A[i]);
            if (A[i] > 1)
                greaterThanOne = true;
        }
        int sum = A[0];
        for (int i = 1; i < N; i++)
            sum ^= A[i];
        if ((sum == 0 && !greaterThanOne) || (sum != 0 && greaterThanOne))
            printf("John\n");
        else
            printf("Brother\n");

    }
}
