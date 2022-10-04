#include "complex.h"
using namespace std;

complex complex::operator+(const complex& c) {
    complex tmp, tmp1 = *this, tmp2(c);
    cout << "\n performing C1 + C2 =" << tmp1 << "+" << tmp2 << " =";
    tmp.real = this->real + c.real;
    tmp.imag = this->imag + c.imag;
    return tmp;
}

complex complex::operator-(const complex c) {
    //a-b = (a.real - b.real) + (a.imag - b.imag)i
    //declare a new complex num with result value
    complex tmp(real - c.real, imag - c.imag), tmp1 = *this, tmp2 = c;
    cout << "\n performing C1 - C2 =" << tmp1 << "-" << tmp2 << " =";
    return tmp;
}

complex complex::operator*(const complex c) {
    //a*b = ((a.real * b.real) - (a.imag * b.imag)) + ((a.real * b.imag) + (b.real * a.imag))i
    //declare a new complex num with result value
    complex tmp((real * c.real) - (imag * c.imag), (real * c.imag) + (imag * c.real)), tmp1 = *this, tmp2 = c;
    cout << "\n performing C1 * C2 =" << tmp1 << "*" << tmp2 << " =";
    return tmp;
}

complex complex::operator/(const complex c) {
    //a*b = ((a.real * b.real) + (a.imag * b.imag))/(b.real^2 + b.imag^2) + (-(a.real * b.imag) + (b.real * a.imag))/(b.real^2 + b.imag^2)i
    //declare a new complex num with result value
    complex tmp, tmp1 = *this, tmp2 = c;
    cout << "\n performing C1 / C2 =" << tmp1 << "/" << tmp2 << " =";
    if (c.real == 0 && c.imag == 0) { // check divisor is not 0
        cout << "divide error" << endl;
    } else {
        //set value
        tmp.setdata(((real * c.real) + (imag * c.imag)) / (pow(c.real, 2) + pow(c.imag, 2)), (-(real * c.imag) + (imag * c.real)) / (pow(c.real, 2) + pow(c.imag, 2)));
    }
    return tmp;
}

complex complex::getconjugate() {
    //z* = z.real - z.imag i
    complex tmp(real, -imag);
    cout << "\n performing C2 = conjugate(C1) =" << endl;
    return tmp;
}

float complex::getmodulus() {
    complex tmp = *this;
    cout << "\n performing |C| ="
         << "|" << tmp << "| = ";
    /*
      you have to implement the code
     */
    // |a| = (a.real^2 + a.imag^2)^(1/2)
    //just return
    return (sqrt(pow(real, 2) + pow(imag, 2)));
}

float complex::getreal() {
    return real;
}

float complex::getimaginary() {
    return imag;
}

ostream& operator<<(ostream& s, const complex& c) {
    s << " (" << c.real << setiosflags(ios::showpos)
      << c.imag << "i"
      << ") " << resetiosflags(ios::showpos);
    return s;
}

complex complex::getreciprocal() {
    // 1/a = a.real/(a.real^2 + a.imag^2) + (a.imag/(a.real^2 + a.imag^2))i
    complex c(real / (pow(real, 2) + pow(imag, 2)), -imag / (pow(real, 2) + pow(imag, 2)));
    return c;
}

void complex::setdata(float r, float i) {
    real = r;
    imag = i;
    return;
}

void complex::getdata() {
    cout << "Enter real:";
    cin >> real;
    cout << real << endl;
    cout << "Enter Imaginary:";
    cin >> imag;
    cout << imag << endl;
    string temp;
    getline(cin, temp);
}

bool complex::operator==(const complex& b) {
    return ((real == b.real) && (imag == b.imag));
}

complex& complex::operator=(const complex& b) {
    real = b.real;
    imag = b.imag;
    return *this;
}
