#pragma once

#include <iostream>

using namespace std;

/**
 * \brief Node for use in binary tree.
 */
template<class T>
struct BNode
{
    BNode(T data) : data(data)
    {
        left = right = nullptr;
    }
    
    BNode *left, *right;
    T data;

    /**
     * \brief Swap the value of this node and the
     * given node and delete that node.
     * \param node The node to copy the value from.
     */
    void swap(BNode<T>* node)
    {
        if (!node)
        { // We have 0 children, just delete this node
            std::cout << "node not valid, deleting this";
            delete this;
            return;
        }
        data = node->data;
        delete node;
    }

    void print()
    {
        cout << "\n  " << data << "\n";
        cout << " / \\\n";
    
        if (left != nullptr) cout << left->data;
        else cout << "null";

        if (right != nullptr) cout << "   " << right->data << "\n";
        else cout << "  null\n";

        cout << typeid(left).name();
        if (left) cout << left;
        if (left == nullptr) cout << "is nullptr";
        if (left == NULL) cout << "is NULL";
    }

    // We can't have any operator < or > overloads
    // because they don't work with pointers. C++ limitation.
};
