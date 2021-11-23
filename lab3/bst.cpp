//bst.cpp to implement your class
#include "bst.hpp"
#include <iostream>
#include <ostream>
#include <vector>
struct nodeData // a struct used in some functions to be able to compile infor of the nodes in a bst
{
    int value; // eg. key
    int level; // how far down the node is on the tree
    int parent; // the key of the parent
};


ENSC251_Lab3::NodePtr ENSC251_Lab3::BinarySearchTree::returnRightmost(ENSC251_Lab3::NodePtr Step)
{
    if (Step->right == NULL)      //once there is no more left most nodes, return pointer
    {
        return Step;
    }
    else {
        returnLeftmost(Step->right); //keep recursively finding the left most node
    }
}
ENSC251_Lab3::NodePtr ENSC251_Lab3::BinarySearchTree::returnLeftmost(ENSC251_Lab3::NodePtr Step) {
    if (Step->left == NULL)      //once there is no more left most nodes, return pointer
    {
        return Step;
    }
    else {
        returnLeftmost(Step->left); //keep recursively finding the left most node
    }
}
void compile_nodes(ENSC251_Lab3::NodePtr start_node, int start_level, std::vector<nodeData>& data);
ENSC251_Lab3::NodePtr delete_node_func(ENSC251_Lab3::NodePtr root, int key);
ENSC251_Lab3::NodePtr find_node(ENSC251_Lab3::NodePtr start_node, int key);

ENSC251_Lab3::NodePtr min_val(ENSC251_Lab3::NodePtr node) // the smallest value in a bst is the leftmost node
{
    ENSC251_Lab3::NodePtr minval = node;

    while (minval->left != NULL) {
        minval = minval->left;
    }
    return minval;
}

ENSC251_Lab3::NodePtr inOrderSuccessor( // an in order traversal used to find the successor of a node
    ENSC251_Lab3::NodePtr root,
    ENSC251_Lab3::NodePtr node)
{
    if (node->right != NULL) 
        return min_val(node->right);
 
    ENSC251_Lab3::NodePtr parent_node = node->parent;
    while (parent_node != NULL && node == parent_node->right) {
        node = parent_node;
        parent_node = parent_node->parent;
    }
    return parent_node;
}

ENSC251_Lab3::BinarySearchTree::BinarySearchTree() {
    
    root->parent = nullptr;
    root->left = nullptr; // assign the pointers in the node to be nullptr values, but assign the root -1 as a placeholder to check (since bst node keys cant be negative anyways)
    root->right = nullptr;
    root->key = -1;
}

ENSC251_Lab3::BinarySearchTree::BinarySearchTree(ENSC251_Lab3::BinarySearchTree & in_tree){
    root->parent = nullptr;
    root->left = nullptr; // assign the pointers in the node to be nullptr values, but assign the root -1 as a placeholder to check (since bst node keys cant be negative anyways)
    root->right = nullptr;
    root->key = -1;

    std::vector<nodeData> temp_data;
    compile_nodes(in_tree.root, -1, temp_data); // compile the original node data into a vector
    int max_level = 0;
    for (auto i : temp_data) {

        if (i.level > max_level) {
            max_level = i.level;
        }
    }
    for (int i = 0; i < max_level + 1; i++) { // add the compiled node keys into the new bst in order of their levels
        for (auto j : temp_data) {
            if (j.level == i) {
                    this->insertNode(j.value);
                }
            }
        }

}

ENSC251_Lab3::NodePtr insertion(int in_key, ENSC251_Lab3::NodePtr node);

bool ENSC251_Lab3::BinarySearchTree::insertNode(int in_key) {
    if (this->root->key == -1) { //first to check if the tree is empty, if it is simply assign the root the key
        this->root->key = in_key;
        return true;
    }
    root = insertion(in_key, root); // call the insertion function to be able to insert a node resursively
    return true;
}

