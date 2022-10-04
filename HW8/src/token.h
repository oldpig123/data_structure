#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Queue.h"
//#include "postfix.h"
using namespace std;
extern int isOperator(char);
extern int isOperand(char);
enum class Tag { OPERATOR = 0,
                 OPERAND };  // 0:OPERATOR, 1:OPERAND...
enum class Operator { ADD = 0,
                      SUBTRACT,
                      MULTIPLY,
                      DIVIDE,
                      MODULO,
                      LPAREN,
                      RPAREN,
                      BOTTOM,
                      EXP,
                      U_SUB,
                      INV };
// enum Op2 {'+', '-', '*', '/', '%', '(', ')','#'};
class Token {
    friend ostream& operator<<(ostream& os, const Token& t);

   public:
    Token() {
        d = 0.0;
        o = Operator::ADD;
        tag = Tag::OPERATOR;
		op = "";
    };
    Token(double d_in, Operator o_in, Tag t_in, string op_in) {
        d = d_in;
        o = o_in;
        tag = t_in;
        op = op_in;
    };
    Token(double num) {
        d = num;
        tag = Tag::OPERAND;
    }
    Token(char c) {
		
        if (isOperator(c))
            tag = Tag::OPERATOR;
        else if (isOperand(c)) {
            tag = Tag::OPERAND;
            d = (double)(c) - (int)('0');
        }
		op.push_back(c);
        // cout<<c<<endl;
        switch (c) {
            case '+':
                o = Operator::ADD;
                break;
            case '-':
                o = Operator::SUBTRACT;
                break;
            case '*':
                o = Operator::MULTIPLY;
                break;
            case '/':
                o = Operator::DIVIDE;
                break;
            case '%':
                o = Operator::MODULO;
                break;
            case '(':
                o = Operator::LPAREN;
                break;
            case ')':
                o = Operator::RPAREN;
                break;
            case '#':
                o = Operator::BOTTOM;
                break;
            case '^':
                o = Operator::EXP;
                break;
            case 'N':
                o = Operator::U_SUB;
                break;
            default: {
                // cout << "[Invalid Token " << '\'' << c << '\'' << " ]";
                o = Operator::INV;
                break;
            }
        }
    }
    ~Token(){};  // destructor
    bool operator!=(const Token& rhs) const {
        return !(o == rhs.o);
    }
    bool operator==(const char& op) const {
        Token t(op);
        return (o == t.o);
    }
    double d;  // store the operand
    string op;
    Operator o;  // an enum to store the operator type
    Tag tag;     // a tag 0/1 to indicate this token is operator or operand
};

string opToString(Operator o);
ostream& operator<<(ostream& os, const Token& t);
Queue<Token> tokenize(std::string s);
#endif
