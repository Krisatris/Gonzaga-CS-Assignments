/*
Class: CPSC 122-02
Stella Beemer
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project6.h
Test file for a simple linked list  
To Build: g++ project6Tst.cpp project6.cpp 
To Execute: ./a.out
*/
#include <iostream>
using namespace std;

#include "project6.h"

int main() {
	//Use of a static list 
	List lst;
	for (int i = 0; i < 5; i++)
		lst.PutItemH(i);
	lst.Print();

	//Use of a dynamic list
	List* lst1 = new List;
	for (int i = 0; i < 5; i++)
		lst1->PutItemH(10*i);
	lst1->Print();
	cout << "isEmpty test on two " << lst1->IsEmpty() << endl;
	cout << "getLength test on 2 " << lst1->GetLength() << endl;
	cout << "getItemH test on 2 " << lst1->GetItemH() << endl;
	cout << "deleteItemH test " << endl;
	lst1->DeleteItemH();
	lst1->Print();
	
	int index = lst1->Find(20);
	cout << "find test (using 20) " << index << endl;
	cout << "deleteItem test" << endl;
	lst1->DeleteItem(index);
	lst1->Print();

	delete lst1; //necessary to invoke destructor on dynamic list
	return 0;
}
