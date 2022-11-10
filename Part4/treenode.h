#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:


template <typename T>
class TreeNode {
    public:
    T data;
    unique_ptr<TreeNode<T>> leftChild;
    unique_ptr<TreeNode<T>> rightChild;
    TreeNode<T>* parent;
    TreeNode(const T &param_data) : data(param_data), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
    void setLeftChild(TreeNode<T>* child)
    {
        leftChild = unique_ptr<TreeNode<T>>(child);
        child->parent = this;
    }
    void setRightChild(TreeNode<T>* child)
    {
        rightChild = unique_ptr<TreeNode<T>>(child);
        child->parent = this;
    }
    void write(ostream& out) const
    {
        if(leftChild != nullptr)
        {
            leftChild->write(out);
        }
        out << " " << data << " ";
        if(rightChild != nullptr)
        {
            rightChild->write(out);
        }
    }
    int maxDepth()
        {
            // Root being null means tree doesn't exist.
            if (this == NULL)
                return 0;
        
            // Get the depth of the left and right subtree 
            // using recursion.
            int leftDepth = this->leftChild.get()->maxDepth();
            int rightDepth = this->rightChild.get()->maxDepth();

            // Choose the larger one and add the root to it.
            if (leftDepth > rightDepth)
                return leftDepth + 1;
            else
                return rightDepth + 1;
        }
    TreeNode<T>* operator=(TreeNode<T>* node)
    {
        data = node->data;
        leftChild = node->leftChild;
        rightChild = node->rightChild;
        parent = node->parent;
    }
};

template <typename T>
class TreeNodeIterator
{
    private:
        TreeNode<T>* current;
    public:
        TreeNodeIterator(TreeNode<T>* param_current) : current(param_current) {}
        TreeNodeIterator operator++()
        {
            if(current->rightChild != nullptr)
            {
                current = current->rightChild.get();
                while(current->leftChild != nullptr)
                {
                    current = current->leftChild.get();
                }
            }
            else
            {
                while(current->parent != nullptr && current->parent->rightChild.get() == current)
                {
                    current = current->parent;
                }
                current = current->parent;
            }
            return *this;
        }
        TreeNodeIterator operator++(int)
        {
            TreeNodeIterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const TreeNodeIterator& other) const
        {
            return current == other.current;
        }
        bool operator!=(const TreeNodeIterator& other) const
        {
            return current != other.current;
        }
        T& operator*()
        {
            return current->data;
        }
        T* operator->()
        {
            return &(current->data);
        }
        
};


// do not edit below this line

#endif
