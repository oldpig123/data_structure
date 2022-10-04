#include "Polynomial_bonus.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
void Polynomial::getdata(char c) {
    float coef;
    int exp;
    name = c;
    while (cin >> coef) {
        cin >> exp;
        set(coef, exp);
    }
    cin.clear();
    cin.ignore(100, '\n');
    cout << setw(4) << ' ' << "Polynomial " << c << ": " << *this << endl;
};

Polynomial Polynomial::operator+(Polynomial& b) {
    Polynomial c;
    int i = 0, j = 0;
    while (i < terms || j < b.terms) {//compare the exponent of each term of two polynamials and cal the lower first
        if (i < terms && expon[i] < b.expon[j]) {
            c.coef[c.terms] += coef[i];
            c.expon[c.terms] = expon[i];
            c.terms++;
            i++;
        }
        if (j < terms && expon[i] > b.expon[j]) {
            c.coef[c.terms] += b.coef[j];
            c.expon[c.terms] = b.expon[j];
            c.terms++;
            j++;
        }
        if (expon[i] == b.expon[j] && i < terms && j < b.terms) {
            c.coef[c.terms] += coef[i] + b.coef[j];
            c.expon[c.terms] = b.expon[j];
            c.terms++;
            i++;
            j++;
        }
        if (i == terms) {//if the terms of the polynomial with lower deg is less then other, just do the rest cal of the higher-deg one 
            c.coef[c.terms] += b.coef[j];
            c.expon[c.terms] = b.expon[j];
            c.terms++;
            j++;
        }
        if (j == b.terms) {
            c.coef[c.terms] += coef[i];
            c.expon[c.terms] = expon[i];
            c.terms++;
            i++;
        }
    }

    // c.deg = c.degree();
    return c;
}
Polynomial Polynomial::operator-(Polynomial& b) {
    Polynomial c;
    // ===========================
    // DO IT BY YOURSELF ......
    // ===========================
    // C.set(1, 1);
    int i = 0, j = 0;
    while (i < terms || j < b.terms) {//just like operator+, but the cal with polynomail B is - not +
        if (i < terms && expon[i] < b.expon[j]) {
            c.coef[c.terms] += coef[i];
            c.expon[c.terms] = expon[i];
            c.terms++;
            i++;
        }
        if (j < terms && expon[i] > b.expon[j]) {
            c.coef[c.terms] -= b.coef[j];
            c.expon[c.terms] = b.expon[j];
            c.terms++;
            j++;
        }
        if (expon[i] == b.expon[j] && i < terms && j < b.terms) {
            c.coef[c.terms] += (coef[i] - b.coef[j]);
            c.expon[c.terms] = b.expon[j];
            c.terms++;
            i++;
            j++;
        }
        if (i == terms) {
            c.coef[c.terms] -= b.coef[j];
            c.expon[c.terms] = b.expon[j];
            c.terms++;
            j++;
        }
        if (j == b.terms) {
            c.coef[c.terms] += coef[i];
            c.expon[c.terms] = expon[i];
            c.terms++;
            i++;
        }
    }
    return c;
}

Polynomial Polynomial::operator*(Polynomial& b)  // polynomial multiplication
{
    Polynomial c;
    // ===========================
    // DO IT BY YOURSELF ......
    // ===========================
    // c.set(1, 1);
    for (int i = 0; i < terms; i++) {//just like human do std multiplication on paper but seqeunce switched (B*A)
        for (int j = 0; j < b.terms; j++) {
            if (find(c.expon, c.expon + c.terms, expon[i] + b.expon[j]) == c.expon + c.terms) {
                c.expon[c.terms] = expon[i] + b.expon[j];
                c.coef[c.terms] = coef[i] * b.coef[j];
                c.quick_sort(0, c.terms);
                c.terms++;

            } else {
                c.coef[find(c.expon, c.expon + c.terms, expon[i] + b.expon[j]) - c.expon] += coef[i] * b.coef[j];
                ;
            }
        }
    }
    // c.deg = c.degree();

    return c;
}

