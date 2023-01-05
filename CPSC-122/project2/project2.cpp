/*
Class: CPSC 122-02
Team Member 1: Stella Beemer
Team Member 2: no one
Submitted by: Stella Beemer
GU Username: sbeemer2
File Name: project2.cpp
Program reads from an input file and encrypts/decrypts using
a Caesar Cipher
To Build: g++ project2.cpp -o project2
To Execute: ./project2 infile outfile action shift
*/

#include <iostream>
#include <fstream>
using namespace std;

char transform(char ch, int action, int shift);

int main(int argc, char* argv[]) {
	
	if(argc != 5) {
		cout << "Invalid amount of command line arguments!" << endl;
	}
	
	char ch;
	int action = atoi(argv[3]);
	int shift = atoi(argv[4]);
	ifstream fin;
	ofstream fout;

	fin.open(argv[1]);
	fout.open(argv[2]);

	while(fin.peek() != EOF){
		ch = fin.get();
		if(isalpha(ch)) {
			ch = toupper(ch);
			ch = transform(ch, action, shift);
		}
		fout.put(ch);
	}
	fin.close();
	fout.close();
}

/*
Pre:  ch is the character to be encoded
      action is 0/1, 0 is encrypt and 1 is decrypt
      shift is an int in the range [1, 25]
Post: returns an encrypted/decrypted character
*/
char transform(char ch, int action, int shift) {
	if(action == 0) { 
		ch = (((ch - 65) + shift) % 26) + 65;
	} else { 
		ch = ((((ch - 65) + 26) - shift) % 26) + 65;
	}
	return ch;
}
