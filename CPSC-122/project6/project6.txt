/*
Class: CPSC 122-02
Stella Beemer
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project6.h
function file for a simple linked list  
To Build: g++ project6Tst.cpp project6.cpp 
To Execute: ./a.out
*/
#include <iostream>
using namespace std;

#include "project6.h"

List::List() {
    head = NULL;
    length = 0;
}

List::~List() {
    while(length > 0)
        DeleteItemH();
}

bool List::IsEmpty() const {
    return (length == 0);
}


int List::GetLength() const {
    return length;
}

void List::PutItemH(const itemType newItem) {
    node* tmp = new node;
    tmp->item = newItem;
    tmp->next = head;
    head = tmp;
    length++;
    tmp = NULL;
}

itemType List::GetItemH() const {
    return head->item;
}

void List::DeleteItemH() {
    node* tmp = head->next;
    delete head;
    head = tmp;
    tmp = NULL;
    length--;
}
	
void List::Print() const {
    node * tmp = head;
    while(tmp != NULL) {
        cout << tmp->item << endl;
        tmp = tmp->next;
    }
}

int List::Find(const itemType item) const {
    int index = -1;
    int i = 0;
    node* tmp = head;
    while(index == -1 && tmp != NULL) {
        if(tmp->item == item)
            index = i;
        i++;
        tmp = tmp->next;
    }
    return index;
}

void List::DeleteItem(const int pos) {
    int i = 0;
    node* prev = head;
    node* cur = head;
    while(i < pos) {
        prev = cur;
        cur = cur->next;
        i++;
    }
    prev->next = cur->next;
    delete cur;
    length--;
    prev = cur = NULL;
}