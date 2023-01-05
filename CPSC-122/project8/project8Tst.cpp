/*
Class: CPSC 122-02
Stella Beemer
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project8Tst.cpp
Test file for a doubly linked list with dummy notes at head and
tail to make insertion and deletion easier
To Build: g++ project8Tst.cpp project8.cpp
To Execute: ./a.out
*/
#include <iostream>
using namespace std;

#include "project8.h"

int main() {
  List2* lst = new List2;
  
  for (int i = 1; i <= 10; i++)
    lst->Insert(i,i);

  lst->Insert(11,11);
  lst->Insert(10, 3);
  lst->Insert(-1,1);
  lst->Insert(500,5);

  cout << "Front To Back" << endl;
  lst->PrintForward();

  cout << "Back To Front" << endl;
  lst->PrintBackwards();

  cout << "delete item" << endl;
  lst->Delete(1);
  lst->PrintForward();
  
  cout << "delete items 10 " << lst->DeleteAll(10) << endl;
  lst->PrintForward();
  
  cout << "sort list" << endl;
  lst->Sort();
  lst->PrintForward();
  
  cout << "copy constructor \n" << endl;
  List2* lst2 = new List2(lst);
  lst->PrintForward();

  return 0;
}
