#include "postfix.h"

#include "stack.h"

// function to return precedence value
// if operator is present in stack, in stack priority
int isp(char input) { return -1; }
int isp(Token input) {
    int a = INT32_MAX;
    switch (input.o) {
        case Operator::ADD:
            a = 3;
            break;
        case Operator::U_SUB:
            a = 0;
            break;
        case Operator::SUBTRACT:
            a = 3;
            break;
        case Operator::MULTIPLY:
            a = 2;
            break;
        case Operator::DIVIDE:
            a = 2;
            break;
        case Operator::EXP:
            a = 1;
            break;
        case Operator::MODULO:
            a = 2;
            break;
        case Operator::LPAREN:
            a = 8;
            break;
        case Operator::RPAREN:

            break;
        case Operator::BOTTOM:
            a = 8;
            break;

        default:
            break;
    }
    return a;
}
int icp(char input) { return -1; }
int icp(Token input) {
    int a = INT32_MAX;
    switch (input.o) {
        case Operator::ADD:
            a = 3;
            break;
        case Operator::U_SUB:
            a = 0;
            break;
        case Operator::SUBTRACT:
            a = 3;
            break;
        case Operator::MULTIPLY:
            a = 2;
            break;
        case Operator::DIVIDE:
            a = 2;
            break;
        case Operator::EXP:
            a = 1;
            break;
        case Operator::MODULO:
            a = 2;
            break;
        case Operator::LPAREN:
            a = -1;
            break;
        case Operator::RPAREN:

            break;
        case Operator::BOTTOM:
            a = 8;
            break;
        default:
            break;
    }
    return a;
}

// to check if the input character is an operand
int isOperand(char input) {
    if (input >= '0' && input <= '9') {
        return 1;
    }

    return 0;
}
int isOperand(Token input) {
    if (input.tag == Tag::OPERATOR) {
        return 0;
    } else if (input.tag == Tag::OPERAND) {
        return 1;
    }
}
int isOperator(Token input) {
    if (input.tag == Tag::OPERATOR) {
        return 1;
    } else if (input.tag == Tag::OPERAND) {
        return 0;
    }
}
int isOperator(char input) {
   if (input >= '0' && input <= '9') {
        return 0;
    }

    return 1;
}

Queue<Token> postfix(string e) {  // infix to postfix and return a queue
    Queue<Token> queue = tokenize(e);
    Stack<Token> stack;
    // Token end_p('#');
    // stack.Push(end_p);
    Queue<Token> p_result;
    vector<Token> temp = queue.dump();
    temp.pop_back();
    for (auto i = temp.begin(); i != temp.end(); i++) {
        // cout<<p_result<<endl<< ">";
        if (isOperand(*i)) {
            // cout << "num" << endl;
            p_result.Push(*i);
        } else if (i->o == Operator::RPAREN) {
            // cout << ")" << endl;
            if (!stack.IsEmpty())
            {
                Token j;
            while ( stack.Top(j)->o != Operator::LPAREN ) {
                Token a;
                stack.Delete(a);
                p_result.Push(a);
            }
            stack.Delete(j);
            }
            else
            {
                Token a(0.0,Operator::INV,Tag::OPERATOR,")");
                
                p_result.Push(a);
            }
            
            
            
        } else {
            // cout << "other op" << endl;
            Token j;
            while (!stack.IsEmpty() && isp(*stack.Top(j)) <= icp(*i) ) {
                // cout << "??" << endl;
                Token a;
                stack.Delete(a);
                p_result.Push(a);
            }
            stack.Push(*i);
        }
    }
    while (!stack.IsEmpty()) {
        // cout<<"K"<<stack.IsEmpty();
        Token a;
        stack.Delete(a);
        p_result.Push(a);
    }
    Token end_p('#');
    p_result.Push(end_p);
    cout << setw(10) << left << "PFIX:" << p_result;
    return p_result;
}
