#include <iostream>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, char* argv[])
{
    BinarySearchTree<int> tree;

    tree.add(100, 50, 150);

    /*tree.root->print();
    tree.remove(50, tree.root);
    tree.root->print();*/

    HashTable<int> table;
    table.add(200);
    table.add(48239);
    table.add(29);
    table.add(199);
    table.add(198);

    table.print();

    cout << (table.find(29) ? "found" : "not found");
    
    return 0;
}
