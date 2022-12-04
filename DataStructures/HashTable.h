#pragma once

#include <iostream>
#include <vector>
#include "LinkedList.h"

template <class T>
class HashTable
{
public:
    std::vector<LinkedList<T>*> arr;

    int size() const { return arr.size(); }

    /**
     * \brief Add en element to the hash table.
     * \return The new table size.
     */
    int add(const T& data);

    int hash(const T& data);

    /**
     * \return If the value was found in the hash table.
     */
    bool find(const T& value);

    bool remove(const T& value);

    void print();

    const LinkedList<T>* operator [](int i) const { return arr[i]; }
};

template <class T>
int HashTable<T>::add(const T& data)
{
    int i = hash(data);
    
    // Check if the index exists
    if (size() - 1 < i) arr.resize(i + 1);

    // Check if the index is null, if so put a linked list ptr there
    if (!arr[i]) arr[i] = new LinkedList<T>();
    
    arr[i]->add(data);
    std::cout << "Added to slot " << i << std::endl;
    return arr.size();
}

template <class T>
int HashTable<T>::hash(const T& data)
{
    return data % 7;
}

template <class T>
bool HashTable<T>::find(const T& value)
{
    int i = hash(value);
    
    // Check if the index exists
    if (size() - 1 < i) return false;

    // Check if it exists in the linked list
    if (arr[i]) return static_cast<bool>(arr[i]->find(value));
    return false;
}

template <class T>
bool HashTable<T>::remove(const T& value)
{
    int i = hash(value);
    
    // Check if the index exists
    if (size() - 1 < i) return false;

    // Check if it exists in the linked list
    if (arr[i]) arr[i]->remove(arr[i]->find(value));
    return false;
}

template <class T>
void HashTable<T>::print()
{
    for (auto list : arr)
    {
        if (list) list->print();
    }
}
