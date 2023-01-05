#include <iostream>
using namespace std;

#include "project11.h"


//Non-recursive functions
List::List() {
    head = NULL;
}

void List::PutItemH(itemType item) {
    node* tmp = new node;
    tmp->item = item;
    tmp->next = head;
    head = tmp;
    tmp = NULL;
}

itemType List::GetItemH() {
    return head->item; 
}

void List::DeleteItemH() {
    node* cur = head;
    head = head->next;
    delete cur;
}


//Write the following functions recursively or in such a way that they use
//recursive functions


int List::GetLength() {
    return GetLength(head); 
}

int List::GetLength(node* cur) {
    if(cur == NULL) 
        return 0;
    return 1 + GetLength(cur->next);
}

//This can not have complexity O(n^2) 
List::~List() {
    int length = GetLength();
    for(int i = 0; i < length; i++)
        DeleteItemH();
}

bool List::IsEmpty() {
    return (GetLength() == 0);
}

void List::Print() {
    Print(head);
}

void List::Print(node* cur) {
    if(cur == NULL)
        return;
    cout << cur->item << endl;
    Print(cur->next);
}

void List::PrintR() {
    PrintR(head);
}

void List::PrintR(node* cur) {
    if(cur == NULL)
        return;
    PrintR(cur->next);
    cout << cur->item << endl;
}
