// @file Token.cpp
#include "token.h"

#include <sstream>
#include <stdexcept>

#include "postfix.h"

using namespace std;

string opToString(Operator o, string c) {
    string result = "#";
    switch (o) {
        case Operator::ADD:
            result = "+";
            break;
        case Operator::U_SUB:
        case Operator::SUBTRACT:
            result = "-";
            break;
        case Operator::MULTIPLY:
            result = "*";
            break;
        case Operator::DIVIDE:
            result = "/";
            break;
        case Operator::EXP:
            result = "^";
            break;
        case Operator::MODULO:
            result = "%";
            break;
        case Operator::LPAREN:
            result = "(";
            break;
        case Operator::RPAREN:
            result = ")";
            break;
        case Operator::INV:
            result = "[syntax error \"" + c + "\"]";
            break;
        case Operator::BOTTOM:
            result = "#";
            break;
            // default:
            //     result = c;
            //     break;
    }
    return result;
}

ostream& operator<<(std::ostream& os, const Token& t) {
    if (t.tag == Tag::OPERATOR) {
        os << opToString(t.o, t.op);
    } else {
        os << t.d;
    }

    return os;
}

Queue<Token> tokenize(std::string s) {  // tokenize the input

    // DIY
    std::string temp_string = s;
    temp_string.erase(remove(temp_string.begin(), temp_string.end(), ' '), temp_string.end());
    // cout << temp_string << endl;
    Queue<Token> q;
    for (auto i = temp_string.begin(); i != temp_string.end(); i++) {
        switch (*i) {
            case '-': {
                if (i == s.begin() || (isOperator(*(i - 1)) && (*(i - 1) != ')'))) {
                    string temp_s;
                    temp_s.push_back(*i);
                    i++;
                    while (((*i >= '0' && *i <= '9') || *i == '.') && i != s.end()) {
                        temp_s.push_back(*i);
                        i++;
                    }
                    i--;
                    if (temp_s == "-") {
                        Token temp('N');
                        q.Push(temp);

                    } else {
                        Token temp(atof(temp_s.c_str()));
                        q.Push(temp);
                    }

                } else if (isOperand(*(i - 1)) || *(i - 1) == ')') {
                    Token temp(*i);
                    q.Push(temp);
                }
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.': {
                string temp_s;
                while (((*i >= '0' && *i <= '9') || *i == '.') && i != s.end()) {
                    temp_s.push_back(*i);
                    i++;
                }
                i--;

                Token temp(atof(temp_s.c_str()));
                q.Push(temp);

                break;
            }
            default: {
                Token temp(*i);
                q.Push(temp);
                break;
            }
        }
    }
    Token end_t('#');
    q.Push(end_t);
    cout << setw(10) << left << "TOKENIZE:" << q << endl;

    return q;
}