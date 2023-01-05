#include <iostream>
using namespace std;

#include "Queue4.h"

CQueue::CQueue(int sizeIn) {
    que = new itemType[sizeIn];
    front = back = -1;
    size = sizeIn;
    length = 0;
}

CQueue::~CQueue() {
    que = NULL;
    delete [] que;
}

bool CQueue::IsEmpty() {
    return (length == 0);
}

void CQueue::Enqueue(itemType newItem) {
    back = (back + 1) % size;
    que[back] = newItem;
    length++;
}

void CQueue::Dequeue() {
    front = (front + 1) % size;
    length--;
}

void CQueue::Print() {
    for(int i = 0; i < length; i++) {
        cout << que[(front + i + 1) % size] << endl;
    }
}

itemType CQueue::Peek() {
    return que[front + 1];
}