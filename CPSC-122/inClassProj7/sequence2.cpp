#include <iostream>
#include <fstream>
using namespace std;

int seq(int steps);

int main(int argc, char* argv[]) {

    cout << seq(atoi(argv[1])) << endl;
}

int seq(int steps) {
    if(steps == 1)
        return 12;
    else
        return seq(steps - 1) - 5;
}