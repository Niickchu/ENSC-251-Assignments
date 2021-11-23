#include "stack.hpp"
#include <iostream>
#include <string>

//function to determine if a line is all whitespace or empty
bool isBlankLine(std::string const& input);

int main(){

    Stack<int> sint1; //creating sint1 object
    sint1.push(1);    //pushing values into sint1
    sint1.push(2);    
    sint1.push(3);
    sint1.push(4);
    sint1.push(5);
    sint1.push(6);

    Stack<int> sint2;   //creating sint2 object
    sint2 = sint1;      //using = operator for creating sint 2

    sint1.reverse();       //reversing and printing sint1
    std::cout << "sint1\n-----";
    printStack(sint1);

    printf("%s", KNRM);     //printing sint2
    std::cout << "\n\nsint2\n-----";
    printStack(sint2);

    Stack<double> sdouble1; //creating sdouble1 object
    
    sdouble1.push(1.5);     //pushing values into sdouble1
    sdouble1.push(2.5);
    sdouble1.push(3.5);
    sdouble1.push(4.5);
    sdouble1.push(5.5);
    sdouble1.push(6.5);

    printf("%s", KNRM);     //printing sdouble1
    std::cout << "\n\nsdouble1\n--------";
    printStack(sdouble1);

    Stack<double> sdouble2(sdouble1);   //using copy constructor to assign values to sdouble2
    sdouble2.reverse();                 //reversing sdouble2

    printf("%s", KNRM);                 //priting top of sdouble2
    std::cout << "\n\nsdouble2 top\n------------\n";
    printf("%s", KBLU);
    std::cout << sdouble2.peek()->data;


    std::string userInput;
   
    while (1) {             //user input loop
        printf("%s", KNRM);
        std::cout << "\n\n\n\nEnter a string: ";
        printf("%s", KCYN);
        std::getline(std::cin, userInput);

        if (isBlankLine(userInput)) { std::cout << "Nothing was inputted, please try again"; }  //check if user inputted only blankspace or only hit enter
        else break;
    }

    Stack<char> palindrome;         //creating the palindrome object
    for (int i = 0; i < userInput.size(); i++)
    {
        palindrome.push(userInput[i]);  //pushing userinput into palindrome
    }
    
    printf("%s", KNRM);         //printing out the palindrome
    std::cout << std::endl << "\n\nHere is the palindrome\n----------------------\n";
    printf("%s", KCYN);
    std::cout << userInput;     //first print out the userinput

    printInline(palindrome);    //then print out the palindrome object, should be the reverse of userInput string, since input is pushed to the top

    // StackFrame<char>* node = palindrome.peek();
    // while (node != NULL)
    // {
    //     std::cout << node->data;
    //     node = node->link;
    // }
    std::cout << std::endl;
    printf("%s", KNRM);

    return 0;
}

//function to determine if a line is all whitespace or empty
bool isBlankLine(std::string const& input)
{
    auto temp = input.c_str();  //return pointer to c style string
    for (temp; *temp; ++temp)   //loop through new string
    {
        if (!isspace(*temp)) return false;  //return false if not a blankline
    }
    return true;    //return true if it is a blank line
}
