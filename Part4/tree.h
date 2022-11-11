#ifndef TREE_H
#define TREE_H

#include "treenode.h"
#include <iostream>
using std::cout;
using std::endl;


// TODO your code goes here:
template<typename T>
class BinarySearchTree {
private:
    unique_ptr<TreeNode<T>> root;
public:
    BinarySearchTree() {}
    BinarySearchTree(const BinarySearchTree<T> &other)
    {
        if (root == nullptr)
        {
            root = unique_ptr<TreeNode<T>>(new TreeNode<T>(other.root.get()->data));
        }
        TreeNode<T> *oldTreeNode = other.root.get();
        TreeNode<T> *currentTreeNode = root.get();
    }

    void write(ostream &o) const
    {
        if (root)
        {
            root.get()->write(o);
        }

    }
    int maxDepth()
    {
        return root.get()->maxDepth();
    }

    TreeNode<T> *insert(T someData){
        if (root == nullptr) {
            root = unique_ptr<TreeNode<T>>(new TreeNode<T>(someData));
            return root.get();
        }
        bool found = 0;
        TreeNode<T> *ptr = root.get();
        while (found == 0) {
            if (!(ptr->data < someData) && !(someData < ptr->data)) {
                return ptr;
            }
            if (someData < ptr->data) {
                if (ptr->leftChild) {
                    ptr = ptr->leftChild.get();
                } else {
                    ptr->setLeftChild(new TreeNode<T>(someData));
                    TreeNode<T>* node_ptr = ptr->leftChild.get();
                    leftRotate(node_ptr);
                    return ptr->leftChild.get();
                }
            } else if (ptr->data < someData) {
                if (ptr->rightChild) {
                    ptr = ptr->rightChild.get();
                } else {
                    ptr->setRightChild(new TreeNode<T>(someData));
                    TreeNode<T>* node_ptr = ptr->rightChild.get();
                    rightRotate(node_ptr);
                    return ptr->rightChild.get();
                }
            }

        }
        return nullptr;
    }


  TreeNode<T> *find(T someData) const
  {
        TreeNode<T> *temp = root.get();
        if (!(temp->data < someData) && !(someData < temp->data))
        {
            return temp;
        }

        while (temp != nullptr)
        {
            if (!(temp->data < someData) && !(someData < temp->data))
            {
                return temp;
            }
            else if (someData < temp->data)
            {
                temp = temp->leftChild.get();
            }
            else if (temp->data < someData)
            {
                temp = temp->rightChild.get();
            }
        }
        return nullptr;
    }


    void operator=(const BinarySearchTree<T> &other)
    {

        root = unique_ptr<TreeNode<T>>(new TreeNode<T>(other.root.get()->data));
        TreeNode<T> *oldTreeNode = other.root.get();
        TreeNode<T> *currentTreeNode = root.get();
        buildPreOrder(oldTreeNode, currentTreeNode);
    }

    TreeNodeIterator<T> begin()
    {
        TreeNode<T> *temp = root.get();
        if(!temp){
            return nullptr;
        }
        while (temp->leftChild) {
            temp = temp->leftChild.get();
        }
        return TreeNodeIterator<T>(temp);
    }

