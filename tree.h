#ifndef TREE_H
#define TREE_H

struct Tree {
    int inf;
    Tree *left, *right;
    Tree *parent;
    char color;
    Tree (int value): inf(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

void insert(Tree *&, int);
void print_tree(Tree *&);

#endif
