// On POJ, this solution is only accepted by C++.
// G++ will encounter Runtime Error with srand()
// But without srand(), the code gets TLE...
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <iostream>

using namespace std;

struct node_t {
    double elem;
    int priority;
    int value;
    int size;
    node_t *left, *right;
};

node_t pool[200500];
int pool_counter;
node_t *root;

void treap_init(){
    root = NULL;
    pool_counter = 0;
}

void update_size(node_t *node) {
    if (node) {
        node->size = 1;
        node->size += node->left ? node->left->size : 0;
        node->size += node->right ? node->right->size : 0;
    }
}

node_t *rotate_left(node_t *node) {
    node_t *right = node->right, *right_left = right->left;
    right->left = node;
    node->right = right_left;

    update_size(node);
    update_size(right);
    return right;
}

node_t *rotate_right(node_t *node) {
    node_t *left = node->left, *left_right = left->right;
    left->right = node;
    node->left = left_right;

    update_size(node);
    update_size(left);
    return left;
}

void insert(node_t *&node, double elem, int value) {
    if (node == NULL) {
        node = &pool[pool_counter++];
        node->left = node->right = NULL;
        node->elem = elem;
        node->value = value;
        node->priority = rand();
        node->size = 1;
        return;
    }

    if (node->elem > elem) {
        insert(node->left, elem, value);
        update_size(node);
        if (node->priority < node->left->priority)
            node = rotate_right(node);
    } 
    else {
        insert(node->right, elem, value);
        update_size(node);
        if (node->priority < node->right->priority)
            node = rotate_left(node);
    }
};


double get_nth(node_t *node, int rank) {
    if (node == NULL)
        return FLT_MAX;
    int left = node->left ? node->left->size : 0;
    if (left >= rank)
        return get_nth(node->left, rank);
    if (left + 1 == rank)
        return node->elem;
    return get_nth(node->right, rank - left - 1);
}

void print(node_t *node, bool &first) {
    if (node) {
        print(node->left, first);
        if (node->elem > FLT_MIN) {
            if (first)
                first = false;
            else
                printf(" ");
            printf("%d", node->value);
        }
        print(node->right, first);
    }
}

int main() {
    srand(time(0));
    int N;
    while (scanf("%d", &N) == 1) {
        treap_init();
        insert(root, 0, -1);
        for (int i = 0; i < N; i++) {
            int rank, val;
            scanf("%d %d", &rank, &val);

            double first = get_nth(root, rank + 1);
            double second = get_nth(root, rank + 2);

            insert(root, (first + second) / 2, val);
            update_size(root);

        }
        bool first = true;
        print(root, first);
        printf("\n");
    }
    return 0;
}
