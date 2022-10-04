//-----------------------------------------------------------------------------
// A Polynomial Class
//
#include <iostream>
using namespace std;
#define N 100  // preset maximum number of coefficient for a polynomial
class Polynomial {
    friend ostream& operator<<(ostream& os, Polynomial& s);

   private:
    int expon[N];   // array of exp
    float coef[N];  // array of coefficients
    int terms = 0;  // the number polynomial terms (0 for the zero polynomial)

    // define public member functions
   public:
    Polynomial() {
        for (int i = 0; i < N; i++) {
            coef[i] = 0;
            expon[i] = 0;
        }
    };
    char name = ' ';
    void getdata(char);  // get polynomial (coeff, order)s data
    void set(float, int);
    void quick_sort(int, int);
    // int degree();  // find the deg of a polynomial
    long double operator()(int);
    long double evaluate(int);
    Polynomial differentiate();  // differentiate this polynomial and return it
    Polynomial operator+(Polynomial&);
    Polynomial operator-(Polynomial&);
    Polynomial operator*(Polynomial&);  // polynomial multiplication
};