ENSC251_Lab3::NodePtr insertion(int in_key, ENSC251_Lab3::NodePtr node) {

    if (node == NULL) //if a pointer to next node DNE, create the node there                                                        //what does node == NULL mean
    {
        node = new ENSC251_Lab3::Node; 
        node->key = in_key;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;                                                                                                        //why is the node parent null?
    }
    else if (node->key < in_key) //if inputted value is greater than the root key, go right and create link. Recursive
    {
        node->right = insertion(in_key, node->right);  //pointer to right subtree is = recursion until NULL
        node->right->parent = node; //creates link

    }
    else if (node->key > in_key) //if inputted value is less than the root key, go left and create link. Recursive
    {
        node->left = insertion(in_key, node->left);    //pointer to left subtree = recursion until NULL
        node->left->parent = node;
    }
    return node;
}

ENSC251_Lab3::NodePtr ENSC251_Lab3::BinarySearchTree::searchNode(int key) {

    NodePtr returned_node; //define a node pointer to the found node, this is returned

    returned_node = find_node(root, key); //pass in root (start_node), and the key we want to search for

    return returned_node;
}

ENSC251_Lab3::NodePtr find_node(ENSC251_Lab3::NodePtr start_node, int key) {


    if (start_node == NULL || start_node->key == key) { //if pointer to root == NULL, or the passed in value is the node
                                                        //return the start node (since this must be the searched for node)
        return start_node;
    }
    if (start_node->key < key) {
        return find_node(start_node->right, key);       //recursion here
    }

    return find_node(start_node->left, key);            //recursion here

    //return NULL if not found

}

void compile_nodes(ENSC251_Lab3::NodePtr start_node, int start_level, std::vector<nodeData>& data) { // a function that alters a passed in vector to contain info on all the nodes in a tree
    if (start_level == -1) { // an arbitrary number to check for in order to catch the root node's appropriate level
        nodeData temp_data;
        temp_data.value = start_node->key;
        temp_data.parent = 0;
        temp_data.level = 0;
        data.push_back(temp_data);
        start_level = start_level + 1;
    }
    if (start_node == NULL) {
        return;
    }
    if (start_node->left != nullptr) { // add the nodes left child's info if it exists
        nodeData temp_data;
        temp_data.value = start_node->left->key;
        temp_data.parent = (start_node->left->parent->key * -1);
        temp_data.level = start_level + 1;
        data.push_back(temp_data);
        compile_nodes(start_node->left, start_level + 1, data);
    }
    if (start_node->right != NULL) { // add the node's right child's info if it exists
        nodeData temp_data;
        temp_data.value = start_node->right->key;
        temp_data.parent = start_node->right->parent->key;
        temp_data.level = start_level + 1;
        data.push_back(temp_data);
        compile_nodes(start_node->right, start_level + 1, data);
    }
    return;
}

std::ostream& ENSC251_Lab3::operator <<(std::ostream& os, ENSC251_Lab3::BinarySearchTree& bst) { // overload << operator to print out a trees information

    std::vector<nodeData> node_data;
    compile_nodes(bst.root, -1, node_data); // uses the comile nodes function to make a vector of the node info 

    int max_level = 0;

    for (auto i : node_data) { // loop through the node data in order to find the max level

        if (i.level > max_level) {
            max_level = i.level;
        }
    }


    for (int i = 0; i < max_level + 1; i++) { // loop through the vector again but only printing information of the nodes in a order based on the level (lowest to greatest)
        os << "Level " << i << ":     ";
        for (auto j : node_data) {
            if (j.level == i) {

                if (j.level != 0) {

                    if (j.parent < 0) {
                        os << j.value << "-" << "(Left Child of: " << (j.parent * -1) << "), ";
                    }
                    else {
                        os << j.value << "-" << "(Right Child of: " << j.parent << "), ";
                    }
                }
                else { os << j.value << "-" << "Root Node"; }
            }
        }
        os << '\n';
    }

    return os;

}


