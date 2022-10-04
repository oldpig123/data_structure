//#ifndef POLYNOMIAL_H
//#define POLYNOMIAL_H
#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iomanip>

#include "Chain.h"
#include "ChainIterator.h"

extern int debug;
using namespace std;

struct Term {  // all members of Term are public by default
    int coef;  // coefficient
    int exp;   // exponential lorder
    Term Set(int c, int e) {
        coef = c;
        exp = e;
        return *this;
    };
    Term Set(ChainNode<Term> temp) {
        Term data = temp.GetData();
        coef = data.coef;
        exp = data.exp;
        return *this;
    };
};
class Polynomial {
    friend ostream& operator<<(ostream&, Polynomial&);
    friend istream& operator>>(istream&, Polynomial&);
    friend Polynomial operator+(const Polynomial&, const Polynomial&);

   public:
    // Polynomial(Chain <Term>ll) :poly(ll) { label = '0' + counter++;  };
    Polynomial() {
        label = 'A' + counter;
        num = counter++;
        message();
    };
    Polynomial(char c) {
        label = c;
        num = counter++;
        message();
    };
    Polynomial(const Polynomial&);  // copy constructor
    ~Polynomial();
    void operator=(const Polynomial&);
    Polynomial operator*(const Polynomial&) const;

   public:
    Chain<Term> poly;
    void free();
    char label;

   private:
    void message();
    static int counter;
    int num;
};
// ======================================
//   COPY CONSTRUCTOR of polynomial
// ======================================
Polynomial::Polynomial(const Polynomial& p) {
    ChainNode<Term>* current = p.poly.first;
    this->num = counter++;
    this->label = p.label;
    this->poly.current = this->poly.first;
	ChainNode<Term>* temp;
    while (current) {
        if (this->poly.current) {
            this->poly.current->data = current->data;
			temp = this->poly.current;
            this->poly.current = this->poly.current->link;
        } else {
            poly.InsertBack(current->data);
			poly.current = poly.last->link;
            
        }

        current = current->link;
    }
	

    if (this->poly.current) {
		cout<<"0";
        this->poly.current->avv->last->link = this->poly.current;
        this->poly.current->avv->last = this->poly.last;
        this->poly.current->avv->last->link = NULL;
		this->poly.last = temp;
        this->poly.last->link = NULL;
		this->poly.current->avv->num += (this->poly.num - p.poly.num);
		if (debug) cout << "\nrecycle " << (this->poly.num - p.poly.num)<< " nodes->total AV nodes = " << this->poly.current->avv->num << endl;
    }

    message();
};

//======================================
// print out poly object message
//======================================
void Polynomial::message() {
    if (debug) cout << "\nConstruct Poly(num=" << this->num << ", op=" << this->label << ")";
};

int Polynomial::counter = 0;  // initialize static variables
//======================================
// COPY 'ASSIGNMENT' of Polynomial
//======================================
void Polynomial::operator=(const Polynomial& p) {
    /* do it by yourself */
    ChainNode<Term>* current = p.poly.first;
    // this->num = counter++;
    // this->label = p.label;
    this->poly.current = this->poly.first;
	ChainNode<Term>* temp;
    while (current) {
        if (this->poly.current) {
            this->poly.current->data = current->data;
			temp = this->poly.current;
            this->poly.current = this->poly.current->link;
        } else {
            poly.InsertBack(current->data);
			poly.current = poly.last->link;
            
        }

        current = current->link;
    }
	

    if (this->poly.current) {
		cout<<"0";
        this->poly.current->avv->last->link = this->poly.current;
        this->poly.current->avv->last = this->poly.last;
        this->poly.current->avv->last->link = NULL;
		this->poly.last = temp;
        this->poly.last->link = NULL;
		this->poly.current->avv->num += (this->poly.num - p.poly.num);
		if (debug) cout << "\nrecycle " << (this->poly.num - p.poly.num)<< " nodes->total AV nodes = " << this->poly.current->avv->num << endl;
    }


    message();
};
// Destructor: executed automatically after the corresponding '}"
Polynomial::~Polynomial() {
    // The ~Chain() will be triggered to clear the linked list poly
    if (debug) cout << "\nDestruct Poly(num=" << this->num << ", op=" << setw(2) << (char)this->label << "): ";
};
// The destructor automatically delete a linkted list data but
// it conflicts with an operator overloading function p3 = p1 + p2;
void Polynomial::free() {  // Free all nodes in the chain
    cout << "Free Polynomial " << setw(4) << (char)this->label << endl;
    poly.free();
};

