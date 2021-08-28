/* CS515 Assignment 2
File: evaluation.cpp
Name: Biao Zhang
Section: 1
Date: 09/20/2020
Collaboration Declaration:
          assistance received from online resources etc.
*/
// infix expression evaluation
// implemented with STL vector
// evalues expression with multiple digit numbers, * / + - and {} [] () paratheis
// assume the expression is well formatted with balanced braces. 

#include <iostream>
#include <stack>
#include <climits>
#include <string>
#include <ctype.h>
using namespace std;

//----------------------------------------------------------------
// Generates a stack of string tokens representing postfix
// notation for the input line
void generateRPN(string line, stack<string> &postfix);

//---------------------------------------------------------
// Implementing operation according to the input string
int operation(int a, int b, string op){
    if(op.compare("+") == 0)
        return b+a;
    else if(op.compare("-") == 0)
        return b-a;
    else if(op.compare("*") == 0)
        return b*a;
    else if(op.compare("/") == 0)
        return b/a;
    return INT_MIN;
}

//----------------------------------
// Check whether it is a digit
bool isNumber(string &str){
    string::const_iterator itr = str.begin();
    while(isdigit(*itr))
        itr++;
    return itr == str.end();
}

//----------------------------------------------------------------
// Returns a the result of evaluating the passed postfix token
// stack as a decimal string
string evaluateRPN(stack<string> &postfix)
{
    int a, b;
    stack<int> results;
    while(!postfix.empty()){
        if(postfix.top().compare("+") == 0 || postfix.top().compare("-") == 0
           || postfix.top().compare("*") == 0 || postfix.top().compare("/") == 0) {
            a = results.top();
            results.pop();
            b = results.top();
            results.pop();
            results.push(operation(a, b, postfix.top()));
        } else if(isNumber(postfix.top())) {
            string item = postfix.top();
            string::const_iterator i = item.begin();
            int item_val = 0;
            while(i != item.end()){
                item_val = item_val*10 + *i - '0';
                i++;
            }
            results.push(item_val);
        }
        postfix.pop();
    }
    string result = to_string(results.top());
    return result;
}

//----------------------------------------------------------------
int main(int argc, char ** argv)
{
    string line;
    cout << "Expression: ";
    while ( getline(cin,line) )
    {

        if(line.compare("exit") == 0)
            break;

        // skip empty line
        if (line.length() == 0)
            continue;

        stack<string> postfix;

        generateRPN(line, postfix);

        //Reverse the order of the original stack
        stack<string> reversePostfix;
        while(!postfix.empty()){
            reversePostfix.push(postfix.top());
            postfix.pop();
        }
        
        cout << "Answer: " << evaluateRPN(reversePostfix) << endl;
        line.clear();
        cout << "Expression: ";
    }
    return 0;
}