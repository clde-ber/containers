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
                NodePtr tmpY = y;
                NodePtr tmpX = x;

                swap(&x, &y);
                x->left = tmpX->left;
                x->right = tmpY->left;
                y->left = tmpX;
                y->right = tmpY->right;
                root = y;
                root->parent = NULL;
                x->parent = root;
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;

                swap(&x, &y);
                y->right = tmpY->right;
                y->left = tmpX->right;
                x->right = tmpY;
                x->left = tmpX->left;
                root = x;
                root->parent = NULL;
                y->parent = root;
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
                NodePtr child = NULL;
                std::cout << "************" << std::endl;
                while (fromRoot)
                {
                    parentNode = fromRoot;
                    if (node->data < fromRoot->data)
                        fromRoot = fromRoot->left;
                    else
                        fromRoot = fromRoot->right;
                    if (fromRoot)
                    {
                        child = fromRoot;
                        child->parent = parentNode;
                        /*std::cout << "child " << child->data << std::endl;
                        if (child->left)
                        std::cout << "child left" << child->left->data << std::endl;
                        if (child->right)
                        std::cout << "child right" << child->right->data << std::endl;*/
                    }
                }
                node->parent = parentNode;
                if (node->parent)
                std::cout << "node->parent = " << node->parent->data << std::endl;
                std::cout << "node = " << node->data << std::endl;
                if (!node->parent)
                {
                    std::cout << "root = node " << std::endl;
                    //node->parent = NULL;
                    root = node;
                    std::cout << "node->parent = " << node->parent << std::endl;
                    node->color = 0;
                    return ;
                }
                if (node->data < parentNode->data)
                {
                    std::cout << "right" << std::endl;
                    parentNode->left = node;
                    rightRotate(root);
                }
                else
                {
                    std::cout << "left" << std::endl;
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
            int isDeletable(NodePtr found)
            {
                if (found->left && found->right && !found->left->left && !found->left->right && !found->right->left && !found->right->right)
                    {
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->right;
                            found->parent->right->left = found->left;
                        }
                        else
                        {
                            found->parent->left = found->right;
                            found->parent->left->left = found->left;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    else if (found->left && !found->right)
                    {
                        if (found == found->parent->right)
                            found->parent->right = found->left;
                        else
                            found->parent->left = found->left;
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    else if (found->right && !found->left)
                    {
                        if (found == found->parent->right)
                            found->parent->right = found->right;
                        else
                            found->parent->left = found->right;
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        return 1;
                    }
                    return 0;
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
                Key compare = root->data;
                if (key < compare)
                {
                    while (root->right && !isDeletable(found))
                    {
                        std::cout << "rotate left" << std::endl;
                        leftRotate(root);
                        prettyPrint();
                    }
                   /* std::cout << "found right" << found->right << std::endl;
                    std::cout << "found : " << found->data << std::endl;
                    std::cout << "found parent : " << found->parent->data << std::endl;
                    std::cout << "*******************" << std::endl;
                    if (found == found->parent->right)
                        found->parent->right = found->left;
                    else
                        found->parent->left = found->left;
                    if (found->left)
                        found->left->parent = found->parent;
                    initializeNode(found);
                    delete found;
                    found = NULL;*/
                    recolor(root);
                }
                else if (key > compare)
                {
                    while (root->left && !isDeletable(found))
                    {
                        std::cout << "rotate right" << std::endl;
                        rightRotate(root);
                        prettyPrint();
                    }
                    /*std::cout << "found left" << found->left << std::endl;
                    std::cout << "found : " << found->data << std::endl;
                    std::cout << "found parent : " << found->parent->data << std::endl;
                    std::cout << "*******************" << std::endl;
                    if (found == found->parent->right)
                        found->parent->right = found->right;
                    else
                        found->parent->left = found->right;
                    if (found->right)
                        found->right->parent = found->parent;
                    initializeNode(found);
                    delete found;
                    found = NULL;*/
                    recolor(root);
                }
                else
                {
                    std::cout << "found : " << found->data << std::endl;
                    prettyPrint();
                    std::cout << "*******************" << std::endl;
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