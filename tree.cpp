#include <iostream>
#include <vector>
#include <cmath>

struct Tree {
    int inf;
    Tree *left, *right;
    Tree *parent;
    char color;
    Tree (int value): inf(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

int max = 0;
std::vector<std::vector<std::pair<Tree*, int>>> d;

// Insert an element
void insert(Tree *&tr, int value) {
    Tree *n = new Tree(value);
    if (value > max) max = value;
    if (!tr) tr = n;
    else {
        Tree *y = tr;
        while (y) {
            if (n->inf > y->inf) {
                if (y->right) y = y->right;
                else {
                    y->right = n;
                    n->parent = y;
                    break;
                }
            }
            else if (n->inf < y->inf) {
                if (y->left) y = y->left;
                else {
                    y->left = n;
                    n->parent = y;
                    break;
                }
            }
            else break;
        }
    }
}

// Traversal with tree height calculation
void max_height(Tree *&x, int &max, int depth = 0) {
    if (depth > max)
        max = depth;
    if (x->left)
        max_height(x->left, max, depth + 1);
    if (x->right)
        max_height(x->right, max, depth + 1);
}

// Traversal with depth calculation and node offset from the left edge of the level
void deepness(Tree *&x, int depth = 0, int count = 1) {
    d[depth].push_back({x, count - (1<<depth)});
    if (x->left) 
        deepness(x->left, depth + 1, count*2);
    if (x->right) 
        deepness(x->right, depth + 1, count*2+1);
}

// Print space n times
void print_space(int n){
    if (n < 1) return;
    std::string s(n, ' ');
    std::cout << s;
}

// Print the tree
void print_tree(Tree *&tr){
    int r = log10(max) + 1;
    int height = 0;
    max_height(tr, height);
    d.resize(height + 1);
    deepness(tr);
    // Space at the beginning of each level
    int init_space = (r + 1)*(1<<(height - 1));
    // Iterate through levels
    for (int depth = 0; depth <= height; depth++) {
        print_space(init_space - r);
        int prev_offset = 0;
        // Space between nodes at this level
        int space = init_space*2 - r;
        if (space == 0) space = 1;
        // Iterate through nodes at the level
        for (auto &node : d[depth]) {
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
