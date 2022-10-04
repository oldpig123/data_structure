#include "stack.h"

template<class T>
T* Stack<T>::Pop(T& a){
    if (Bag<T>::IsEmpty())
    {
        Bag<T>::Empty();
        return 0;
    }
    Bag<T>::top--;
    a = Bag<T>::array[Bag<T>::top];
    Bag<T>::message(a);
    return &a;
}