#include <iostream>
#include "BinarySearchTree.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, char* argv[])
{
    BinarySearchTree<int> tree;

    tree.add(10, 5, 3, 15);
    tree.print_post_order(tree.root);
    cout << endl;
    tree.print_in_order(tree.root);
    cout << endl;
    tree.print_pre_order(tree.root);
    
    
    return 0;
}
