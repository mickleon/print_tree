#include <iostream>
#include <vector>
#include <cmath>
#include "tree.h"

void print_space(int n){
    if (n < 1) return;
    std::string s(n, ' ');
    std::cout << s;
}

Node* Tree::max() {
    if (!Tree::root) return nullptr;
    Node* y = Tree::root;
    while (y->right) {
        y = y->right;
    }
    return y;
}
Node* Tree::max(Node *&x) {
    if (!x) return nullptr;
    Node* y = x;
    while (y->right) {
        y = y->right;
    }
    return y;
}

Node* Tree::min() {
    if (!Tree::root) return nullptr;
    Node* y = Tree::root;
    while (y->left) {
        y = y->left;
    }
    return y;
}
Node* Tree::min(Node *&x) {
    if (!x) return nullptr;
    Node* y = x;
    while (y->left) {
        y = y->left;
    }
    return y;
}

void Tree::insert(int value) {
    Node* n = new Node(value);
    if (!Tree::root) {
        Tree::root = n;
        Tree::height = 1;
        return;
    }
    Node* y = Tree::root;
    int node_height = 1;
    while (y) {
        if (n->inf > y->inf) {
            if (y->right) {
                y = y->right;
                node_height++;
            }
            else {
                y->right = n;
                n->parent = y;
                node_height++;
                break;
            }
        }
        else if (n->inf < y->inf) {
            if (y->left) {
                y = y->left;
                node_height++;
            }
            else {
                y->left = n;
                n->parent = y;
                node_height++;
                break;
            }
        }
        else {
            delete n;
            return;
        }
    }
    if (node_height > Tree::height) {
        Tree::height = node_height;
    }
}

Node* Tree::find(int value) {
    if (!Tree::root || Tree::root->inf == value)
        return Tree::root;
    if (value < Tree::root->inf)
        return Tree::find(Tree::root->left, value);
    return Tree::find(Tree::root->right, value);
}
Node* Tree::find(Node *&x, int value) {
    if (!x || x->inf == value)
        return x;
    if (value < x->inf)
        return Tree::find(x->left, value);
    return Tree::find(x->right, value);
}

void Tree::update_height() {
    Tree::height = Tree::calculate_height(Tree::root);
}

int Tree::calculate_height(Node* x) {
    if (!x) return 0;
    return 1 + std::max(Tree::calculate_height(x->left), 
    Tree::calculate_height(x->right));
}

void Tree::erase(Node *&x) {
    Node *p = x->parent;
    if (!x->left && !x->right) { // No children
        if (!p) { // Only one node in tree
            Tree::root = nullptr;
            Tree::height = 0;
        }
        else {
            if (p->left == x) p->left = nullptr;
            else if (p->right == x) p->right = nullptr;
            Tree::update_height();
        }
        delete x;
    }
    else if (!x->left || !x->right) { // 1 child
        Node *child = x->left ? x->left : x->right;
        if (!p) { // Root
            Tree::root = child;
            Tree::update_height();
        }
        else {
            if (p->left == x) p->left = child;
            else if (p->right == x) p->right = child;
            Tree::update_height();
        }
        child->parent = p;
        delete x;
    }
    else { // 2 childer
        Node *succ = Tree::min(x->right);
        x->inf = succ->inf;
        if (succ->parent->left == succ) 
            succ->parent->left = succ->right;
        else
            succ->parent->right = succ->right;
        if (succ->right)
            succ->right->parent = succ->parent;
        delete succ;
        Tree::update_height();
    }
}

// Traversal with depth calculation and node offset from the left edge of the level
void Tree::make_array(Node *&x, int depth = 0, int count = 1) {
    Tree::array[depth].push_back({x, count - (1<<depth)});
    if (x->left) 
        Tree::make_array(x->left, depth + 1, count*2);
    if (x->right) 
        Tree::make_array(x->right, depth + 1, count*2+1);
}

void Tree::print(){
    int r = log10(Tree::max()->inf) + 1;
    Tree::array.assign(Tree::height, {});
    Tree::make_array(Tree::root);
    // Space at the beginning of each level
    int init_space = (r + 1)*(1<<(Tree::height - 2));
    for (int depth = 0; depth <= Tree::height - 1; depth++) {
        print_space(init_space - r);
        int prev_offset = 0;
        // Space between nodes at this level
        int space = init_space*2 - r;
        if (space == 0) space = 1;
        for (auto &node : Tree::array[depth]) {
            // Calculate indentation if the tree is incomplete
            print_space((space + r)*(node.second - prev_offset));
            if (node.first->color == 'r')
                printf("\033[31m%*d\033[m", r, node.first->inf);
            else
                printf("%*d", r, node.first->inf);
            // Space after the node
            print_space(space);
            // Save offset for subsequent calculations
            prev_offset = node.second + 1;
        }
        std::cout << '\n';
        init_space /= 2;
    }
}

void Tree::clear(Node* x) {
    if (x) {
        Tree::clear(x->left);
        Tree::clear(x->right);
        delete x;
    }
}