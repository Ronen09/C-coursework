#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists
template<typename T>
class Node {
    public:
    T data;
    Node<T>* next;
    Node<T>* previous;
    Node(T param_data)
    {
        data=param_data;
        next = nullptr;
        previous = nullptr;
    }
};

template<typename T>
class NodeIterator {
  
private:
    
    Node<T>* current;
    
public:
    

    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }
    
    T & operator*() {
        return current->data;
    }

    Node<T>* getNode()
    {
        return current;
    }

    // TODO: complete the code for NodeIterator here
    NodeIterator<T> operator++()
    {
        current = current->next;
        return *this;
    }
    bool operator==(NodeIterator<T> other)
    {
        Node<T>* other_node_ptr = other.current;
        return (other_node_ptr == this->current);
    }
    bool operator!=(NodeIterator<T> other)
    {
        Node<T>* other_node_ptr = other.current;
        return !(other_node_ptr == this->current);
    }

    
};
template<typename T>
class ConstNodeIterator {
  
private:
    
    Node<T>* current;
    
public:
    

    ConstNodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }
    
    T const& operator*(){
        return current->data;
    }

    Node<T>* getNode() const
    {
        return current;
    }

    // TODO: complete the code for NodeIterator here
    ConstNodeIterator<T> operator++()
    {
        current = current->next;
        return *this;
    }
    bool operator==(ConstNodeIterator<T> other) const
    {
        Node<T>* other_node_ptr = other.current;
        return (other_node_ptr == this->current);
    }
    bool operator!=(ConstNodeIterator<T> other) const
    {
        Node<T>* other_node_ptr = other.current;
        return !(other_node_ptr == this->current);
    }
};

// do not edit below this line

#endif
