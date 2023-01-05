/*
Class: CPSC 122-02
Stella Beemer
GU Username: sbeemer2
Submitted By: Stella Beemer
GU Username:
File Name: project7Tst.cpp
Tester file for a linked list with head and tail pointers  
To Build: g++ project7Tst.cpp project7.cpp 
To Execute: ./a.out
*/

#include <iostream>
using namespace std;

#include "project7.h"

int main() {
    List1 lst1;
    for(int i = 0; i < 5; i++) 
        lst1.PutItemH(i);
    lst1.Print();

    List1* lst2 = new List1;
    for(int i = 0; i < 5; i++) 
        lst2->PutItemH(i * 10);
    lst2->Print();

    cout << "testing isEmpty " << lst2->IsEmpty() << endl;
    cout << "testing getLength " << lst2->GetLength() << endl;
    cout << "testing getItemH " << lst2->GetItemH() << endl;

    cout << "testing putItemT " << endl;
    lst2->PutItemT(-10);
    lst2->Print();

    cout << "testing getItemT " << lst2->GetItemT() << endl;

    cout << "testing deleteItemT " << endl;
    lst2->DeleteItemT();
    lst2->Print();

    cout << "testing findItem w/ target = 0 " << lst2->FindItem(0) << endl;
    
    // to test if this function can delete more than one num
    cout << "testing deleteItem w/target = 10 " << endl;
    lst2->PutItemT(10);
    lst2->Print();
    cout << endl;
    lst2->DeleteItem(10);
    lst2->Print();

    delete lst2;
    return 0;
}