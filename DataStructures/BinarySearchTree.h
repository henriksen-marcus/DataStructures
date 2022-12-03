#pragma once

#include "BNode.h"
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
    BNode<T>* root = nullptr;

    /**
     * \brief Add a node to the binary tree.
     * \param data The value the new node should have.
     * \return Ptr to the new node.
     */
    BNode<T>* add(const T& data);

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
     * \brief Remove a node from the tree. Automatically
     * shuffles the nodes back in their correct place.
     * \param value The value of the node to remove.
     * \param rt The tree's root node.
     * \return The updated node (used for recursion).
     */
    BNode<T>* remove(const T& value, BNode<T>* rt);

    /**
     * \return The smallest node from the subtree
     * of the given root.
     * \param rt The root node.
     */
    BNode<T>* min(BNode<T>* rt);

    /**
     * \return The largest node from the subtree
     * of the given root.
     * \param rt The root node.
     */
    BNode<T>* max(BNode<T>* rt);

    /**
     * \brief Print the value of every
     * node in an ascending manner.
     * \param rt The tree's root node.
     * \remarks In-order tree traversal.
     */
    void print_in_order(BNode<T>* rt);

    /**
     * \brief Print the value of every
     * node.
     * \param rt The tree's root node.
     * \remarks Post-order tree traversal.
     */
    void print_post_order(BNode<T>* rt);

    /**
     * \brief Print the value of every
     * node.
     * \param rt The tree's root node.
     * \remarks Pre-order tree traversal.
     */
    void print_pre_order(BNode<T>* rt);

    /**
     * \param rt The tree's root node.
     * \param value The value to look for.
     * \return Pointer to the found node. Nullptr
     * if no node was found.
     */
    BNode<T>* find(BNode<T>* rt, const T& value);

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
    
    BNode<T>* add_recursive(const T& data, BNode<T>* rt);
};

template<class T>
BNode<T>* BinarySearchTree<T>::add(const T& data)
{
    if (!root)
    {
     root = new BNode<T>(data);
     size_++;
     return root;
    }
       
    return add_recursive(data, root);
}

template<class T>
BNode<T>* BinarySearchTree<T>::add_recursive(const T& data, BNode<T>* rt)
{
    if (data < rt->data)
    {
     if (rt->left) return add_recursive(data, rt->left);
     rt->left = new BNode<T>(data);
     size_++;
     return rt->left;
    }
    else if (data > rt->data)
    {
     if (rt->right) return add_recursive(data, rt->right);
     rt->right = new BNode<T>(data);
     size_++;
     return rt->right;
    }
    // Duplicate was found
    return nullptr;
}

template <class T>
BNode<T>* BinarySearchTree<T>::remove(const T& value, BNode<T>* rt)
{
    // If we find a nullptr it means the value doesn't exist in the tree
    if (!rt) return rt;

    // Value is less than the current root 
    if (value < rt->data) rt->left = remove(value, rt->left);
    // Value is more than the current root
    else if (value > rt->data) rt->right = remove(value, rt->right);
    else
    { // We have found the node
        if (!rt->left and !rt->right)
        { // No children
            delete rt; // Deallocate from memory, remove it's value
            rt = nullptr; // rt still has it's address, we set it to null to be sure
        }
        else if (!rt->left)
        { // One child
            auto temp = rt;
            rt = rt->right; // Make the right child the root of the subtree
            delete temp;
            
            /* Remember that rt is currently equal to one of the nodes in the tree.
             * We cannot delete rt directly because it would make a hole in the tree.
             * All sub-nodes would be disconnected from the tree.
             * So we update rt (the current node in the tree) and delete the old
             * dangling pointer (now referenced by temp). */
        }
        else if (!rt->left)
        { // One child
            auto temp = rt;
            rt = rt->left; // Make the left child the root of the subtree
            delete temp;
        }
        else
        { // Two children
            auto temp = min(rt->right); // Get the in-order successor
            rt->data = temp->data; // Update the current node's data

            /* Now we do some more recursion. BEFORE updating the tree by returning rt,
             * we delete the in-order successor, so we don't delete the rt right after
             * updating it. */
            rt->right = remove(temp->data, rt->right);
        }
    }
    return rt; // We return the new state of the current node to update the parent's reference
}

template <class T>
BNode<T>* BinarySearchTree<T>::min(BNode<T>* rt)
{
    return rt->left ? min(rt->left) : rt;
}

template <class T>
BNode<T>* BinarySearchTree<T>::max(BNode<T>* rt)
{
    return rt->right ? min(rt->right) : rt;
}

template<class T>
void BinarySearchTree<T>::print_in_order(BNode<T>* rt)
{
    // Go as far left as we can
    if (rt->left) print_in_order(rt->left);
    std::cout << rt->data << " ";
    if (rt->right) print_in_order(rt->right);
}

template<class T>
void BinarySearchTree<T>::print_post_order(BNode<T>* rt)
{
    // Go as far left as we can
    if (rt->left) print_post_order(rt->left);
    if (rt->right) print_post_order(rt->right);
    std::cout << rt->data << " ";
}

template <class T>
void BinarySearchTree<T>::print_pre_order(BNode<T>* rt)
{
    // Go as far left as we can
    std::cout << rt->data << " ";
    if (rt->left) print_post_order(rt->left);
    if (rt->right) print_post_order(rt->right);
}

template<class T>
BNode<T>* BinarySearchTree<T>::find(BNode<T>* rt, const T& value)
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

    std::uniform_int_distribution<int> dist(min, max);
    std::random_device rd;
       
    for (int i{}; i < amount; i++)
    {
     add(dist(rd));
    }
    return size();
}

