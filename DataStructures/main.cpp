#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main(int argc, char* argv[])
{
    BinarySearchTree<float> tree;
    tree.add(5, 3, 4, 7, 6, 8, 2);
    tree.print_sorted(tree.root);
    return 0;
}
