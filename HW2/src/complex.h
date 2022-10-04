#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
//#include "complexi_demo.cpp"
using namespace std;

class complex {
   public:
    float real;  // Real Part
    float imag;  //  Imaginary Part
   public:
    complex(float r = 0, float im = 0) : real(r), imag(im) {}
    complex(const complex& b) {
        real = b.real;
        imag = b.imag;
    }
    complex operator+(const complex& b);
    complex operator-(const complex);
    complex operator*(const complex);
    complex operator/(const complex);
    complex getconjugate();
    complex getreciprocal();
    float getmodulus();
    void setdata(float, float);
    void getdata();
    float getreal();
    float getimaginary();
    bool operator==(const complex&);
    complex& operator=(const complex&);
    friend ostream& operator<<(ostream& , const complex& );
};

