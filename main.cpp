#include <iostream>
#include "tree.h"

int main() {
    using std::cout; using std::cin;
    Tree tr;
    cout << "Number of nodes: ";
    int n, x;
    cin >> n;
    cout << "Nodes: ";
    for (int i = 0; i < n; i++) {
        cin >> x;
        tr.insert(x);
    }
    tr.print();
}

/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
