#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include "List.h"
//#include "Stack.h"
#include "Queue.h"

extern int debug;
extern const int width;
extern int N;
using namespace std;

template<class T> class List;
//template<class T> class Stack;
template<class T> class Queue;
//template<class U> class Tree;
//*****  Node Template Class 
template <class T>
class Node {
	//friend class List <T>;
	//friend class Stack <T>;
	friend class Queue <T>;
//	friend class Tree<T>;
	friend ostream &operator<<(ostream &, List<T>&);
public:
	T GetData() { return data; };
	Node <T>* GetLink() { return link; };
	Node() { av_init(); };
	Node(T element, Node<T>* l = NULL) {
		data = element; 
		link = l;
	};
	void* operator new(size_t size) {
		void* p;
		if (avv->first == NULL)	 Node();   
		// if (!avv->num) Node();
		p = avv->Pop();
		if (debug)	cout << "#AVnodes = " << right << setw(width) << avv->num << ", ";
		return p;
	};

	void operator delete(void* p) {
		Node<T>* t = (Node<T>*) p;
		avv->InsertBack(t);
		if (debug) cout << "#AVnodes = " << right << setw(width) << avv->num << ", ";
	};
	void av_init();
	static List<T> *avv;
public:
	T data;
	Node<T> *link;
};

// **********Initialize the avv pointer ********
template <class T> 
List<T> * Node<T>::avv = new List<T>;

// initialize the available list with N nodes
template<class T>
void Node<T>::av_init() {
	if (avv->first == NULL) {
		Node<T>* t = (Node<T>*) malloc(sizeof(Node<T>));
		avv->InsertBack(t);
		for (int i = 0; i < N - 1; i++) {
			avv->last = avv->last->link = (Node <T>*) malloc(sizeof(Node<T>));
			avv->num++;
		};
		avv->last->link = NULL;
	}
	//	link = 0;
	if (debug) cout << "Initial #AVnodes =" << N << ",\n";
};


#endif