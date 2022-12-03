#pragma once

#include <iostream>
#include <vector>
#include "LinkedList.h"

template <class T>
class HashTable
{
public:
    std::vector<LinkedList<T>*> arr;
};
