#include <iostream> //cin and cout
#include "bst.hpp"

using namespace ENSC251_Lab3;

void input_error();
int userInputForKey();
bool checkValidPointer(ENSC251_Lab3::NodePtr testPointer);
void printFamily(ENSC251_Lab3::NodePtr inPointer, ENSC251_Lab3::BinarySearchTree *bst);

int main() {

	ENSC251_Lab3::BinarySearchTree bst1;	//creating tree bst1

	bst1.insertNode(10);	//inserting values(nodes) into tree 
	bst1.insertNode(5);
    bst1.insertNode(15);
	bst1.insertNode(3);
    bst1.insertNode(7);
	bst1.insertNode(13);
    bst1.insertNode(18);
	bst1.insertNode(4);
    bst1.insertNode(6);
	bst1.insertNode(9);
	bst1.insertNode(8);
	bst1.insertNode(16);
    bst1.insertNode(19);
	bst1.insertNode(17);
	std::cout << "Binary Search Tree 1:\n" << bst1;		//print out bst1 using overloaded operator to 

	ENSC251_Lab3::BinarySearchTree bst2, bst3; 			//creating tree bst2 and bst3
	
	//bst3 = bst2 = bst1; doesn't work like this
	bst2 = bst1;
	bst3 = bst1;


	std::cout << "Binary Search Tree 2:\n" << bst2;		//print out bst2 and bst3
	std::cout << "Binary Search Tree 3:\n" << bst3;

	ENSC251_Lab3::BinarySearchTree bst4(bst3); 			//copy constructor to create bst4
	std::cout << "Binary Search Tree 4:\n" << bst4;		//print out bst4

	std::cout << "Deleting Nodes...\n\n\n";				//Deleting nodes from trees
	bst1.deleteNode(4); //no child
	bst1.deleteNode(9);	//single left child

	bst2.deleteNode(10); //top node (two children)

	bst3.deleteNode(3); //single right child
	bst3.deleteNode(9); //single left child
	bst3.deleteNode(16); //single right child

	bst4.deleteNode(18); //two children, successor has no child
	bst4.deleteNode(7);	 //two children, successor has no child
	bst4.deleteNode(10); //top node

	std::cout << "Nodes deleted. Here are the new trees:\n\n";
	std::cout << "Binary Search Tree 1:\n" << bst1;		//Printing out new tree from deleted node
	std::cout << "Binary Search Tree 2:\n" << bst2;
	std::cout << "Binary Search Tree 3:\n" << bst3;
	std::cout << "Binary Search Tree 4:\n" << bst4;



	std::cout << "\n\n\n\n\nPart 2:\nPlease enter your choice:\n\n";   //user prompts
	while (1) {
        int user_input;      //menu system. Printed out to user everytime after an option is selected and executed
            std::cout << "\n\n[1] search a key in bst4\n"
            "[2] Search the successor node of a key in bst4\n"
            "[3] Insert a key into bst4\n"
            "[4] Delete a key from bst4\n"
            "[5] Print out bst4\n"
            "[6] Exit the program\n\n"
            "Enter choice: ";

        std::cin >> user_input;      //store user input for use in switch statement
        std::cin.clear();            //clear buffer regardless of user input, since this is in a loop,   
        std::cin.ignore(1000, '\n'); //and error checking is done by the switch statement, this functions as input validation
        std::cout << std::endl;

        switch (user_input)     //determines user input and executes corresponding code
        {
        case 1: //search family printout
		{
			//startCase1:
			int TempKey;
			ENSC251_Lab3::NodePtr TempPtr;		//creating temp and temp Node pointers

			TempKey = userInputForKey();					//get user inputted key to search for
			TempPtr = bst4.searchNode(TempKey);	//getting the pointer associated with the key
			if (checkValidPointer(TempPtr)){
				printFamily(TempPtr, &bst4);			//print out the family function if pointer is valid
				TempPtr = NULL;					//pointer cleanup, don't ever delete this pointer
				continue;						//continues to outer loop
			}
			std::cout << "\n\n Warning: The inputted key does not exist, please try again\n";
			TempPtr = NULL;			//pointer cleanup, don't ever delete this pointer
			break;

		}
        case 2: //successor family printout
		{
			int TempKey;
			ENSC251_Lab3::NodePtr TempPtr;

			TempKey = userInputForKey();							//ge user inputted key to search for
			TempPtr = bst4.searchSuccessor(TempKey);	//returns pointer to successor, has own error messages
			if (checkValidPointer(TempPtr)){
				printFamily(TempPtr, &bst4);				//print out the family function if pointer is valid
					TempPtr = NULL;					//pointer cleanup, don't ever delete this pointer
					continue;						//continues to outer loop
			}
			TempPtr = NULL;
			break;							//continues to outer loop
		}
		case 3: //insert key into bst4
		{
			int TempKey;
			TempKey = userInputForKey();
			bst4.insertNode(TempKey);
			std::cout << "Here is the new tree: ";
			std::cout << bst4;
			continue;
		}
        case 4: //delete key from bst4
		{
			int TempKey;
			TempKey = userInputForKey();
			bst4.deleteNode(TempKey);
			std::cout << "Here is the new tree: ";
			std::cout << bst4;
			break;
		}
        case 5: //print out bst4
		{
			std::cout << bst4;
			break;
		}
        case 6: //exit program
			std::cout << "\n\nExiting Program...\n\n";
			return 0;
			break;
        default:
			std::cout << "\nError: Invalid entry, please enter a number between 1 and 6\n";    //outputs error message for user
            break;
        }//end of switch statement
	}//end of while loop

	return 0;
}

void input_error()
{
	std::cout << "\n\ninvalid entry, please follow the prompt and try again\n";
	std::cin.clear();
	std::cin.ignore(1000, '\n');
}

int userInputForKey()
{
	int TempKey;

	std::cout << "Please enter the key as a number \nEnter key: "; //function this
	std::cin >> TempKey;
	while (std::cin.fail()) {
		input_error();
		std::cin >> TempKey;
	}
	return TempKey;
}

bool checkValidPointer(ENSC251_Lab3::NodePtr testPointer) {			//checks if a pointer points to null, returns 0 if it points to NULL, returns 1 otherwise
	if (testPointer == NULL) {
		return 0;
	}
	return 1;
}

void printFamily(ENSC251_Lab3::NodePtr inPointer, ENSC251_Lab3::BinarySearchTree* bst) {			//prints out the family information for the key
	std::cout << "Pointer Family Information:\n";
	std::cout << "Key value: " << bst->getNodeKey(inPointer) << std::endl;		//get node key
	if (inPointer->parent != NULL) {
		std::cout << "Parent Key value: " << bst->getParentKey(inPointer) << std::endl;	//get parent key
	}
	if (inPointer->left != NULL) {
		std::cout << "Left Child value: " << bst->getLeftKey(inPointer) << std::endl;		//get left key
	}
	if (inPointer->right != NULL) {
		std::cout << "Right Child value: " << bst->getRightKey(inPointer) << std::endl;	//get right key
	}
}