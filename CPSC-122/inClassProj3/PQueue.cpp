//Priority queue using list and inheritance

#include <iostream>
using namespace std;
#include "PQueue.h"

PQueue::PQueue() : Queue()
{}

void PQueue::Enqueue(itemType newItem) {
    if(head->item > newItem) {
        PutItemH(newItem);
    }
    node* cur = head->next;
    node* prev = head;
    while(cur->item < newItem) {
        cur = cur->next;
        prev = cur;
    }
    node* insert = new node;
    insert->item = newItem;
    insert->next = cur;
    prev->next = insert;
}