    TreeNodeIterator<T> end()
    {
        return nullptr;
    }
    TreeNode<T> * leftRotate(TreeNode<T>* node_ptr)
    {
        while(node_ptr->parent)
        {
            if(node_ptr->parent->balanceFactor()==-2)
            {
                TreeNode<T>*nodeToMove= node_ptr->parent;
                TreeNode<T>* newSubTreeRoot =  node_ptr;

                if(newSubTreeRoot->parent->parent == nullptr)
                {
                    newSubTreeRoot->parent= nullptr;
                    unique_ptr<TreeNode<T>>newRoot= unique_ptr<TreeNode<T>>(newSubTreeRoot);
                    root.release();
                    root=std::move(newRoot);
                }
                else
                {
                    TreeNode<T>* newSubTreeRootParent =newSubTreeRoot->parent->parent;
                    newSubTreeRoot->parent=newSubTreeRootParent;
                    unique_ptr<TreeNode<T>>newSubTreeRootUP= unique_ptr<TreeNode<T>>(newSubTreeRoot);
                    newSubTreeRootParent->leftChild.release();
                    newSubTreeRootParent->leftChild=std::move(newSubTreeRootUP);

                }
                nodeToMove->parent= nullptr;
                nodeToMove->leftChild.release();
                nodeToMove->leftChild = nullptr;
                bool found = 0;
                TreeNode<T>*tempNodePointer = root.get();
                while (found == 0)
                {
                    found=1;
                    if (nodeToMove->data < tempNodePointer->data)
                    {
                        if (tempNodePointer->leftChild)
                        {
                            tempNodePointer = tempNodePointer->leftChild.get();
                            found=0;
                        } else
                        {
                            tempNodePointer->setLeftChild(nodeToMove);
                            tempNodePointer = tempNodePointer->leftChild.get();
                            while(tempNodePointer->parent)
                            {
                                if(tempNodePointer->parent->balanceFactor()==2)
                                {
                                    rightRotate(tempNodePointer);
                                }
                                else if(tempNodePointer->parent->balanceFactor()==-2)
                                {
                                    leftRotate(tempNodePointer);
                                }
                                else
                                {
                                    tempNodePointer=tempNodePointer->parent;
                                }
                            }
                            return node_ptr;
                        }
                    } 
                    else 
                    {
                        if (tempNodePointer->rightChild)
                        {
                            tempNodePointer = tempNodePointer->rightChild.get();
                            found=0;
                        }
                        else
                        {
                            tempNodePointer->setRightChild(nodeToMove);
                            tempNodePointer = tempNodePointer->rightChild.get();
                            while(tempNodePointer->parent)
                            {
                                if(tempNodePointer->parent->balanceFactor()==2)
                                {
                                    rightRotate(tempNodePointer);
                                }
                                else if(tempNodePointer->parent->balanceFactor()==-2)
                                {
                                    leftRotate(tempNodePointer);
                                }
                                else
                                {
                                    tempNodePointer=tempNodePointer->parent;
                                }
                            }
                            return node_ptr;
                        }
                    }
                }

            }
            else if (node_ptr->parent->balanceFactor()==2)
            {
                rightRotate(node_ptr);
            }
            else
            {
                node_ptr = node_ptr->parent;
            }
        }
    }
    TreeNode<T> * rightRotate(TreeNode<T>* node_ptr)
    {
        while(node_ptr->parent)
        {
            if(node_ptr->parent->balanceFactor()==2)
            {
                    TreeNode<T>*nodeToMove= node_ptr->parent;
                    TreeNode<T>* newSubTreeRoot =  node_ptr;

                    if(newSubTreeRoot->parent->parent == nullptr)
                    {
                        newSubTreeRoot->parent= nullptr;
                        unique_ptr<TreeNode<T>>newRoot= unique_ptr<TreeNode<T>>(newSubTreeRoot);
                        root.release();
                        root=std::move(newRoot);
                    }
                    else
                    {
                        TreeNode<T>* newSubTreeRootParent =newSubTreeRoot->parent->parent;
                        newSubTreeRoot->parent=newSubTreeRootParent;

                        unique_ptr<TreeNode<T>>newSubTreeRootUP= unique_ptr<TreeNode<T>>(newSubTreeRoot);
                        newSubTreeRootParent->rightChild.release();
                        newSubTreeRootParent->rightChild=std::move(newSubTreeRootUP);

                    }
                    nodeToMove->parent= nullptr;
                    nodeToMove->rightChild.release();
                    nodeToMove->rightChild = nullptr;
                    bool found = 0;
                    TreeNode<T>*tempNodePointer = root.get();
                    while (found == 0)
                    {
                        found=1;
                        if (nodeToMove->data < tempNodePointer->data)
                        {
                            if (tempNodePointer->leftChild)
                            {
                                tempNodePointer = tempNodePointer->leftChild.get();
                                found=0;
                            }else
                            {
                                tempNodePointer->setLeftChild(nodeToMove);
                                tempNodePointer = tempNodePointer->leftChild.get();
                                while(tempNodePointer->parent)
                                {
                                    if(tempNodePointer->parent->balanceFactor()==2)
                                    {
                                        rightRotate(tempNodePointer);
                                    }
                                    else if(tempNodePointer->parent->balanceFactor()==-2)
                                    {
                                        leftRotate(tempNodePointer);
                                    }
                                    else
                                    {
                                        tempNodePointer=tempNodePointer->parent;
                                    }
                                }
                                return node_ptr;
                            }

                        }
                        else
                        {
                            if (tempNodePointer->rightChild)
                            {
                                tempNodePointer = tempNodePointer->rightChild.get();
                                found=0;
                            }
                            else
                            {
                                tempNodePointer->setRightChild(nodeToMove);
                                tempNodePointer = tempNodePointer->rightChild.get();
                                while(tempNodePointer->parent){
                                    if(tempNodePointer->parent->balanceFactor()==2)
                                    {
                                        rightRotate(tempNodePointer);
                                    }
                                    else if(tempNodePointer->parent->balanceFactor()==-2)
                                    {
                                        leftRotate(tempNodePointer);
                                    }
                                    else
                                    {
                                        tempNodePointer=tempNodePointer->parent;
                                    }
                                }
                                return node_ptr;
                            }
                        }
                    }

            }
            else if(node_ptr->parent->balanceFactor()==-2)
            {
                leftRotate(node_ptr);
            }
            else
            {
                node_ptr = node_ptr->parent;
            }
        }
    }
};
#endif