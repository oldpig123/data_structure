#ifndef TREE_H
#define TREE_H

#include <iostream>
//#include <queue>
#include <cmath>

#include "Queue.h"
#include "postfix.h"
#include "stack.h"
using namespace std;
template <class T>
class Tree;
template <class T>
class TreeNode;

template <class T>
class TreeNode {
    friend class Tree<T>;

   private:
    TreeNode<T>* LeftChild;
    T data;
    TreeNode<T>* RightChild;
};

template <class T>
class Tree {
   public:
    Tree(TreeNode<T> data, TreeNode<T>* left, TreeNode<T>* right) {
        root = &data;
        root->LeftChild = left;
        root->RightChild = right;
    };

    Tree() { root = NULL; };
    ~Tree(){};
    bool isempty() { return (root == NULL); };
    void Insert(T);
    void Inorder() {
        Inorder(root);
        cout << endl;
    };  // Driver
    void Inorder(TreeNode<T>* CurrentNode) {
        if (CurrentNode != NULL) {
            Inorder(CurrentNode->LeftChild);   // Visit LeftChild subtree
            cout << CurrentNode->data << " ";  // Print data
            Inorder(CurrentNode->RightChild);  // Visit RightChild subtree
        }
    };  // Workhorse
    void Preorder() {
        Preorder(root);
        cout << endl;
    };
    void Preorder(TreeNode<T>*);
    void Postorder() {
        // cout << "do postorder by yourself\n";
        Postorder(root);
        cout << endl;
    };
    void Postorder(TreeNode<T>*);
    void Levelorder();
    void Infix(string);
    double Evaluate() {
        return Evaluate(root);
    };
    double Evaluate(TreeNode<T>*);

   private:
    TreeNode<T>* root;
};

// Function to visit nodes in Preorder
template <class T>
void Tree<T>::Preorder(TreeNode<T>* CurrentNode) {
    // cout << "do preorder by yourself\n";
    if (CurrentNode != NULL) {
        cout << CurrentNode->data << " ";
        Preorder(CurrentNode->LeftChild);
        Preorder(CurrentNode->RightChild);
    }
};

// Function to visit nodes in Postorder
template <class T>
void Tree<T>::Postorder(TreeNode<T>* CurrentNode) {
    // cout << "do it by yourself\n";
    if (CurrentNode != NULL) {
        Postorder(CurrentNode->LeftChild);
        Postorder(CurrentNode->RightChild);
        cout << CurrentNode->data << " ";
    }
};
// Insert the item into the tree according to its priority, i.e., A<C<E etc.
// That is the so-called binary search tree
template <class T>
void Tree<T>::Insert(T item) {
    // cout << "do BST insert by yourself\n";
    if (root == NULL) {
        TreeNode<T>* temp = new TreeNode<T>;
        temp->data = item;
        temp->LeftChild = NULL;
        temp->RightChild = NULL;
        root = temp;
    } else {
        TreeNode<T>* temp;
        TreeNode<T>* backup;
        temp = root;
        // backup = NULL;
        while (temp != NULL) {
            // cout<<" "<<temp;
            // cout<<"*";
            backup = temp;
            if (item > temp->data) {
                temp = temp->RightChild;
            } else if (item < temp->data) {
                temp = temp->LeftChild;
            } else {
                return;
            }
            // cout<<"+";
        }
        // cout<<"--"<<backup<<" "<<backup->data<<" "<<item;
        if (item > backup->data) {
            // cout<<">";
            temp = new TreeNode<T>;
            temp->data = item;
            temp->LeftChild = NULL;
            temp->RightChild = NULL;
            backup->RightChild = temp;
        } else if (item < backup->data) {
            // cout<<"<";
            temp = new TreeNode<T>;
            temp->data = item;
            temp->LeftChild = NULL;
            temp->RightChild = NULL;
            backup->LeftChild = temp;
        }
        // else{
        // 	cout<<item<<" WTF";
        // }
    }
};

