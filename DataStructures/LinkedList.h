#pragma once

#include "LNode.h"

template <class T>
class LinkedList
{
public:
    LinkedList()
    {
        head = nullptr;
        size_ = 0;
    }
    
    LNode<T> *head;

    /**
     * \brief Add a node at the end of the list.
     * \param data The data the new node should contain.
     * \return The new list size.
     */
    int add(const T& data);
    int add_front(const T& data);

    /**
     * \brief Insert a new node in the list.
     * The node currently there will be pushed back.
     * \param data The data the new node should contain.
     * \param index The index to insert at.
     * \return The new list size.
     */
    int insert(const T& data, int index);

    /**
     * \brief Insert a new node in the list after the
     * given node.
     * \param data The data the new node should contain.
     * \param node The index to insert after.
     * \return The new list size.
     */
    int insert_after(LNode<T>* node, const T& data);

    /**
     * \brief Add a set of nodes to the end of the list.
     * \param data The data the first node should contain.
     * \param args Optional, add any number of arguments
     * here to add more nodes to the list.
     * \remarks Variadic template function.
     */
    template<class... Types>
    void add(const T& data, const Types&... args)
    {
        add(data);
        add(args...);
    }

    void remove(LNode<T>* node);
    void remove(const T& value);
    void pop();

    void empty();

    bool is_empty() const { return size_ == 0; }

    /**
     * \brief Print the entire list.
     */
    void print();

    /**
     * \return Ptr to the last element in the list.
     */
    LNode<T>* get_tail();

    LNode<T>* find(const T& value);

    LNode<T>* at(int index);
    
    int size() const { return size_; }

    T operator [](int i)
    {
        int counter{};
        auto current_node = head;
        while (current_node)
        {
            if (counter++ == i) return current_node->data;
            current_node = current_node->next;
        }
        return NULL;
    }

private:
    int size_;

    void empty_private(LNode<T>* hd);
};


template <class T>
int LinkedList<T>::add(const T& data)
{
    if (head == nullptr) head = new LNode<T>(data);
    else get_tail()->next = new LNode<T>(data);
    return ++size_;
}

template <class T>
int LinkedList<T>::add_front(const T& data)
{
    auto temp = new LNode<T>(data);
    temp->next = head;
    head = temp;
}

template <class T>
int LinkedList<T>::insert(const T& data, int index)
{
    auto temp = at(index);
    if (!temp) return -1;
    
    auto new_node = new LNode<T>(data);
    new_node->next = temp->next;
    temp->next = new_node;
    return size_++;
}

template <class T>
int LinkedList<T>::insert_after(LNode<T>* node, const T& data)
{
    auto temp = node->next;
    node->next = new LNode<T>(data);
    node->next = temp;
    return size_++;
}


template <class T>
void LinkedList<T>::remove(LNode<T>* node)
{
    if (!node) return;
    if (node == head)
    {
        // We need to keep track of head
        head = head->next;
        delete node;
        --size_;
        return; 
    }
    
    auto current_node = head;
    while (current_node->next != node)
    {
       current_node = current_node->next;
    }
    // We are now at the node before the node to be deleted,
    // if it was found

    // Make sure we found the node and didn't just go through
    // the whole loop
    if (current_node->next == node)
    {
        current_node->next = node->next;
        delete node;
        --size_;
    }
}

template <class T>
void LinkedList<T>::remove(const T& value)
{
    remove(find(value));
}

template <class T>
void LinkedList<T>::pop()
{
    remove(get_tail());
}

template <class T>
void LinkedList<T>::empty()
{
    if (head) empty_private(head);
}

template <class T>
void LinkedList<T>::empty_private(LNode<T>* hd)
{
    if(hd->next) empty_private(hd->next);
    delete hd;
    size_--;
}

template <class T>
void LinkedList<T>::print()
{
    auto current_node = head;
    while (current_node)
    {
        std::cout << current_node->data << " -> ";
        current_node = current_node->next;
    }
    std::cout << "null\n"; 
}

template <class T>
LNode<T>* LinkedList<T>::get_tail()
{
    auto current_node = head;
    while (current_node->next)
    {
        current_node = current_node->next;
    }
    return current_node;
}

template <class T>
LNode<T>* LinkedList<T>::find(const T& value)
{
    auto current_node = head;
    while (current_node)
    {
        if (current_node->data == value) return current_node;
        current_node = current_node->next;
    }
    return nullptr;
}

template <class T>
LNode<T>* LinkedList<T>::at(int index)
{
    int count{};
    auto current_node = head;
    while (current_node)
    {
        if (count++ == index) return current_node;
        current_node = current_node->next;
    }
    return nullptr;
}


