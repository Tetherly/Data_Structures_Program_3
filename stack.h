// Created by Tyler Starling on 6/15/2021.
// COP 4530
// Header file for the stack class

#ifndef COP4530_PROGRAM_3_STACK_H
#define COP4530_PROGRAM_3_STACK_H
#include <iostream>
#include <vector>

namespace cop4530{

    template <typename T>
    class Stack {
        protected:
            std::vector<T> c; //  list container used for underlying Stack class
        public:
            Stack();    //  default constructor
            ~Stack();   //  destructor
            Stack(const Stack<T>& s); //  copy constructor
            Stack(Stack<T>&& s);  //  move constructor
            Stack<T>& operator=(const Stack<T>& s);   //  copy assignment operator=
            Stack<T>& operator=(Stack<T>&& s);    //  move assignment operator=
            bool empty() const; //  returns true if the stack is empty, false otherwise
            void clear();    //  deletes all elements from the stack
            void push(const T& x);  //  copy version for pushing x onto the stack
            void push(T && x);   //  move version for pushing x onto the stack
            void pop(); //  removes the most recently added element of the stack
            T& top();   //  returns a reference to the most recently added element of the stack
            const T& top() const;   //  returns the most recently added element of the stack as a const reference
            int size() const;   //  returns the number of elements stored on the stack
            void print(std::ostream& os, char ofc=' ') const;    //  prints elements of the stack to ostream os with ofc as delimiter
    };

        //  non-member functions
        template <typename T>
        std::ostream& operator<<(std::ostream& os, const Stack<T>& a);  //  invokes the print() function to print the Stack<T> in the specified ostream

        template <typename T>
        bool operator==(const Stack<T>& a, const Stack<T>& b);  //  returns true if the two compared Stacks have the same elements, in the same order, and false otherwise

        template <typename T>
        bool operator!=(const Stack<T>& a, const Stack<T>& b);  //  opposite of operator==()

        template <typename T>
        bool operator<=(const Stack<T>& a, const Stack<T>& b);  //  returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b

    #include "stack.hpp"
}
#endif //COP4530_PROGRAM_3_STACK_H
