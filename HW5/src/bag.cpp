#include "bag.h"
template <class T>
void Bag<T>::message(const T& a) {
    cout << "Pop"<< " " << a << " "
         << "from " << name<<endl;
}
template <class T>
T* Bag<T>::Pop(T& a) {
    if (IsEmpty()) {
        Empty();
        return 0;
    }
    int delpos = top / 2;
    a = array[delpos];
    message(a);
    for (int i = delpos; i < top; i++) {
        array[i] = array[i + 1];
    }
    top--;
    return &a;
}
template <class T>
void Bag<T>::Push(const T& a) {
    if (IsFull()) {
        Full(a);
    } else {
        array[top] = a;
        top++;
    }
}
template<class T>
bool Bag<T>::IsFull() const {
    return top == MaxSize;
}
template<class T>
bool Bag<T>::IsEmpty() const {
    return top == 0;
}
template<class T>
int Bag<T>::Size() const{
    return top;
}
