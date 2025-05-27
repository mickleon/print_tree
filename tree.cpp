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

// Traversal with depth calculation and node offset from the left edge of the level
void Tree::make_array(Node *&x, int depth = 0, int count = 1) {
    Tree::array[depth].push_back({x, count - (1<<depth)});
    if (x->left) 
        Tree::make_array(x->left, depth + 1, count*2);
    if (x->right) 
        Tree::make_array(x->right, depth + 1, count*2+1);
}

// Print the tree
void Tree::print(){
    int r = log10(Tree::max()->inf) + 1;
    Tree::array.assign(Tree::height, {});
    Tree::make_array(Tree::root);
    // Space at the beginning of each level
    int init_space = (r + 1)*(1<<(Tree::height - 2));
    // Iterate through levels
    for (int depth = 0; depth <= Tree::height - 1; depth++) {
        print_space(init_space - r);
        int prev_offset = 0;
        // Space between nodes at this level
        int space = init_space*2 - r;
        if (space == 0) space = 1;
        // Iterate through nodes at the level
        for (auto &node : Tree::array[depth]) {
            // Calculate indentation to the node if the tree is incomplete
            print_space((space + r)*(node.second - prev_offset));
            // Print the node
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