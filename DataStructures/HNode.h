#pragma once

#include <iostream>

/**
 * \brief Heap node. Used in max/min heap binary trees.
 */
template <class T>
struct HNode
{
     HNode(T data) : data(data)
     {
      parent = left = right = nullptr;
     }
        
     HNode *parent, *left, *right;
     T data;

     void print()
     {
      std::cout << "\n  " << data << "\n";
      std::cout << " / \\\n";
        
      if (left != nullptr) std::cout << left->data;
      else std::cout << "null";

      if (right != nullptr) std::cout << "   " << right->data << "\n";
      else std::cout << "  null\n";
     }

     // We can't have any operator < or > overloads
     // because they don't work with pointers. C++ limitation.
};
