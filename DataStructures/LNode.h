#pragma once

#include <iostream>

/**
 * \brief Linked node. For use with linked lists.
 */
template<class T>
struct LNode
{
    LNode(T data) : data(data)
    {
        next = nullptr;    
    }
    
    LNode* next;
    T data;

    /**
     * \brief Print the value of the node and it's next
     */
    void print()
    {
        std::cout << data << " -> ";
        if (next) cout << next->data;
        else cout << "null";
        cout << "\n";
    }
};
