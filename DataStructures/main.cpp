#include <iostream>
#include "BinarySearchTree.h"
#include "LNode.h"

using namespace std;

int main(int argc, char* argv[])
{
    auto* node = new LNode<string>("heyo");

    node->print();
    
    return 0;
}
