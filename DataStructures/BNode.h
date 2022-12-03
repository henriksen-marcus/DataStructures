#pragma once

#include <iostream>

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

    void print()
    {
       std:: cout << "\n  " << data << "\n";
        std::cout << " / \\\n";
    
        if (left != nullptr) std::cout << left->data;
        else std::cout << "null";

        if (right != nullptr) std::cout << "   " << right->data << "\n";
        else std::cout << "  null\n";
    }

    // We can't have any operator < or > overloads
    // because they don't work with pointers. C++ limitation.
};
