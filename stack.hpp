// Created by Tyler Starling on 6/15/2021.
// COP 4530
// Source file for the stack class

#include <iostream>
#include <vector>
#include "stack.h"


using namespace std;
using namespace cop4530;

//  Default Constructor
template <typename T>
Stack<T>::Stack() {
}
//  Destructor for Stack Class.
template <typename T>
Stack<T>::~Stack(){
    c.clear();
}
//  Copy Constructor for Stack Class.
template <typename T>
Stack<T>::Stack(const Stack<T>& s){
    for(int i = 0; i < s.c.size(); i++){
        c.push_back(s.c.at(i));
    }
}
//  Move Constructor for Stack Class.
template <typename T>
Stack <T>::Stack(Stack<T>&& s){
    for(int i = 0; i < s.c.size(); i++){
        c.push_back(s.c.at(i));
    }
    s.c.clear();
}
//  Copy Assignment Operator= for Stack Class.
template <typename T>
Stack<T>& Stack <T>::operator=(const Stack<T>& s){
    Stack<T> copy = s;
    swap(*this, copy);
    return *this;
}
//  Move Assignment Operator= for Stack Class.
template <typename T>
Stack<T>& Stack <T>::operator=(Stack<T>&& s){
    swap(c, s.c);
    return *this;
}
//  Empty Function that determines whether or not a Stack contains elements.
template <typename T>
bool Stack <T>::empty() const{
    return c.empty();
}
//  Deletes all elements from the stack.
template <typename T>
void Stack <T>::clear(){
    c.clear();
}
//  Adds x to the Stack. Copy Version.
template <typename T>
void Stack <T>::push(const T &x){
    c.push_back(x);
}
//  Adds x to the Stack. Move Version.
template <typename T>
void Stack <T>::push(T&& x){
    c.push_back(x);
}
//  Removes the most recently added element of the Stack.
template <typename T>
void Stack <T>::pop(){
    c.pop_back();
}
//  Returns a reference to the most recently added element of the Stack.
template <typename T>
T& Stack <T>::top(){
    return c.back();
}
//  Returns the most recently added element of the Stack as a const reference.
template <typename T>
const T& Stack <T>::top() const{
    return c.back();
}
//  Returns the number of elements stored in the Stack.
template <typename T>
int Stack <T>::size() const{
    return c.size();
}
//  Prints the elements of the Stack to the ostream os; ofc is a delimiter for separation between elements.
template <typename T>
void Stack <T>::print(ostream& os, char ofc) const{
    for(int i = 0; i < c.size(); i++){
        os << c[i] << ofc;
    }
}

/******** Non-Member Functions ********/

//  Invokes the print() function to print the Stack<T> a in the specified ostream.
template <typename T>
ostream& operator<<(ostream& os, const Stack<T>& a){
    a.print(os);
    return os;
}
//  Returns true if the two compared Stacks have the same elements, in the same order, false otherwise.
template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b){
    Stack<T> copyCat = a;
    Stack<T> copyCatTwo = b;
    if(copyCat.size() == copyCatTwo.size()){
        for(int i = 0; i < copyCat.size(); i++){
            if(copyCat.top() != copyCatTwo.top()){
                return false;
            }else{
                copyCat.pop();
                copyCatTwo.pop();
            }
        }
        return true;
    }
    return false;
}
//  Opposite of operator==().
template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b){
    if(!(a == b)){
        return true;
    }
    return false;
}
//  Returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b.
template <typename T>
bool operator <=(const Stack<T>& a, const Stack<T>& b){
    Stack<T> copyCat = a;
    Stack<T> copyCatTwo = b;
    if(copyCat.size() <= copyCatTwo.size()){
        while(!(copyCat.empty())){
            if(copyCat.top() <= copyCatTwo.top()){
                copyCat.pop();
                copyCatTwo.pop();
            }else{
                return false;
            }
        }
        return true;
    }
    return false;
}