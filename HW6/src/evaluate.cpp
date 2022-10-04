#include "postfix.h"
#include "stack.h"

double Eval(Queue<Token>& token)
// Evaluate the postfix expression e¡CIt is assumed that the last token (a token
// is either an operator, operand, or ¡¥#¡¦) in e is ¡¥#¡¦.  A function NextToken is
// used to get the next token from e. The function uses the stack stack
{
    Stack<Token> stack;
    double result = NAN;
	//cout<<token;
    vector<Token> temp = token.dump();
    temp.pop_back();
    for (auto i = temp.begin(); i != temp.end(); i++) {
		//cout<<*i<<endl;
        if (i->tag == Tag::OPERAND) {
			//cout<<"num";
            stack.Push(*i);
        } else {
			//cout<<"op";
            switch (i->o) {
                case Operator::ADD: {
                    double a, b;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        b = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
					result = a+b;
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::U_SUB:{
                    double a;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    
					result = a*-1;
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::SUBTRACT:{
                    double a, b;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        b = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
					result = b-a;
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::MULTIPLY:{
                    double a, b;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        b = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
					result = a*b;
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::DIVIDE:{
                    double a, b;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        b = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
					result = b/a;
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::EXP:{
                    double a, b;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        b = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
					result = pow(b,a);
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::MODULO:{
                    double a, b;
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        a = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
                    if (!stack.IsEmpty()) {
                        Token i;
                        stack.Delete(i);
                        b = i.d;
                    } else {
						StackEmpty();
                        return NAN;
                    }
					result = fmod(b,a);
                    Token r(result);
                    stack.Push(r);
                    break;
                }
                case Operator::INV:
					StackEmpty();
					return NAN;
					break;
                default:
                    break;
            }
        }
		//Token debug;
		//cout<<result<<endl<<*stack.Top(debug)<<"*"<<endl;
    }
	stack.Delete();
	if (stack.IsEmpty())
	{
		return result;
	}
	else{
		StackEmpty();
		return NAN;
	}
	
    
}