Polynomial Polynomial::differentiate() {
    Polynomial deriv;  // = new Polynomial ( 0, deg - 1 );
                       // ===========================
                       // DO IT BY YOURSELF ......
                       // ===========================
    // deriv.set(1, 1);
    for (int i = 0; i < terms; i++) {//dA/dx = d(ax^n)/dx = (a*n)x^(n-1)
        if (expon[i] - 1 >= 0) {
            deriv.expon[deriv.terms] = expon[i] - 1;
            deriv.coef[deriv.terms] = coef[i] * expon[i];
            deriv.terms++;
        }
    }
    return deriv;
}
// using C(2) instead of C.evaluate(2)
// to evaluate the polynomial when x=2
long double Polynomial::operator()(int x) {
    long double p = 0;
    // ===========================
    // DO IT BY YOURSELF ......
    // ===========================
    for (int i = 0; i < terms; i++) {//just cal an*x^n from first term to last term. the time complexity is sum of exponent of all terms
        p += (long double)coef[i] * pow((long double)x, (long double)expon[i]);//but the time complexity of func "pow" is much faster
    }

    return p;
}

// use Horner's method to compute and return the polynomial evaluated at x
// wiki: https://en.wikipedia.org/wiki/Horner%27s_method
// https://www.youtube.com/watch?v=RGrmEWj38bsc
// return the polynomial evaluation with value x
// or
long double Polynomial::evaluate(int x) {
    long double p = 0;
    // ===========================
    // DO IT BY YOURSELF ......
    // ===========================
    for (int i = terms; i >= 0; i--) {//well, just go check wiki. time complexity is the deg of the polynamial
        int temp = expon[i];
        p += (long double)coef[i];
        while (temp > expon[i - 1] && i > 0) {
            p = p * (long double)x;
            temp--;
        }
        while (temp > 0 && i == 0) {
            p = p * (long double)x;
            temp--;
        }
    }

    return p;
}

ostream& operator<<(ostream& os, Polynomial& s) {//save coefficient and term from low to high to stream buffer
    os << "(";
    for (int i = s.terms; i >= 0; i--) {
        if (s.coef[i] != 0) {
            if (s.coef[i] > 0) os << "+";
            os << s.coef[i] << "x^" << s.expon[i];
        }
    }
    os << ")";
    return os;
}

void Polynomial::set(float a, int b) {  // function to set one term (a*x^b)
    if (find(expon, expon + terms, b) == expon + terms) {//determine if the  term with exponent b is set first, creat a new term if no, or modify it.
        expon[terms] = b;
        coef[terms] = a;
        quick_sort(0, terms);
        terms++;
    } else {
        expon[find(expon, expon + terms, b) - expon] = a;
    }

} /*
 int Polynomial::degree() {  // find the highest degree of this polynomial
     int d = 0;
     for (int i = N - 1; i >= 0; i--)
         if (coef[i] != 0) {
             d = i;
             i = -1;
         };
     return d;
 }*/
void Polynomial::quick_sort(int left, int right) {  // quick sort algorithm, sort the terms of polynomial from lower exponent to higher

    if (left > right) {  // terminate condition
        return;
    }

    int i = left, j = right, temp = expon[left];  // chose a standard val
    float t_coef = coef[left];

    while (i != j) {  // group data with the smaller at left ane bigger at right

        while (expon[j] >= temp && i < j)
            j--;
        while (expon[i] <= temp && i < j)
            i++;

        int t = expon[i];
        float t_c = coef[i];
        expon[i] = expon[j];
        coef[i] = coef[j];
        expon[j] = t;
        coef[j] = t_c;
    }

    expon[left] = expon[i];  // put the std data at middle
    coef[left] = coef[i];
    expon[i] = temp;
    coef[i] = t_coef;
    quick_sort(left, i - 1);   // do it again with smaller side
    quick_sort(i + 1, right);  // do it again with bigger side
}