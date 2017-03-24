#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int main() {
    char buffer[1000500];
    scanf("%s", buffer);
    int buffer_size = strlen(buffer);

    int block_size = sqrt(buffer_size);
    int block_number = ceil(1.0 * buffer_size / block_size);

    vector<string> blocks(block_number);
    for (int i = 0; i < block_number - 1; i++)
        blocks[i] = string(buffer + i * block_size, block_size);
    blocks.back() = string(buffer + (block_number - 1) * block_size);

    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char op;
        scanf(" %c ", &op);
        if (op == 'I') {
            int p;
            char ch;
            scanf(" %c %d", &ch, &p);

            int block = 0, size = 0;
            while (block < block_number && blocks[block].size() + size < p)
                size += blocks[block++].size();
            if (block >= block_number)
                blocks.back().push_back(ch);
            else
                blocks[block].insert(blocks[block].begin() + (p - size - 1),ch);
        }
        else {
            int p;
            scanf("%d", &p);
            int block = 0, size = 0;
            while (block < block_number && blocks[block].size() + size < p)
                size += blocks[block++].size();
            printf("%c\n", blocks[block][p - size - 1]);
        }
    }
}

