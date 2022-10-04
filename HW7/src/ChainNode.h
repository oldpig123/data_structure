#ifndef CHAIN_NODE_H
#define CHAIN_NODE_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>

#include "ChainIterator.h"
extern int debug;
using namespace std;
// extern void *av;  // pointer to av list ChainNode<T>*
//  the static pointer avv points to this av.

template <class T>
class Chain;
template <class T>
class ChainIterator;  // new added from previos LinkedChain program
class Polynomial;
const int width = 2;
extern int N;

//*****  ChainNode Template Class
template <class T>
class ChainNode {
    friend class Polynomial;
    friend class Chain<T>;
    friend class ChainIterator<T>;  // new added for iterator
    friend istream &operator>>(istream &, Polynomial &);
    template <class U>
    friend ostream &operator<<(ostream &, Chain<U> &);

   public:
    T GetData() { return data; };
    ChainNode<T> *GetLink() { return link; };
    ChainNode() {
        av_init();
    };

    ChainNode(T element, ChainNode<T> *l = 0) : data(element), link(l){};
    static void av_init();
    void *operator new(size_t sz) {
        void *m = malloc(sz);
        if (debug) std::cout << "\nUser Defined :: Operator new_ChainNode" << std::endl;
        if (avv->first == NULL) {
            av_init();
        }
        m = avv->Pop();
        if (debug) cout << "->total AV nodes = " << avv->num << endl;

        return m;
    };
    void operator delete(void *m) {
        if (debug) std::cout << "\nUser Defined :: Operator delete_ChainNode" << std::endl;

        avv->InsertBack((ChainNode<T> *)m);
    };
    static Chain<T> *avv;

   private:
    T data;
    ChainNode<T> *link;
};

// **********Initialize the avv pointer ********
template <class T>
Chain<T> *ChainNode<T>::avv = new Chain<T>;

// initialize the available list with a coupld of nodes
template <class T>
void ChainNode<T>::av_init() {
    if (avv->first == NULL) {
        if (debug) {
            cout << "-> Initail Total AV Nodes = " << N << endl;
        }
        for (int i = 0; i < N; i++) {
            avv->InsertBack((ChainNode<T> *)malloc(sizeof(ChainNode<T>)));
        }
        avv->num = N;
    }
    // av = avv;
    //  initialized the available list
    //  do it by yourself
}

#endif