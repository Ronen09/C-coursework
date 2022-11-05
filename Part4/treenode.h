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
    TreeNode(T param_data)
    {
        data=param_data;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
    }
    setLeftChild(TreeNode<T>* child)
    {
        leftChild = unique_ptr<TreeNode<T>>(child);
        child->parent = this;
    }
    setRightChild(TreeNode<T>* child)
    {
        rightChild = unique_ptr<TreeNode<T>>(child);
        child->parent = this;
    }
    write(ostream& out) const
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

};
// do not edit below this line

#endif
