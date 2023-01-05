/*
Class: CPSC 122-02
Team Member 1: Stella Beemer
Team Member 2: No one
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project5Tst.cpp 
Program creates a C-String class with
        constructor, destructor, display, 
        copy, length, isEqual, find, and concat
To Build: g++ project5.cpp projec5Tst.cpp
To Execute: ./a.out test1 test2 isEqualTst copyTst findTst concatTst
*/
#include "project5.h"
#include <iostream> 
using namespace std;

int main(int argc, char* argv[]) {
    MyString str1(argv[1]); //causes the constructor to run
    str1.myDisplay();

    MyString* str2 = new MyString(argv[2]);
    str2->myDisplay();

    cout << str2->myStrlen() << endl; //test length

    cout << str2->isEqual(argv[3]) << endl; //test isEqual

    str2->myStrcpy(argv[4]); //test copy
    str2->myDisplay();

    cout << str2->find(argv[5]) << endl; //test find

    str2->concat(argv[6]); //test concat
    str2->myDisplay();
    delete str2; //causes the destructor to run
    return 0;  //destructor runs again because str1 goes out of scope
}
   
  
