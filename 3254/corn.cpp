#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

#define MOD 100000000

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    int field[M][N];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &field[i][j]);
   
    long long table[(1 << N)][M];
    memset(table, 0, sizeof table);

    vector<unsigned> states;
    states.reserve(1 << N);

    for (unsigned state = 0; state < (1 << N); state++) {
        bool valid = true; 
        for (int i = 0; i < N - 1; i++)
            if ((state & (1 << i)) && (state & (1 << (i + 1)))) {
                valid = false;
                break;
            }
        if (valid)
            states.push_back(state);
    }


    for (int i = 0; i < states.size(); i++) {
        unsigned state = states[i];
        bool valid = true;
        for (int j = 0; j < N; j++)
            if ((state & (1 << j)) && (field[0][j] == 0)) {
                valid = false;
                break;
            }
        if (valid)
            table[state][0] = 1;
    }


    for (int row = 0; row < M - 1; row++) {
        for (int i = 0; i < states.size(); i++)
            for (int j = 0; j < states.size(); j++) {
                unsigned state = states[i], new_state = states[j];
                bool valid = true;
                for (int k = 0; k < N; k++)
                    if ((new_state & (1 << k)) && field[row + 1][k] == 0) {
                        valid = false;
                        break;
                    }

                if (!valid)
                    continue;

                if (state & new_state)
                    continue;

                table[new_state][row + 1] = (table[new_state][row + 1] + 
                                             table[state][row]) % MOD;
            }
    }

    long long answer = 0;
    for (unsigned state = 0; state < (1 << N); state++)
        answer = (answer + table[state][M - 1]) % MOD;

    printf("%lld\n", answer);
    return 0;
}
