/*
Class: CPSC 122-02
Stella Beemer
GU Username: sbeemer2
Submitted By: Stella Beemer
GU Username:
File Name: project7.cpp
Function file for a linked list with head and tail pointers  
To Build: g++ project7Tst.cpp project7.cpp 
To Execute: ./a.out
*/
#include <iostream>
using namespace std;

#include "project7.h"

List1::List1() {
    head = NULL;
    tail = NULL;
    length = 0;
}

List1::~List1() {
    while(length > 0)
        DeleteItemH();
}

bool List1::IsEmpty() const {
    return (length == 0);
}

int List1::GetLength() const {
    return length;
}

void List1::PutItemH(const itemType newItem) {
    node* tmp = new node;
    tmp->item = newItem;
    tmp->next = head;
    head = tmp;
    length++;
    if(length == 1) {
        tail = tmp;
    }
    tmp = NULL;

}

itemType List1::GetItemH() const {
    return head->item;
}

void List1::DeleteItemH() {
    node* tmp = head->next;
    delete head;
    head = tmp;
    tmp = NULL;
    length--;
}

void List1::PutItemT(const itemType newItem) {
    if(length == 0) {
        PutItemH(newItem);
        return;
    }
    node* tmp = new node;
    tmp->item = newItem;
    tail->next = tmp;
    tail = tmp;
    tail->next = NULL;
    tmp = NULL;
    length++;
}

itemType List1::GetItemT() const {
    return tail->item;
}

void List1::DeleteItemT() {
    node* tmp = head;
    while(tmp->next != tail) 
        tmp = tmp->next;
    tail = tmp;
    delete tmp->next;
    length--;
    tmp = NULL;
    tail->next = NULL;
}

void List1::Print() const {
    node* tmp = head;
    while(tmp != NULL) {
        cout << tmp->item << endl;
        tmp = tmp->next;
    }
}

int List1::FindItem(const itemType target) const {
    int count = 0;
    node* tmp = head;
    while(tmp->next != NULL) {
        if(tmp->item == target)
            count++;
        tmp = tmp->next;
    }
    if(tail->item == target)
        count++;
    
    return count;
}

int List1::DeleteItem(const itemType target) {
    int count, items;
    count = items = FindItem(target);
    node* prev;
    node* cur;
    if(head->item == target) {
        DeleteItemH();
        count--;
    } if(tail->item == target) {
        DeleteItemT();
        count--;
    }
    while(count != 0) {
        prev = cur = head;
        while(cur->item != target && cur->next != NULL) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        delete cur;
        length--;
        count--;

    }
    return items;
}