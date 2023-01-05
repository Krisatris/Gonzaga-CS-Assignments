#include <iostream>
using namespace std;

#include "project11.h"


int main() {
    List* lst1 = new List;
    for (int i = 0; i < 5; i++)
        lst1->PutItemH(i);
    cout << lst1->GetLength() << endl;
    cout << lst1->IsEmpty() << endl << endl;
    lst1->Print();
    cout << endl;
    lst1->PrintR();

    delete lst1; 
    return 0;
}
