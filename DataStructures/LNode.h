#pragma once

#include <iostream>

/**
 * \brief Linked node. For use with linked lists.
 */
template<class T>
struct LNode
{
    LNode(const T& data) : data(data)
    {
        next = nullptr;    
    }
    
    LNode<T>* next;
    T data;

    /**
     * \brief Print the value of the node and it's next
     */
    void print()
    {
        std::cout << data << " -> ";
        if (next) std::cout << next->data;
        else cout << "null";
        std::cout << "\n";
    }
};