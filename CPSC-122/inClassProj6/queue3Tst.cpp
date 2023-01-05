#include <iostream>
using namespace std;

#include "queue3.h"


int main()
{
 PQueue* que = new PQueue;
 que->Enqueue(10);
 for (int i = 5; i >= 0; i--)
  que->Enqueue(i);
 que->Enqueue(6);
 que->Print();

 delete que;
 
}
