#include <cctype>
#include "stack.h"
#include "postfix.h"
#include "queue.h"
#define debug 0   //set 1/0 for Debug/Release mode
char cont;
double Eval(Queue<Token>&);
void logo();
int main() {
	string infix ;
	Queue <Token> pfix;
	system("CLS");
	do {
		if(debug) logo();
		cout << left << setw(10) << "\nINFIX:    ";
		getline(cin >> ws, infix);
		if(!debug) cout << left << infix<<endl;
		pfix = postfix(infix); 
		cout << "\nEvaluate  "<< infix << " = " << Eval(pfix) << endl;
		cout << "Continue? (Y/N) ";
		cin >> cont; cout << (char) toupper(cont)<<endl;
	} while (cont == 'Y' || cont == 'y');
	return 0;
}
void logo() {
	system("CLS");
	cout << "Demo program of a NTUST 2022 Calculator by J.-J. Chen\n";
	cout<<"well, actually I am YU-CHEN CHU, student ID num is B10807005"<<endl;
	cout << "Enter the infix expression:\n\n";
	cout << left << setw(10) << "INFIX:    ";
}
