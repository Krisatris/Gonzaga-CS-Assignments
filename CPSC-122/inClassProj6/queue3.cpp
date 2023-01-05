//Queue using List and composition 
#include <iostream>
using namespace std;
#include "queue3.h"

PQueue::PQueue() : Queue()
{}

PQueue::PQueue(PQueue* q) : Queue(q)
{}

void PQueue::Enqueue(itemType newItem) { 
    if(IsEmpty()) 
        PutItemH(newItem);
    else if(newItem < head->item)
        PutItemH(newItem);
    else if(newItem > tail->item)
        PutItemT(newItem);
    else {
        node* insertPtr = PtrTo(newItem);
        node* temp = new node;
        temp->next = insertPtr->next;
        insertPtr->next = temp;
        temp->item = newItem;
        insertPtr = NULL;
    }
}

node* PQueue::PtrTo(itemType newItem) {
    node* temp = head;
    while(temp->next->item < newItem) {
        temp = temp->next;
    }
    return temp;
}
	
