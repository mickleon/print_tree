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
    int c;
    while (true) {
        cout << "1. Insert\n2. Erase\n3. Quit\n> ";
        cin >> c;
        switch (c) {
        case 1: {
            cout << "Node to insert: ";
            cin >> x;
            tr.insert(x);
            tr.print();
            break;
        }
        case 2: {
            cout << "Node to erase: ";
            cin >> x;
            Node *y = tr.find(x);
            if (y) tr.erase(y);
            tr.print();
            break;
        }
        case 3: return 0;
        default: break;
        }
    }
}

/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
