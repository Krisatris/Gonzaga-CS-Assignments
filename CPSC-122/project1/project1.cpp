/*
Class: CPSC 122-02
Team Member 1: Stella Beemer
Team Member 2: None
Submitted by: Stella Beemer
GU Username: sbeemer2
File Name: project1.cpp
Program generates prime numbers and writes them to a file with a specified number of columns
To build: g++ project1.cpp -o project1
To execute: ./project1 filename.out
*/

#include <iostream>
#include <fstream>
using namespace std;

bool isPrime(int num); 

int main(int argc, char* argv[]) {

	if(argc != 2) {
		cout << "Incorrect number of command line prompts!" << endl;
 		exit(1);
 	}

 	int numInput, colInput;
	ofstream fout;
  
 	cout << "How many integers do you want to see?" << endl;
 	cin >> numInput;

	cout << "Distributed over how many columns?" << endl;
 	cin >> colInput;

	int count = 0;
	int currentNum = 2;
	fout.open(argv[1]);
	while(count != numInput) {
		if(isPrime(currentNum)) {
			fout << currentNum << '\t';
			if(count % colInput == colInput - 1) {
				fout << endl;
			}
			count++;
		}
		currentNum++;
	}
	fout.close();
}

/*
Pre: num is an integer > 1
Post: returns true if num is prime, false otherwise
*/
bool isPrime(int num) {

	for(int i = 2; i <= num / 2; i++) {
		if(num % i == 0) {
			return false;
		}
	}
	return true;
}


