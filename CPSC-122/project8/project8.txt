/*
Class: CPSC 122-02
Stella Beemer
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project8.cpp
Function file for a doubly linked list with dummy notes at head and
tail to make insertion and deletion easier
To Build: g++ project8Tst.cpp project8.cpp
To Execute: ./a.out
*/
#include <iostream>
using namespace std;

#include "project8.h"

List2::List2() {
    length = 0;
    
    //create dummy nodes;
    head = new doubleNode;
    tail = new doubleNode;

    //set values for head dummy node;
    head->prev = NULL;
    head->next = tail;

    //set values for tail dummy node;
    tail->prev = head; 
    tail->next = NULL;
}

List2::List2(List2* lst) {
    length = 0;

    //create dummy nodes
    head = new doubleNode;
    tail = new doubleNode;

    //set values for head dummy nodes
    head->prev = NULL;
    head->next = tail;

    //set values for tail dummy nodes
    tail->prev = head;
    tail->next = NULL;
    
    doubleNode* cur = new doubleNode;
    cur = head;
    doubleNode* temp = new doubleNode;
    temp = lst->head->next;
    while(temp != lst->tail) {
        doubleNode* insert = new doubleNode;
        insert->item = temp->item;
        insert->next = tail;
        insert->prev = cur;
        cur->next = insert;
        tail->prev = insert;
        cur = cur->next;
        temp = temp->next;
        length++;
    }
    cur = NULL;
    temp = NULL;
}

List2::~List2() {
    while(length > 0)
        Delete(length);
    head = NULL;
    tail = NULL;
}

void List2::Insert(itemType item, int pos) {
    //new node goes between these two nodes
    doubleNode* insertPtA = FindPosition(pos);  
    doubleNode* insertPtB = insertPtA->next; 

    //create new node and set its values
    doubleNode* tmp = new doubleNode; 
    tmp->prev = insertPtA;
    tmp->item = item;
    tmp->next = insertPtB;

    //set pointers for the previous and next nodes
    insertPtA->next = tmp;
    insertPtB->prev = tmp;

    length++;
}

void List2::Delete(int pos) {
    doubleNode* deletePtA = FindPosition(pos + 1);
    doubleNode* deletePtB = deletePtA->prev;
    doubleNode* deletePtC = deletePtA->next;
    
    deletePtB->next = deletePtA->next;
    deletePtC->prev = deletePtA->prev;

    delete deletePtA;
    length--;
}

int List2::DeleteAll(itemType item) {
    int count = 0;
    doubleNode* temp = head->next;
    int pos = 1;
    while(temp != NULL) {
        if(temp->item == item) {
            count++;
            temp = temp->next;
            Delete(pos);
        } else {
            pos++;
            temp = temp->next;
        }
    }
    return count;
}

void List2::PrintForward() {
    doubleNode* cur = head->next;

    int i = 0;
    while (i < length) {
        cout << cur->item << endl;
        cur = cur->next;
        i++;
    }
}

void List2::PrintBackwards() {
    doubleNode*  cur = tail->prev;

    int i = 0;
    while (i < length) {
        cout << cur->item << endl;
        cur = cur->prev;
        i++;
    }
}

void List2::Sort() {
    int len = length - 1;
    itemType temp;
    doubleNode* start = head->next;
    doubleNode* cur = head->next;
    doubleNode* small = head->next;

    for(int i = 0; i < length - 1; i++) {
        for(int j = 0; j < len; j++) {
            cur = cur->next;
            if(cur->item < small->item)
                small = cur;
        }
        len = len - 1;

        //swap
        temp = small->item;
        small->item = start->item;
        start->item = temp;
        start = start->next;
        cur = start;
        small = cur;
    }
    start = NULL;
    cur = NULL;
    small = NULL;
}

doubleNode* List2::FindPosition(int pos) {
    doubleNode* cur = head;
    int i = 0;
    while (i < pos - 1) {
        cur = cur->next;
        i++;
    }
    return cur;
} 
