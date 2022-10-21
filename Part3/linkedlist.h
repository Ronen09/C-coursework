#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:
template<typename T>
class LinkedList{
    public:
    Node<T>* head;
    Node<T>* tail;
    int length;
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
    void push_front(T param_data)
    {
        Node<T>* new_data = new Node<T>(param_data);
        Node<T>* temp = head;
        if(length == 0)
        {
            head = new_data;
            tail = new_data;
        }
        else
        {
            head = new_data;
            new_data->next = temp;
            temp->previous = new_data;
        }
        ++length;
    }
    T front()
    {
        return head->data;
    }
    void push_back(T param_data)
    {
        Node<T>* new_data = new Node<T>(param_data);
        Node<T>* temp = tail;
        if(length == 0)
        {
            head = new_data;
            tail = new_data;
        }
        else
        {
            tail = new_data;
            new_data->previous = temp;
            temp->next = new_data;
        }
        length++;
    }
    T back()
    {
        return tail->data;
    }
    int size()
    {
        return length;
    }
    NodeIterator<T> begin()
    {
        return NodeIterator<T>(head);
    }
    NodeIterator<T> end()
    {
        return NodeIterator<T>(nullptr);
    }
    ~LinkedList()
    {
        Node<T>* move = head;
        while(head)
        {
            head = move->next;
            delete move;
            move = head;
        }
    }
    void reverse()
    {
        Node<T>* temp = NULL;
        Node<T>* current = head;
 
        /* swap next and prev for all nodes of
        doubly linked list */
         while (current != NULL) {
            temp = current->previous;
            current->previous = current->next;
            current->next = temp;
            current = current->previous;
    }
 
    /* Before changing the head, check for the cases like
       empty list and list with only one node */
    if (temp != NULL)
        head = (temp->previous);
    }
};



// do not edit below this line

#endif
