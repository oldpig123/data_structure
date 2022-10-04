//-----------------------------------------------------------------------------
// A Polynomial Class
//
#include <iostream>
using namespace std;
#define N 100      // preset maximum number of coefficient for a polynomial
class Polynomial {
friend ostream& operator <<(ostream& os, Polynomial& s);
private:
   float coef[N];    // array of coefficients
   int deg=0;        // the highest exponential degree of polynomial terms (0 for the zero polynomial)

//define public member functions
public:
    Polynomial() { 
        for (int i = 0; i < N; i++) coef[i] = 0;
    };
    char name=' ';
    void getdata(char );           // get polynomial (coeff, order)s data
    void set(float , int );
    int degree();                   // find the deg of a polynomial
    float operator()(int );
    float evaluate(int );
    Polynomial differentiate();     // differentiate this polynomial and return it
    Polynomial operator+(Polynomial& );
    Polynomial operator-(Polynomial& );
    Polynomial operator*(Polynomial& );  // polynomial multiplication
};

