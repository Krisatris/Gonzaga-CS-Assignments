#include <iostream>
#include <fstream>
using namespace std;

int seq1(int steps);
int seq2(int steps);
int seq3(int n, int k);

int main(int argc, char* argv[]) {

    cout << seq1(atoi(argv[1])) << endl;
    cout << seq2(atoi(argv[2])) << endl;
    cout << seq3(atoi(argv[3]), atoi(argv[4])) << endl;
}

int seq1(int steps) {
    if(steps == 1)
        return 12;
    else
        return seq1(steps - 1) - 5;
}

int seq2(int steps) {
    if(steps == 1)
        return 2;
    else if(steps == 2)
        return 3;
    else
        return seq2(steps - 1) * seq2(steps - 2);
}

int seq3(int n, int k) {
    if(n == k)
        return 1;
    else if(k == 0)
        return 1;
    else {
        return seq3(n - 1, k - 1) + seq3(n - 1, k);
    }
}