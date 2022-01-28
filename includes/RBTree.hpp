#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

namespace ft
{
    template< class Key >
    struct Node
    {
        Key data; // holds the key
        Node *parent; // pointer to the parent
        Node *left; // pointer to left child
        Node *right; // pointer to right child
        int color; // 1 -> Red, 0 -> Black
    };

    template< class Key, class T >
    class RBTree
    {
        private:
            Node< Key > *root = NULL;

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(Node< Key > *node)
            {
                node->data = 0;
                node->parent = NULL;
                node->left = NULL;
                node->right = NULL;
                node->color = 0;
            }
            void swap(Node< Key > **x, Node< Key > **y)
            {
                Node< T > **tmp = x;
                x = y;
                y = tmp;
            }
        public:
            typedef Node< Key >* NodePtr;

            void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;
                //NodePtr origin = root;

                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr leftY = y->left;

                y->parent = tmpX->parent;
                y->left = tmpX;
                x->parent = tmpY;
                x->right = leftY;
                //swap(&x->right, &y->left);
                swap(&x, &y);
                //if (!y->parent)
                root = y;
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                //NodePtr origin = root;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->right;

                y->parent = tmpX;
                y->left = rightX;
                x->right = tmpY;
                x->parent = tmpY->parent;
                //swap(&x->right, &y->left);
                swap(&x, &y);
                //if (!x->parent)
                root = x;
                root->color = 0;
            }
            void insert(int key)
            {
                NodePtr node = new Node< Key >;
                initializeNode(node);
                node->data = key;
                node->color = 1; // new node must be red
                
                NodePtr fromRoot = root;
                NodePtr parentNode = NULL;
                while (fromRoot)
                {
                    parentNode = fromRoot;
                    if (node->data < fromRoot->data)
                        fromRoot = fromRoot->left;
                    else
                        fromRoot = fromRoot->right;
                }
                node->parent = parentNode;
                if (!node->parent)
                {
                    root = node;
                    node->color = 0;
                    return ;
                }
                if (node->data < parentNode->data)
                {
                    parentNode->left = node;
                    rightRotate(root);
                }
                else
                {
                    parentNode->right = node;
                    leftRotate(root);
                }
                recolor(getRoot());
            }
            NodePtr getRoot()
            {
                return root;
            }
            void recolor (NodePtr node)
            {
                if (node != NULL)
                {
                    if (node->left && node->left->color)
                    {
                        if (node->left->right)
                            node->left->right->color = 0;
                        if (node->left->left)
                            node->left->left->color = 0;
                    }
                    if (node->right && node->right->color)
                    {
                        if (node->right->right)
                            node->right->right->color = 0;
                        if (node->right->left)
                            node->right->left->color = 0;
                    }
                    recolor(node->left);
                    recolor(node->right);
                }
                if (root->right)
                    root->right->color = 0;
                if (root->left)
                    root->left->color = 0;
            }
            void deleteNode(int key)
            {
                NodePtr found = NULL;
                NodePtr node = getRoot();
                int i = 0;
                int count = i;
                while (node)
                {
                    if (node->data == key)
                        found = node;
                    if (key <= node->data)
                        node = node->left;
                    else
                        node = node->right;
                    i++;
                }
                count = i;
                if (!found)
                {
                    std::cout << "Couldn't find key in the tree"<< std::endl;
                        return ;
                }
                std::cout << "****" << std::endl;
                std::cout << "root" << root->data << std::endl;
               /* if (key == root->data)
                {
                    while (found && found->left)
                        rightRotate(root);
                    while (found && found->right)
                        leftRotate(root);
                    if (found == found->parent->right)
                        found->parent->right = found->right;
                    else
                        found->parent->left = found->right;
                    initializeNode(found);
                    delete found;
                    recolor(root);
                    return ;
                }*/

                if (key >= root->data)
                {
                    while (found && found->left && found->left->right)
                        rightRotate(root);
                    if (found == found->parent->right)
                        found->parent->right = found->right;
                    else
                        found->parent->left = found->right;
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    recolor(root);
                }
                else
                {
                    while (found && found->right && found->right->left)
                        leftRotate(root);
                    if (found == found->parent->right)
                        found->parent->right = found->left;
                    else
                        found->parent->left = found->left;
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    recolor(root);
                }
            }
            void printHelper(NodePtr root, std::string indent, bool last)
            {
                // print the tree structure on the screen
                if (root != NULL)
                {
                    std::cout<<indent;
                    if (last)
                    {
                        std::cout<<"R----";
                        indent += "     ";
                    }
                    else
                    {
                        std::cout<<"L----";
                        indent += "|    ";
                    }
                    std::string sColor = root->color?"RED":"BLACK";
                    std::cout<<root->data<<"("<<sColor<<")"<<std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }
            void prettyPrint()
            {
                if (root)
                    printHelper(this->root, "", true);
	        }
            void freeNodes(NodePtr node)
            {
                if (node != NULL)
                {
                    freeNodes(node->left);
                    freeNodes(node->right);
                }
                delete node;
                node = NULL;
            }
            // If a node is red, both of its children are black. This means no two nodes on a path can be red nodes.
            // Every path from a root node to a NULL node has the same number of black nodes.
    };
}

//https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#endif