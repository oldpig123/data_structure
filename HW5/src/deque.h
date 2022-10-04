#ifndef DEQUEUE_H_
#define DEQUEUE_H_

#include "bag.h"

template <class T>
class Deque : public Bag<T> {
    template <class U>
    friend ostream& operator<<(ostream&, const Deque<U>&);

   public:
    Deque(int QueueSize) : Bag<T>::Bag(QueueSize) {
        front = 0;
        rear = 0;
        full = 0;
        strcpy(Bag<T>::name, "Deque");
    };
    ~Deque(){};
    T* Popf(T& a) {
        if (IsEmpty()) {
            Bag<T>::Empty();
            return 0;
        }

        a = Bag<T>::array[front];
        Bag<T>::message(a);
        front++;
        front = front % Bag<T>::MaxSize;
        full = false;
        return &a;
    };  // delete the element from queue
    void Pushr(const T& a) {
        if (IsFull()) {
            Bag<T>::Full(a);
            return;
        }
        Bag<T>::array[rear] = a;
        rear++;
        rear = rear % Bag<T>::MaxSize;
        full = (rear == front);
    };
    T* Popr(T& a) {
        if (IsEmpty()) {
            Bag<T>::Empty();
            return 0;
        }
        rear--;
        rear = (rear + Bag<T>::MaxSize) % Bag<T>::MaxSize;
        a = Bag<T>::array[rear];
        Bag<T>::message(a);
        full = false;
        return &a;
    };  // delete the element from queue
    void Pushf(const T& a) {
        if (IsFull()) {
            Bag<T>::Full(a);
            return;
        }
        if (IsEmpty()) {
            Bag<T>::array[front] = a;
            rear++;
            rear = rear % Bag<T>::MaxSize;
        } else {
            front--;
            front = (front + Bag<T>::MaxSize) % Bag<T>::MaxSize;
            Bag<T>::array[front] = a;
        }

        full = (rear == front);
    };

    bool IsEmpty() {
        return (front == rear && !full);
    };
    bool IsFull() {
        return (front == rear && full);
    };

   private:
    int rear, front;  // circular list implementation
    bool full;
};

template <class T>
ostream& operator<<(ostream& os, const Deque<T>& q) {
    os << " All Data in " << right << setw(6) << q.name << '[' << q.MaxSize << "] are: ";
    for (int i = 0; i < q.MaxSize; i++)
        os << "(" << i << ") " << q.array[i] << setw(3) << " ";

    os << "\n Valid data among them are: ";
    int i = q.front, j = 0;
    while (i != q.rear || j == 0) {
        j = 1;
        os << "(" << i << ") " << q.array[i] << setw(3) << " ";
        i++;
        i = i % q.MaxSize;
    }

    cout << "\n\n";
    return os;
};

#endif