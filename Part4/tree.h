#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:
template<typename T>
class BinarySearchTree{
    private:
        unique_ptr<TreeNode<T>> root;
    public:
        BinarySearchTree()
        {
        }
        BinarySearchTree(BinarySearchTree& tree)
        {
            while(true)
            {
                if(tree.root->leftChild != nullptr)
                {
                    insert(tree.root->leftChild->data);
                }
                else if(tree.root->rightChild != nullptr)
                {
                    insert(tree.root->rightChild->data);
                }
                else
                {
                    break;
                }
            }
        }
        BinarySearchTree operator=(BinarySearchTree& tree)
        {
            while(true)
            {
                if(tree.root->leftChild != nullptr)
                {
                    insert(tree.root->leftChild->data);
                }
                else if(tree.root->rightChild != nullptr)
                {
                    insert(tree.root->rightChild->data);
                }
                else
                {
                    break;
                }
            }
        }
        write(ostream& out) const
        {
            if(root != nullptr)
            {
                root->write(out);
            }
        }
        TreeNode<T>* insert(T data)
        {
            if(root == nullptr)
            {
                root = unique_ptr<TreeNode<T>>(new TreeNode<T>(data));
                return root.get();
            }
            else
            {
                TreeNode<T>* current = root.get();
                while(true)
                {
                    if(data < current->data)
                    {
                        if(current->leftChild == nullptr)
                        {
                            current->setLeftChild(new TreeNode<T>(data));
                            break;
                        }
                        else
                        {
                            current = current->leftChild.get();
                        }
                    }
                    else if(current->data < data)
                    {
                        if(current->rightChild == nullptr)
                        {
                            current->setRightChild(new TreeNode<T>(data));
                            return current->rightChild.get();
                            break;
                        }
                        else
                        {
                            current = current->rightChild.get();
                        }
                    }
                    else
                    {
                        return current;
                    }
                }
            }
        }
        TreeNode<T>* find(T data) const
        {
            if(root == nullptr)
            {
                return nullptr;
            }
            else
            {
                TreeNode<T>* current = root.get();
                while(true)
                {
                    if(data < current->data)
                    {
                        if(current->leftChild == nullptr)
                        {
                            return nullptr;
                        }
                        else
                        {
                            current = current->leftChild.get();
                        }
                    }
                    else if(data == current->data)
                    {
                        return current;
                    }
                    else
                    {
                        if(current->rightChild == nullptr)
                        {
                            return nullptr;
                        }
                        else
                        {
                            current = current->rightChild.get();
                        }
                    }
                }
            }
        }
};



// do not edit below this line

#endif
