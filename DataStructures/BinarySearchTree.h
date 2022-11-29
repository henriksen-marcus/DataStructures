#pragma once
#include "Node.h"
#include <iostream>
#include <random>

/**
 * \brief Binary search tree.
 * \remarks The reason I use "const &" on a
 * lot of arguments is in the case of T being
 * a large data type like a string. Copying
 * ints is fine because they are the same size
 * as a reference (4 bytes), but strings can be much
 * larger, so we pass by reference (&) and promise
 * not to modify it (const) now that we have a
 * direct way to edit it.
 */
template <class T>
class BinarySearchTree
{
public:
    Node<T>* root = nullptr;

    /**
     * \brief Add a node to the binary tree.
     * \param data The value the new node should have.
     * \return Ptr to the new node.
     */
    Node<T>* add(const T& data);

    /**
     * \brief Add a set of nodes to the binary tree.
     * \param data The first value to add.
     * \param args Optional elements to add.
     * \remarks This function accepts an infinite
     * number of arguments, and serves as a quick
     * method of adding nodes to the tree.
     * Variadic function template.
     */
    template<class... Types>
    void add(const T& data, const Types&... args)
    {
        add(data);
        add(args...);
    }


    /**
     * \brief Print the value of every
     * node in an ascending manner.
     * \param rt The tree's root node.
     * \remarks In-order tree traversal.
     */
    void print_sorted(Node<T>* rt);

    /**
     * \brief Print the value of every
     * node.
     * \param rt The tree's root node.
     * \remarks Post-order tree traversal.
     */
    void print_unsorted(Node<T>* rt);

    /**
     * \param rt The tree's root node.
     * \param value The value to look for.
     * \return Pointer to the found node. Nullptr
     * if no node was found.
     */
    Node<T>* find(Node<T>* rt, const T& value);

    /**
     * \brief Fills the list with integers starting
     * at the next available slot with the specified
     * number of elements.
     * \param min The smallest possible number in the fill pattern.
     * \param max The largest possible number in the fill pattern.
     * \param amount The number of elements to add.
     * \return The new list size.
     * \remarks If no amount is given the entire range from
     * min-max will be printed.
     */
    int fill(int min, int max, int amount = -1);

    /**
     * \return The number of nodes in the tree. 
     */
    int size() const { return size_; }

private:
    int size_ = 0;
    
    Node<T>* add_recursive(const T& data, Node<T>* rt);
};



template<class T>
Node<T>* BinarySearchTree<T>::add(const T& data)
{
    if (!root)
    {
     root = new Node<T>(data);
     size_++;
     return root;
    }
       
    return add_recursive(data, root);
}

template<class T>
Node<T>* BinarySearchTree<T>::add_recursive(const T& data, Node<T>* rt)
{
    if (data < rt->data)
    {
     if (rt->left) return add_recursive(data, rt->left);
     rt->left = new Node<T>(data);
     size_++;
     return rt->left;
    }
    else if (data > rt->data)
    {
     if (rt->right) return add_recursive(data, rt->right);
     rt->right = new Node<T>(data);
     size_++;
     return rt->right;
    }
    // Duplicate was found
    return nullptr;
}

template<class T>
void BinarySearchTree<T>::print_sorted(Node<T>* rt)
{
    // Go as far left as we can
    if (rt->left) print_sorted(rt->left);
    cout << rt->data << " ";
    if (rt->right) print_sorted(rt->right);
}

template<class T>
void BinarySearchTree<T>::print_unsorted(Node<T>* rt)
{
    // Go as far left as we can
    if (rt->left) print_unsorted(rt->left);
    if (rt->right) print_unsorted(rt->right);
    cout << rt->data << " ";
}

template<class T>
Node<T>* BinarySearchTree<T>::find(Node<T>* rt, const T& value)
{
    // Value is less than root, find it in the left side
    if (value < rt->data) return find(rt->left, value);
    // Value is more than root, find it in the right side
    if (value > rt->data) return find(rt->right, value);
    // If none of the above are true, we are looking at the root
    return rt;
}

template<class T>
int BinarySearchTree<T>::fill(int min, int max, int amount)
{
    if (!amount) return size_;
    if (amount == -1) amount = max - min + 1;

    uniform_int_distribution<int> dist(min, max);
    random_device rd;
       
    for (int i{}; i < amount; i++)
    {
     add(dist(rd));
    }
    return size();
}
