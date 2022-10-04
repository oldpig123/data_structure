/* Binary Tree Traversal - Preorder, Inorder, Postorder */
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Tree.h"       // design the tree class by yourself
#include "token.h"
#include "mysetting.h"  // don't care
using namespace std;
void init();
Tree<char> bt;
Tree<Token> bt2;
string infix, input, infix2;
int main() {
    char cont;
    init();
    cout << "Part I: Basic Tree Travrsal\n";
    for (int i = 0; i < 8; i++) bt.Insert(input[i]);
    cout << left << setw(15) << "\nOriginal Input Chars:" << input << endl;
    cout << left << setw(15) << "Preorder: ";
    bt.Preorder();
    cout << left << setw(15) << "Inorder: ";
    bt.Inorder();
    cout << left << setw(15) << "Postorder:";
    bt.Postorder();
    cout << left << setw(15) << "Levelorder:";
    bt.Levelorder();
    //*************************************************************
    cout << "\nPartII:BT Infix expression :\n";
    // Tree<Token> bt2;
    // string infix = "2+3*(4-50)/3-(4-30)";
    bt2.Infix(infix);
    cout << left << setw(15) << "\nInorder: ";
    bt2.Inorder();
    cout << left << setw(15) << "Preorder: ";
    bt2.Preorder();
    cout << left << setw(15) << "Postorder:";
    bt2.Postorder();
    cout << left << setw(15) << "Levelorder:";
    bt2.Levelorder();
    cout << "\nThe infix expression " << infix
         << "is evaluated to " << bt2.Evaluate() << endl;
    // bt2.Infix(infix2);
    // cout << left << setw(15) << "\nInorder: ";
    // bt2.Inorder();
    // cout << left << setw(15) << "Preorder: ";
    // bt2.Preorder();
    // cout << left << setw(15) << "Postorder:";
    // bt2.Postorder();
    // cout << left << setw(15) << "Levelorder:";
    // bt2.Levelorder();
    // cout << "\nThe infix expression " << infix2
    //      << "is evaluated to " << bt2.Evaluate() << endl;
    return 0;
}
void init() {                                   // read the infix from the file infix.txt
    ifstream inFile("./src/traversal.txt", ios::in);  // input file
    if (!inFile) {
        cerr << "Cannot open input file. Check the location of file and edit line 45 of main.cpp" << endl;
        exit(1);
    }
    inFile >> debug;
    inFile.clear();
    inFile.ignore(100, '\n');
    inFile >> input;
    inFile.clear();
    inFile.ignore(100, '\n');
    inFile >> infix;
    inFile.clear();
    inFile.ignore(100, '\n');
    inFile >> infix2;
    inFile.clear();
    inFile.ignore(100, '\n');
};