bool ENSC251_Lab3::BinarySearchTree::deleteNode(int key) {
    
    //search for the node to be deleted
        NodePtr returnP = searchNode(key);	//returns copy of pointer to the searched node, returnP is a pointer to the to be deleted node
        if (returnP == NULL)
        {
            std::cout << "Number " << key << " does not exist in the tree";
            return false;
        }
        //Case 1: if searched node has no children
        if ((returnP->left == NULL) && (returnP->right == NULL))
            if (returnP->parent->left == returnP)		//if returnP is in left branch, delete left node pointer of parent, set = NULL             
                {                 
                NodePtr toParentP;
                toParentP = returnP->parent;

                delete returnP->parent->left;
                toParentP->left = NULL;
                returnP = NULL;
                return true;
                }

            else{						//if returnP is in right branch, delete right node pointer of parent, set = NULL
                NodePtr toParentP;
                toParentP = returnP->parent;

                delete returnP->parent->right;
                toParentP->right = NULL;
                returnP = NULL;
                return true;
                }
        //case 3: if searched node has two children
        else if ((returnP->left != NULL) && (returnP->right != NULL))//if both children exist
        {
        NodePtr successorP = searchSuccessor(key); //find successor to value to be deleted, (this is the min value on the right)
        int temp_key = successorP->key;
        NodePtr temp_ptr = searchNode(key);

        temp_ptr->key = -2;

        deleteNode(temp_key);

        temp_ptr->key = temp_key;
        

        }
    //Case 2a: if searched node has a single child: left child
    else if ((returnP->left != NULL) && (returnP->right == NULL)) //if returnP->left isn't NULL aka Left child exists
    {
        BinarySearchTree temp_tree(*this);
        NodePtr temp_ptr = this->searchNode(key);
        int temp_key = temp_ptr->left->key;
        temp_ptr->key = temp_key;
        temp_ptr->left = nullptr;

        return true;
    }

    //Case 2b:if searched node has right child
    else if ((returnP->left == NULL) && (returnP->right != NULL)) //if only right child exists
    {
        BinarySearchTree temp_tree(*this);
        NodePtr temp_ptr = this->searchNode(key);
        int temp_key = temp_ptr->right->key;
        temp_ptr->key = temp_key;
        temp_ptr->left = nullptr;
        
        return true;
    }
}

ENSC251_Lab3::NodePtr returnLeftmost(ENSC251_Lab3::NodePtr Step)
{
    if (Step->left == NULL)      //once there is no more left most nodes, return pointer
    {
        return Step;
    }
    else {
        returnLeftmost(Step->left); //keep recursively finding the left most node
    }
    return NULL; //not needed
}

ENSC251_Lab3::NodePtr ENSC251_Lab3::BinarySearchTree::searchSuccessor(int key)
{

    return inOrderSuccessor(root, searchNode(key)); // calls the inOrderSuccessor function to be able to fund the successor recursively

}



void ENSC251_Lab3::BinarySearchTree::operator=(const ENSC251_Lab3::BinarySearchTree & to_copy){ // overloaded assignment operator to be able to assign a bst the same values as another
    std::vector<nodeData> temp_data;
    compile_nodes(to_copy.root, -1, temp_data); // compile the node data into a vector
    int max_level = 0;
    for (auto i : temp_data) {

        if (i.level > max_level) {
            max_level = i.level;
        }
    }
    for (int i = 0; i < max_level + 1; i++) { // add the compiled node keys into the new bst in order of their levels
        for (auto j : temp_data) {
            if (j.level == i) {
                    this->insertNode(j.value);
                }
            }
        }
    }

int ENSC251_Lab3::BinarySearchTree::getNodeKey(NodePtr node) 
{
    return node->key;
}

int ENSC251_Lab3::BinarySearchTree::getParentKey(NodePtr node)
{
    return node->parent->key;
}

int ENSC251_Lab3::BinarySearchTree::getLeftKey(NodePtr node) 
{
    return node->left->key;
}

int ENSC251_Lab3::BinarySearchTree::getRightKey(NodePtr node) 
{
    return node->right->key;
}



ENSC251_Lab3::NodePtr ENSC251_Lab3::BinarySearchTree::searchSuccessor_orig(int key)  //search successor of this key
{
    NodePtr returnP = searchNode(key);
    NodePtr LargestP = returnRightmost(returnP);
    if (returnP == NULL)                //if key doesn't exist
    {
        std::cout << "Warning: Key does not exist " << std::endl;
        return NULL;
    }

    else if(returnP == LargestP) 
    {
        std::cout << "Warning: Inputted key is largest in current tree " << std::endl;
        return NULL;
    }

    else {  //If the key does exist
        if (returnP->right != NULL) {       //If right pointer exists, go right once
            return returnLeftmost(returnP->right);  //into recursive left most function
        }
        else {
            std::cout << "Successor does not exist\n";  //if theres no node to the right of the key, there is no successor
            return NULL;
        }
    }
}