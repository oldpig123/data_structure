#ifndef STACK_H_
#define STACK_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
#define DefaultSize 20

void StackEmpty();
template <typename T>
class Stack {
   public:
    Stack(int MaxStackSize = DefaultSize){

        // stack.resize(MaxSize);
    };
    Stack(Stack& src) {
        MaxSize = src.MaxSize;
        stack = src.stack;
    }
    ~Stack(){

    };
    // Create an empty Stack whose maximum size is MaxStackSize
    bool IsFull(){

    };
    // if number of elements in the Stack is equal to the maximum size of
    // the Stack, return TRUE(1); otherwise, return FALSE(0)
    void Push(const T& item) {
        stack.push_back(item);
    };
    // if IsFull(), then StackFull(); else insert item at rear of the Stack
    bool IsEmpty() {
        return stack.empty();
    };
    // if number of elements in the Stack is equal to 0, return TRUE(1)
    // else return FALSE(0)
    T* Delete(T& a) {
        if (IsEmpty()) {
            StackEmpty();
            return 0;
        }

        a = stack.back();
        stack.pop_back();
        return &a;
    };
    T Delete() {
        T a;
        if (IsEmpty()) {
            StackEmpty();
            return a;
        }

        a = stack.back();
        stack.pop_back();
        return a;
    };
    // if IsEmpty(), then StackEmpty() and return 0;
    // else remove the item at the front of the Stack and return a pointer to it
    void StackFull(){};
    T* Top(T& a) {
        if (IsEmpty()) {
            StackEmpty();
            return 0;
        }
        a = stack.back();
        return &a;
    };
    T Top() {
        T a;
        if (IsEmpty()) {
            StackEmpty();
            return a;
        }
        a = stack.back();
        return a;
    };
    template <typename U>
    friend ostream& operator<<(ostream& os, const Stack<U>& s);

   private:
    vector<T> stack;  // top: index of the topmost element to be retrieved
    // T* stack;
    //  T array pointer
    int MaxSize;
};

template <typename U>
ostream& operator<<(ostream& os, const Stack<U>& s) {
    if (s.stack.empty()) {
        os << "stack is empty" << endl;
    } else {
        for (auto i = s.stack.begin(); i != s.stack.end(); i++) {
            os << " " << *i << " ";
        }
    }

    return os;
};
#endif
