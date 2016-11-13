#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class trie{
public:
    trie(){
        root = new trieNode();
        total = 0;
    }

    void insert(const char* str){
        insert(root, str);        
    }
    
    void print(){
        char treeName[35];
        treeName[0] = 0;
        int length = 0;
        print(root, treeName, length);
    }
    
private:
    struct trieNode{
        trieNode(){
            memset(children, 0, sizeof(children));
            count = 0;
        }

        trieNode* children[256];
        size_t  count;
    };

    trieNode* root;
    size_t total;

    void insert(trieNode*& node, const char* str){
        if (!node)
            node = new trieNode();
        if (*str){
            insert(node->children[(int)*str], str + 1);
        }
        else{
            node->count++;
            total++;
        }
    }

    void print(trieNode* node, char* treeName, int length){
        if (node->count)
            printf("%s %.4f\n", treeName, 100.0 * node->count / total);
        else{
            for (size_t i = 0; i < 256; i++)
                if (node->children[i]){
                    treeName[length++] = (char)i;
                    treeName[length] = 0;
                    print(node->children[i], treeName, length);
                    treeName[length--] = 0;
                }
        }
    }
};

int main(){
    char buffer[40];
    trie Trie;
    while (scanf(" %[^\n]", buffer) == 1)
        Trie.insert(buffer);
    Trie.print();
    return 0;
}
