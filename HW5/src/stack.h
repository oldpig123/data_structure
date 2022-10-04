#ifndef STACK_H_
#define STACK_H_

#include "bag.h"

template <class T>
class Stack:public Bag<T> {
  
public:
    Stack(int StackCapacity) :Bag<T>::Bag(StackCapacity) {
        strcpy(Bag<T>::name, "Stack");
    };
    ~Stack() {};
    T* Pop(T&); // delete the element from stack
};


#endif