// polynomial multiplication function
Polynomial Polynomial::operator*(const Polynomial& b) const {
    // ChainIterator <Term> ai(poly);
    Polynomial c('*');
    ChainIterator<Term> ai(this->poly);
    while (ai.NotNull()) {
        // cout<<"*"<<endl;
        ChainIterator<Term> bi(b.poly);
        while (bi.NotNull()) {
            // cout<<"-"<<endl;
            c.poly.current = c.poly.first;
            while (c.poly.current) {
                if (c.poly.current->data.exp == (ai.current->GetData().exp + bi.current->GetData().exp)) {
                    c.poly.current->data.coef += (ai.current->GetData().coef * bi.current->GetData().coef);
                    break;
                }
                c.poly.current = c.poly.current->link;
            }
            if (!c.poly.current) {
                Term temp;
                temp.Set(ai.current->GetData().coef * bi.current->GetData().coef, ai.current->GetData().exp + bi.current->GetData().exp);
                c.poly.InsertInorder(temp);
            }
            bi++;
        }
        ai++;
    }

    return c;
};

Polynomial operator+(const Polynomial& a, const Polynomial& b) {
    Term temp;
    ChainIterator<Term> ai(a.poly), bi(b.poly);
    Polynomial c('+');
    // Term* t1 = new Term;
    // t1->Set(9, 9);
    // Term* t2 = new Term;
    // t2->coef = 8;
    // t2->exp = 8;
    // c.poly.Create2(*t1, *t2);
    /*     	Do it by yourself  	*/
    while (ai.NotNull() || bi.NotNull()) {
        // cout << "*" << endl;
        if (ai.NotNull() && bi.NotNull() && ai.current->GetData().exp > bi.current->GetData().exp) {
            // cout << "case 1" << endl;
            Term temp;
            temp.Set(*(ai.current));
            c.poly.InsertBack(temp);
            ai++;
        }
        if (bi.NotNull() && ai.NotNull() && ai.current->GetData().exp < bi.current->GetData().exp) {
            // cout << "case 2" << endl;
            Term temp;
            temp.Set(*(bi.current));
            c.poly.InsertBack(temp);
            bi++;
        }
        if (ai.NotNull() && bi.NotNull() && ai.current->GetData().exp == bi.current->GetData().exp) {
            // cout << "case 3" << endl;
            Term temp;
            temp.Set(ai.current->GetData().coef + bi.current->GetData().coef, ai.current->GetData().exp);
            c.poly.InsertBack(temp);
            ai++;
            bi++;
        }
        if (!bi.NotNull() && ai.NotNull()) {
            // cout << "case 4" << endl;
            Term temp;
            temp.Set(*(ai.current));
            c.poly.InsertBack(temp);
            ai++;
        }
        if (!ai.NotNull() && bi.NotNull()) {
            // cout << "case 5" << endl;
            Term temp;
            temp.Set(*(bi.current));
            c.poly.InsertBack(temp);
            bi++;
        }
        // if (!ai.NotNull() && !bi.NotNull()) {
        //     cout << "WTF" << endl;
        // }
        // cout << "--" << endl;
    }
    // cout << "add done" << endl;
    return c;
};

ostream& operator<<(ostream& out, Polynomial& p) {
    ChainIterator<Term> ct(p.poly);
    char sign;
    int first = 1;
    out << "(";

    while (ct.NotNull()) {
        sign = ct->coef > 0 ? '+' : '-';
        if (first && sign == '+') {
            out << fabs(ct->coef) << "x^" << ct->exp;
            first = 0;
        } else
            out << ' ' << sign << ' ' << fabs(ct->coef) << "x^" << ct->exp;
        ct++;
    }
    // Term t = p.poly.FirstNode()->GetData();
    // out << t.coef << "x^" << t.exp;
    out << ")";

    return out;
};

istream& operator>>(istream& is, Polynomial& p)
// read in a polynomial  and set up its linked representation.
{
    int i, nterm;
    Term s;
    is >> nterm;
    is.clear();
    is.ignore(100, '\n');
    // cout << nterm << endl;
    for (i = 0; i < nterm; i++) {
        is >> s.coef >> s.exp;  // matrix dimensions
        p.poly.InsertBack(s);
    }
    // Term* t1 = new Term;
    // t1->Set(9, 9);
    // Term* t2 = new Term;
    // t2->coef = 8;
    // t2->exp = 8;
    // p.poly.Create2(*t1, *t2);
    return is;
};

//#endif
