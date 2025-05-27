#ifndef TREE_H
#define TREE_H
#include <vector>

struct Node {
    int inf;
    Node *left, *right;
    Node *parent;
    char color;
    Node (int value):
    inf(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree(): root(nullptr), height(0) {};
    ~Tree() {clear(root);}
    Node* max();
    Node* max(Node *&x);
    Node* min();
    Node* min(Node *&x);
    Node* find(int value);
    Node* find(Node *&x, int value);
    void insert(int value);
    void erase(Node *&x);
    void print();
private:
    std::vector<std::vector<std::pair<Node*, int>>> array;
    int height;
    void make_array(Node *&x, int depth, int count);
    void update_height();
    int calculate_height(Node* node);
    void clear(Node* x);
};

#endif
