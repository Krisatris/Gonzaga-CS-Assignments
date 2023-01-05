#include <iostream>
using namespace std;

#include "Queue4.h"

int main(int argc, char* argv[]) {
    int size = atoi(argv[1]);
    CQueue* que = new CQueue(size);
    for(int i = 0; i < size; i++) {
        que->Enqueue(i);
    }
    cout << que->Peek() << endl;
    que->Dequeue();
    que->Print();
    return 0;
}