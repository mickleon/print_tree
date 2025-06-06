# What is this?
There is C++ class for binary tree, that have method for **console output** for tree **without any specific libraries**. The program correctly outputs numbers **with any number of digits**.

# What is it for?
This is a training example of a binary search tree. This may be necessary for those who study C++ and dynamic structures such as trees.

# What can it do?
In addition to actually **displaying** the tree, you can **insert** and **delete** elements from it by methods 
`Tree::print()`, `Tree::insert(int value)` and `Tree::erase(Node *&x)`.

# Run
```bash
g++ main.cpp tree.cpp -o main
./main
```