#include "ChainNode.h"
#include "Polynomial.h"
#include "av_list.h"

int debug;
int N;
void system_init(ifstream&);
void LOGO() {
    if (debug)
        cout << "===============================================================\n"
             << "       Linked Polynomial Lecture 4 Part I: p44-p47 \n"
             << "      Designed and verified by Jiann-Jone Chen 2022\n"
             << "       		  Done by Yu-Chen Chu 2022\n"
             << "================================================================\n\n";
}
int main() {
    int cont = 1;
    char ch;
    LOGO();
    while (cont) {
        ifstream inFile("./src/polynomial.txt", ios::in);  //"equiv.in" is th input file
        // ifstream inFile("../src/polynomial.txt", ios::in); //"equiv.in" is th input file
        if (!inFile.is_open()) {
            cerr << "Cannot open input file" << endl;
            return 0;
        }
        // cout<<"file open"<<endl;
        system_init(inFile);
        // debug = 1;
        Polynomial a, b, c, d;
        // cout<<"polynomial init"<<endl;
        inFile >> a;  // input polynomial a data
        inFile >> b;  // input polynomial b data
        // cout<<"read file"<<endl;
        c = (a + b);
        cout << "a = " << a << "\nb = " << b << "\nc = a + b =\n"
             << a << " + " << b << " =\n " << c << "\n";
        // cout<<"break 1"<<endl;
        d = a * b;
        // cout<<d<<endl;
        d = c + d;
        // cout<<d<<endl;
        cout << "\n(a+b) + (a*b) =\n"
             << c << '+' << a << " * " << b << " =\n"
             << d << "\n";
        // cout<<"break 2"<<endl;
		d = a;
		cout<<d;
        cont = 0;
        cout << "Press any key to trigger polynomial destructor\n";
        cin.get();
    }  // this right brace trigger polynomial destructor to free all allcated space
    cout << "\nPress any key to terminate the program\n";
    // cin.ignore();
    cin.get();
    return 0;
};

void system_init(ifstream& is) {
    is >> debug;
    is.clear();
    is.ignore(100, '\n');
    is >> N;
    is.clear();
    is.ignore(100, '\n');
}