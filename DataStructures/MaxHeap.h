#pragma once

#include <iostream>
#include "HNode.h"

template <class T>
class MaxHeap
{
public:
    HNode<T>* root = nullptr;

    /**
     * \brief Add a node to the binary tree.
     * \param data The value the new node should have.
     * \return Ptr to the new node.
     */
    HNode<T>* add(const T& data, int i, int size);

    /**
     * \brief Remove a node from the tree. Automatically
     * shuffles the nodes back in their correct place.
     * \param value The value of the node to remove.
     * \param rt The tree's root node.
     * \return The updated node (used for recursion).
     */
    HNode<T>* remove(const T& value, HNode<T>* rt);

    /**
     * \return The number of nodes in the tree. 
     */
    int size() const { return size_; }

private:
     int size_;
};

template <class T>
HNode<T>* MaxHeap<T>::add(const T& data, int i, int size)
{
     if (!root) root = new HNode<T>(data);
     else
     {
         int num = 2 * i;
     }
}