template <class T>
void Tree<T>::Levelorder() {
    // cout << "do levelorder by yourself\n";
    Queue<TreeNode<T>*> q;
    TreeNode<T>* temp;
    temp = root;
    while (temp != NULL) {
        cout << temp->data << " ";
        if (temp->LeftChild != NULL) {
            q.Push(temp->LeftChild);
        }
        if (temp->RightChild != NULL) {
            q.Push(temp->RightChild);
        }

        if (!q.IsEmpty()) {
            temp = *(q.Pop(temp));
        } else {
            temp = NULL;
        }
    }
};
template <class T>
void Tree<T>::Infix(string s) {
    if (root == NULL) {
        Stack<T> p;
        p = postfix(s);
        p.Delete();
        Stack<TreeNode<T>*> st;
        TreeNode<T>* temp;
        temp = new TreeNode<T>;
        temp->data = p.Delete();
        temp->LeftChild = NULL;
        temp->RightChild = NULL;
        root = temp;
        st.Push(temp);
        while (!p.IsEmpty()) {
            if (temp->RightChild == NULL) {
                temp->RightChild = new TreeNode<T>;
                temp->RightChild->data = p.Delete();
                temp->RightChild->LeftChild = NULL;
                temp->RightChild->RightChild = NULL;
                // cout << "R" << temp->RightChild->data << endl;
                if (isOperator(temp->RightChild->data)) {
                    st.Push(temp);
                    temp = temp->RightChild;
                }

            } else if (temp->LeftChild == NULL) {
                temp->LeftChild = new TreeNode<T>;
                temp->LeftChild->data = p.Delete();
                temp->LeftChild->LeftChild = NULL;
                temp->LeftChild->RightChild = NULL;
                // cout << "L" << temp->LeftChild->data << endl;
                if (isOperator(temp->LeftChild->data)) {
                    st.Push(temp);
                    temp = temp->LeftChild;
                }
            } else {
                temp = st.Delete();
            }
        }

    } else {
        Queue<TreeNode<T>*> q;
        TreeNode<T>* temp;
        temp = root;
        while (temp != NULL) {
            if (temp->LeftChild != NULL) {
                q.Push(temp->LeftChild);
            }
            if (temp->RightChild != NULL) {
                q.Push(temp->RightChild);
            }
            delete temp;

            if (!q.IsEmpty()) {
                temp = *(q.Pop(temp));
            } else {
                temp = NULL;
            }
        }
        root = NULL;
        Infix(s);
    }
}

template <class T>
double Tree<T>::Evaluate(TreeNode<T>* CurrentNode) {
    if (isOperand(CurrentNode->data)) {
        return CurrentNode->data.d;
    } else if (isOperator(CurrentNode->data)) {
        switch (CurrentNode->data.o) {
            case Operator::ADD: {
                return Evaluate(CurrentNode->LeftChild) + Evaluate(CurrentNode->RightChild);
                break;
            }
            case Operator::SUBTRACT: {
                return Evaluate(CurrentNode->LeftChild) - Evaluate(CurrentNode->RightChild);
                break;
            }
            case Operator::MULTIPLY: {
                return Evaluate(CurrentNode->LeftChild) * Evaluate(CurrentNode->RightChild);
                break;
            }
            case Operator::DIVIDE: {
                return Evaluate(CurrentNode->LeftChild) / Evaluate(CurrentNode->RightChild);
                break;
            }
            case Operator::EXP: {
                return pow(Evaluate(CurrentNode->LeftChild), Evaluate(CurrentNode->RightChild));
                break;
            }
            case Operator::MODULO: {
                return fmod(Evaluate(CurrentNode->LeftChild), Evaluate(CurrentNode->RightChild));
                break;
            }
            case Operator::INV:
                StackEmpty();
                return NAN;
                break;
            default:
                break;
        }
    }
}

#endif