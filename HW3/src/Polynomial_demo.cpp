// #include <cmath>
// #include <iomanip>

// #include "Polynomial.h"
// void Polynomial::getdata(char c) {
//     float coef;
//     int exp;
//     name = c;
//     while (cin >> coef) {
//         cin >> exp;
//         set(coef, exp);
//     }
//     cin.clear();
//     cin.ignore(100, '\n');
//     cout << setw(4) << ' ' << "Polynomial " << c << ": " << *this << endl;
// };

// Polynomial Polynomial::operator+(Polynomial& b) {
//     Polynomial c;
//     for (int i = 0; i <= this->deg; i++) c.coef[i] += this->coef[i];
//     for (int i = 0; i <= b.deg; i++) c.coef[i] += b.coef[i];
//     c.deg = c.degree();
//     return c;
// }
// Polynomial Polynomial::operator-(Polynomial& b) {
//     Polynomial C;
//     // ===========================
//     // DO IT BY YOURSELF ......
//     // ===========================
//     // C.set(1, 1);
//     for (int i = 0; i <= deg || i <= b.deg; i++) {
//         if (i <= deg) {
//             C.coef[i] += coef[i];
//         }

//         if (i <= b.deg) {
//             C.coef[i] -= b.coef[i];
//         }
//     }
//     C.deg = C.degree();
//     return C;
// }

// Polynomial Polynomial::operator*(Polynomial& b)  // polynomial multiplication
// {
//     Polynomial c;
//     // ===========================
//     // DO IT BY YOURSELF ......
//     // ===========================
//     // c.set(1, 1);
//     for (int i = 0; i <= deg; i++) {
//         for (int j = 0; j <= b.deg; j++) {
//             c.coef[i + j] += coef[i] * b.coef[j];
//         }
//     }
//     c.deg = c.degree();
//     return c;
// }

// Polynomial Polynomial::differentiate() {
//     Polynomial deriv;  // = new Polynomial ( 0, deg - 1 );
//                        // ===========================
//                        // DO IT BY YOURSELF ......
//                        // ===========================
//     // deriv.set(1, 1);
//     for (int i = 0; i < deg; i++) {
//         deriv.coef[i] = (i + 1) * coef[i + 1];
//     }
//     deriv.deg = deriv.degree();
//     return deriv;
// }
// // using C(2) instead of C.evaluate(2)
// // to evaluate the polynomial when x=2
// float Polynomial::operator()(int x) {
//     float p = 0;
//     // ===========================
//     // DO IT BY YOURSELF ......
//     // ===========================
//     for (int i = 0; i <= deg; i++) {
//         p += coef[i] * pow(x, i);
//     }

//     return p;
// }

// // use Horner's method to compute and return the polynomial evaluated at x
// // wiki: https://en.wikipedia.org/wiki/Horner%27s_method
// // https://www.youtube.com/watch?v=RGrmEWj38bsc
// // return the polynomial evaluation with value x
// // or
// float Polynomial::evaluate(int x) {
//     float p = 0;
//     // ===========================
//     // DO IT BY YOURSELF ......
//     // ===========================
//     for (int i = deg; i >= 0; i--) {
//         p = p * x + coef[i];
//     }

//     return p;
// }

// ostream& operator<<(ostream& os, Polynomial& s) {
//     os << "(";
//     for (int i = 99; i >= 0; i--) {
//         if (s.coef[i] != 0) {
//             if (s.coef[i] > 0) os << "+";
//             os << s.coef[i] << "x^" << i;
//         }
//     }
//     os << ")";
//     return os;
// }

// void Polynomial::set(float a, int b) {  // function to set one term (a*x^b)
//     coef[b] = a;
//     if (b > deg) deg = b;
// }
// int Polynomial::degree() {  // find the highest degree of this polynomial
//     int d = 0;
//     for (int i = N - 1; i >= 0; i--)
//         if (coef[i] != 0) {
//             d = i;
//             i = -1;
//         };
//     return d;
// }