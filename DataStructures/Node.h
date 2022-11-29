#pragma once

#include <iostream>

using namespace std;

/**
 * \brief Node for use in binary tree.
 */
template<class T>
struct Node
{
    Node(T data) : data(data)
    {
        left = right = nullptr;
    }
    
    Node *left, *right;
    T data;

    void print()
    {
        cout << "\n  " << data << "\n";
        cout << " / \\\n";
    
        if (left) cout << left->data;
        else cout << "null";

        if (right) cout << "   " << right->data << "\n";
        else cout << "  null\n";
    }

    // We can't have any operator < or > overloads
    // because they don't work with pointers. C++ limitation.
};
