//header file bst.hpp to declare your class
#ifndef BST_HEADER
#define BST_HEADER


#include <iostream>
#include <ostream>

namespace ENSC251_Lab3 {

    struct Node {
        int key; // key value of the node
        struct Node* parent; // pointer to parent node
        struct Node* left; // pointer to left subtree
        struct Node* right; // pointer to right subtree
    };
    typedef struct Node* NodePtr;

    class BinarySearchTree {
    private:
        Node * root = new Node; //creates a pointer to tree, using NodePtr threw errors
    public:
        BinarySearchTree(); // default constructor
        BinarySearchTree(BinarySearchTree& in_tree); // constructor that assigns the new bst the values of the passed in one
        bool insertNode(int in_key); // inserts a node with the given key
        NodePtr searchNode(int key); // searches for a node and 
        bool deleteNode(int key); // deletes a node in a tree and takes into account its children
        NodePtr searchSuccessor(int key); // searches for an in order successor to the a node with the given key
        NodePtr searchSuccessor_orig(int key); // searches for an in order successor to the a node with the given key using a different method
        friend std::ostream& operator <<(std::ostream& os, BinarySearchTree& bst); // overloaded << operator to print out the info of a bst
        void operator=(const BinarySearchTree & to_copy); // overloaded assignment operator to assign a bst the values of another
        NodePtr returnRightmost(ENSC251_Lab3::NodePtr Step);
        NodePtr returnLeftmost(ENSC251_Lab3::NodePtr Step);
        int getNodeKey(NodePtr node);
        int getParentKey(NodePtr node);
        int getLeftKey(NodePtr node);
        int getRightKey(NodePtr node);
    };

}

#endif