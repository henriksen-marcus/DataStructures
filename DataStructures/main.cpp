#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main(int argc, char* argv[])
{
    BinarySearchTree<int> tree;

    tree.add(100, 50, 150);

    tree.root->print();
    tree.remove(50, tree.root);
    tree.root->print();
    
    return 0;
}
