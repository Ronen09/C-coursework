#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <initializer_list>
using std::initializer_list;
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
    LinkedList(initializer_list<T> l)
    {   
        length = 0;
        for(auto list_item:l)
        {
            this->push_back(list_item);
        }
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
    ConstNodeIterator<T> begin() const
    {
        return ConstNodeIterator<T>(head);
    }
    ConstNodeIterator<T> end() const
    {
        return ConstNodeIterator<T>(nullptr);
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
 
        
         while (current != NULL) {
            temp = current->previous;
            current->previous = current->next;
            current->next = temp;
            current = current->previous;
    }
 
    
    if (temp != NULL)
        head = (temp->previous);
    }
    NodeIterator<T> insert(NodeIterator<T>ptr,T data)
    {
        Node<T>* ins = ptr.getNode();
        Node<T>* ins_next = ins->next;
        Node<T>* ins_prev = ins->previous;
        Node<T>* new_node = new Node<T>(data);
        new_node->next = ins;
        new_node->previous = ins_prev;
        ins_prev->next = new_node;
        ins_prev = new_node;
        return NodeIterator(new_node);
    }
    NodeIterator<T> erase(NodeIterator<T>ptr)
    {
        Node<T>* ins = ptr.getNode();
        Node<T>* ins_next = ins->next;
        Node<T>* ins_prev = ins->previous;
        ins_next->previous = ins_prev;
        ins_prev->next = ins_next;
        delete ins;
        return NodeIterator(ins_next);
    }
};



// do not edit below this line

#endif
