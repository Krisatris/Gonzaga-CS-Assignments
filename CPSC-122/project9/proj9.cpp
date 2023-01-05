#include <iostream>
using namespace std;

#include "calc.h"

Calc::Calc(int argcIn, char* argv[]) {
    inFix = argv[1];
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
        postFix = new char[i + 2];
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

bool Calc::CheckTokens() {
    int i = 0;
    while(inFix[i] != '\0') {
        if(inFix[i] >= 'A' && inFix[i] <= 'Z') {
        } else if(inFix[i] == '(' || inFix[i] == ')') {
        } else if(inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '*' || inFix[i] == '/') {
        } else {
            return false;
        }
        i++;
    }
    return true;
}

bool Calc::CheckParens() {
    int i = 0;
    Stack* stk = new Stack;
    while(inFix[i] != '\0') {
        if(inFix[i] == '(') {
            stk->Push(inFix[i]);
        } else if(inFix[i] == ')') {
            stk->Pop();
        } 
        i++; 
    }
    return (stk->IsEmpty());
}