#include <iostream>
#include "tree.h"

int main() {
    Tree *tr = nullptr;
    int n;
    std::cin >> n;
    int x, max = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> x;
        if (x > max) max = x;
        insert(tr, x);
    }
    print_tree(tr);
}

/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
