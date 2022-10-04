
#ifndef QUEUE_H_
#define QUEUE_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
#define DefaultQSize 20
extern void QueueEmpty();
template <typename T>
class Queue {
    template<typename U>
    friend ostream& operator<<(ostream& os, const Queue<U>& t){
        for (auto i = t.queue.begin(); i != t.queue.end(); i++)
        {
            os << *i<<" ";
        }
        return os;
    };
   public:
    Queue<T>& operator=(const Queue<T>& rhs) {
        front = rhs.front;
        rear = rhs.rear;
        MaxSize = rhs.MaxSize;
        top = rhs.top;
        queue = rhs.queue;
        return *this;
    };
    Queue(int MaxQueueSize = DefaultQSize);
    Queue(const Queue&);
    ~Queue();
    void QueueFull(){};
    bool IsFull() { return 0; };
    void Push(const T& item) {
        queue.push_back(item);
    };
    vector<T> dump(){
        vector<T> temp;
        temp = queue;
        return temp;
    }
    bool IsEmpty();
    T* Delete(T& a) {
        if (IsEmpty()) {
            QueueEmpty();
            return 0;
        }

        vector<T> temp;
        a = queue.front();
        copy(queue.begin() + 1, queue.end(), temp.begin());
        queue = temp;
        return &a;
    };
    T* Pop(T& a) {
        if (IsEmpty()) {
            QueueEmpty();
            return 0;
        }
        vector<T> temp;
        a = queue.front();
        copy(queue.begin() + 1, queue.end(), temp.begin());
        queue = temp;
        return &a;
    };

   private:
    int front;        // front: index of the first element to be retrieved
    int rear;         // rear:index of the last element
    vector<T> queue;  // T array
    int MaxSize;
    int top;
};

template <class T>
Queue<T>::Queue(int MaxQueueSize) : MaxSize(MaxQueueSize) {
    //for (int i = 0; i < MaxSize; i++) queue.push_back(-1);
    front = rear = -1;
    top = 0;
}

// copy constructor
template <class T>
Queue<T>::Queue(const Queue& rhs) {
    front = rhs.front;
    rear = rhs.rear;
    MaxSize = rhs.MaxSize;
    top = rhs.top;
    queue = rhs.queue;
}

template <class T>
Queue<T>::~Queue() {
}

template <class T>
bool Queue<T>::IsEmpty() {
    return queue.empty();
}

#endif