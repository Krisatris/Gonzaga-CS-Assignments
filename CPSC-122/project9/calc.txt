#include <iostream>
using namespace std;

#include "calc.h"

Calc::Calc(int argcIn, char* argv[]) {
    inFix = argv[1];
    stk = new Stack;
    if(CheckTokens() && CheckParens()) {
        int i = 0;
        int j = 0;
        hashTble = new int[26];
        while(inFix[i] != '\0') {
            if(inFix[i] >= 'A' && inFix[i] <= 'Z' && hashTble[int(inFix[i] - 65)] == 0) {
                hashTble[int(inFix[i] - 65)] = atoi(argv[j + 2]);
                j++;
            }
            i++;
        }
        postFix = new char[j * 2];
        postFix[(j * 2) - 1] = '\0';
    }
}

Calc::~Calc() {
    stk = NULL;
    inFix = NULL;
    postFix = NULL;
    hashTble = NULL;
    delete stk;
    delete inFix;
    delete postFix;
    delete hashTble;
}

void Calc::DisplayInFix() {
    int i = 0;
    while(inFix[i] != '\0') {
        cout << inFix[i];
        i++;
    }
    cout << endl;
}

void Calc::DisplayPostFix() {
    int i = 0;
    while(postFix[i] != '\0') {
        cout << postFix[i];
        i++;
    }
    cout << endl;
}

void Calc::InFixToPostFix() {
    int i = 0;
    int j = 0;
    while(inFix[i] != '\0') {
        switch(inFix[i]) {
            case 'A' ... 'Z':
                postFix[j] = inFix[i];
                j++;
                break;
            case '(':
                break;
            case '+' : case '-': case '*': case '/':
                stk->Push(inFix[i]);
                break;
            case ')':
                postFix[j] = stk->Peek();
                j++;
                stk->Pop();
                break;
        }
        i++;
    }
}

void Calc::Evaluate() {
    int i = 0;
    int op1 = 0;
    int op2 = 0;
    int res = 0;
    int temp = 0;
    while(postFix[i] != '\0') {
        if(postFix[i] >= 'A' && postFix[i] <= 'Z') {
            temp = hashTble[int(postFix[i]) - 65];
            stk->Push(temp);
        } else {
            op2 = stk->Peek();
            stk->Pop();
            op1 = stk->Peek();
            stk->Pop();
            switch (postFix[i]) {
                case '+':
                    res = op1 + op2;
                    stk->Push(res);
                    break;
                case '-':
                    res = op1 - op2;
                    stk->Push(res);
                    break;
                case '*':
                    res = op1 * op2;
                    stk->Push(res);
                    break;
                case '/':
                    res = op1 / op2;
                    stk->Push(res);
                    break;
                default:
                    break;
            }
        }
        i++;
    }
    cout << "result is " << stk->Peek() << endl;
}

bool Calc::CheckTokens() {
    int i = 0;
    while(inFix[i] != '\0') {
        switch (inFix[i]) {
            case 'A' ... 'Z':
                break;
            case '(': case ')':
                break;
            case '+': case '-': case '*': case '/':
                break;
            default:
                return false;
                break;
        }
        i++;
    }
    return true;
}

bool Calc::CheckParens() {
    int i = 0;
    while(inFix[i] != '\0') {
        switch(inFix[i]) {
            case '(':
                stk->Push(inFix[i]);
                break;
            case ')':
                stk->Pop();
                break;
            default:
                break;
        }
        i++; 
    }
    return (stk->IsEmpty());
}