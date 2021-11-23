#ifndef stack_hpp

#include <iostream>
#include <iomanip>
#include <stdio.h>

#define KNRM  "\x1B[0m" // ansi colour codes for colour output
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[90m"
#define KWHT  "\x1B[37m"


template <class type>
struct StackFrame
{
    type data;
    StackFrame *link;
};

template <class type>
using StackFramePtr = StackFrame<type>*;


template <class type>
class Stack
{
public:
    ~Stack() // deconstructor that pops the enitre stack. (pop calls delete)
    {
        type next;
        while (!empty())
        {
            next = pop();
        }
    }



    Stack<type> operator=(const Stack &orig_stack){ // operator overload that deep copies by pushing each
                                                    // value from the original stack to the bottom of the other
        StackFramePtr<type> temp_frame = orig_stack.top;
        while(temp_frame != nullptr){
            push_to_bottom(temp_frame->data);
            temp_frame = temp_frame->link;
        }
        return *this;
    }

    Stack(Stack &orig_stack){   // operator overload that deep copies by pushing each
                                // value from the original stack to the bottom of the other
        top = nullptr;
        StackFramePtr<type> temp_frame = orig_stack.top;
        while(temp_frame != nullptr){
            push_to_bottom(temp_frame->data);
            temp_frame = temp_frame->link;
        }
    }

    Stack() // default constructor that just assigns the top frame to null
    {
        top = nullptr;
    }

    bool empty() const // checks if the top frame exists (eg has been set)
    {
        return (top == nullptr);
    }

    StackFramePtr<type> peek() // simply returns the top frame if it exists
    {
        if (!empty())
            return top;
        else
            return nullptr;
    }

    void push(type the_symbol) // pushes an elemet by making it the new top frame and linking the rest 
    {                          // of the stack to it

        try
        {
            StackFrame<type> *temp_frame = new StackFrame<type>();
            temp_frame->data = the_symbol;
            temp_frame->link = top;
            top = temp_frame;
        }
        catch (const std::bad_alloc &) // catches the bad_alloc exception
        {
            exit(2);
        }

        
    }

    type pop() // pops the top element from the stack and deletes that pointer. then makes the new top, the old
    {          // top's link
        if (empty())
        {
            std::cout << "popping empty stack";
            exit(1);
        }

        type result = top->data;

        try
        {
            StackFramePtr<type> temp_frame;
            temp_frame = top;
            top = top->link;
            delete temp_frame;
        }
        catch (const std::bad_alloc &)
        {
            exit(2);
        }

        

        return result;
    }

    type reverse() // recursively reverses a stack by holding each value in the function call then talking
    {              // advantage of the other push_to_bottom function. Does so in O(n^2) time
        if (get_size() > 0)
        {
            type temp_symbol = top->data;
            pop();
            reverse();
            push_to_bottom(temp_symbol);
        }
        return 0;
    }

    int get_size() const // member function that uses the recursive get_stack_size function to find the size
    {                   // of the stack
        return get_stack_size(top, 0);
    }

    void push_to_bottom(type the_symbol) // pushes a symbol to the bottom of the stack using recursion
    {               
        if (get_size() == 0) // if the stack has a size of 0, add the desired element to the stack
        {
            push(the_symbol);
        }
        else
        {
            type temp_symbol = top->data;
            pop();
            push_to_bottom(the_symbol); // calls itself again to hold each item in the function call
            push(temp_symbol);  // push the element back into the stack after the base case is met
        }
    }

private:
    StackFramePtr<type> top;
};

template <class type>
void printInline(Stack<type> S){ // prints the stack by looping through the top node and stoping once it reaches
    StackFramePtr<type> node = S.peek();    // the end where the node will be null
    while (node != NULL)
    {
        std::cout << node->data;
        node = node->link;
    }
}

template <class type> // prints the stack by looping through the top node and stoping once it reaches
void printStack(Stack<type> S){ // the end where the node will be null
    std::cout << std::endl;

const char *longString = R""""(

 |
 V

)"""";
        StackFramePtr<type> temp_frame = S.peek();
        while(temp_frame != nullptr){
            printf("%s", KBLU);
            std::cout << std::setw(2);
            std::cout <<temp_frame->data;
            if(temp_frame->link != nullptr){
                printf("%s%s", KCYN, longString);
            }
            temp_frame = temp_frame->link;
        }
        std::cout << "\n";
        std::cout << std::endl;
    }

template <class type>
int get_stack_size(StackFramePtr<type> cur_frame, int current_size) // returns the size of a stack by incrementing the
{                                                                   // for each valid link between frames
    if (cur_frame == nullptr)
    {
        return current_size;
    }
    else
    {
        get_stack_size(cur_frame->link, current_size + 1);
    }
}
#endif