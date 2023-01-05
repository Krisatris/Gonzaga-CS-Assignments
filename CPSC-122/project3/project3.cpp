/*
Class: CPSC 122-02
Team Member 1: Stella Beemer
Team Member 2: no one
Submitted by: Stella Beemer
GU Username: sbeemer2
File Name: project3.cpp
Program reads from an input file and encrypts/decrypts using a
affine cipher and a hashmap with multiplicative inverses
To Build: g++ project3.cpp -o project3
To Execute: ./project3 infile outfile inverses action alpha beta
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

void makeHash(fstream&, char[], int[]);
void printCipher(char*[], int, int, int, int[]);
void fileOpen(fstream&, char[], char);
char transform(char, int[], int, int, int);

int main(int argc, char* argv[]) {
	if(argc != 7) {
		cout << "Invalid amount of command line arguments!" << endl;
        exit(EXIT_FAILURE);
	}

	fstream finverses;
	int inverses[26];
	makeHash(finverses, argv[3], inverses);
	
	int action = atoi(argv[4]);
	int alpha = atoi(argv[5]);
    int beta = atoi(argv[6]);
	printCipher(argv, action, alpha, beta, inverses);	

	return 0;
}

/*
Pre:  file is a referrence to an fstream object
	  name of the physical file
	  mode is 'r' for input and 'w' for output
Post: file is opened, throws error if one is encountered
*/
void fileOpen(fstream& file, char name[], char mode) {
	string fileType;

	if(mode == 'r')
		fileType = "input";
	if(mode == 'w')
		fileType = "output";

	if(mode == 'r')
		file.open(name, ios::in);
	if(mode == 'w')
		file.open(name, ios::out);

	if(file.fail()) {
		cout << "Error opening " << fileType << " file" << endl;
		exit(EXIT_FAILURE);
	}
}

/*
Pre:  finv is a reference to inverse file fstream object
	  name is the name of finv file
	  inverses is array of inverses to fill
Post: inverses is filled with inverses from file
*/
void makeHash(fstream& finv, char name[], int inverses[]) {
	int index;
	int inverse;
	fileOpen(finv, name, 'r');
	while(finv.peek() != EOF) {
		finv >> index;
		finv >> inverse;
		inverses[index] = inverse;
	}
	finv.close();
}

/*
Pre:  argv[] is command line inputs
	  action is 0/1, passed to transform
	  alpha is int in range [1, 25], passed to transform
	  beta int in range [1, 25], passed to transform
	  inverses is arr of inverses, passed to transform
Post: encypted message is printed to outfile
*/
void printCipher(char* argv[], int action, int alpha, int beta, int inverses[]) {
	char ch;
	fstream fin;
	fstream fout;

	fileOpen(fin, argv[1], 'r');
    fileOpen(fout, argv[2], 'w');

	while(fin.peek() != EOF){
		ch = fin.get();
		if(isalpha(ch)) {
			ch = toupper(ch);
			ch = transform(ch, inverses, action, alpha, beta);
		}
		fout.put(ch);
	}
	fin.close();
	fout.close();
}

/*
Pre:  ch is the character to be encoded
	  arr is the array of multiplicative inverses
      action is 0/1, 0 is encrypt and 1 is decrypt
      alpha is an int in the range [1, 25] used as a multipler
	  beta is an int in the range [1, 25] used for adding
Post: returns an encrypted/decrypted character
*/
char transform(char ch, int arr[], int action, int alpha, int beta) {
	if(action == 1) { 
		alpha = arr[alpha];
		beta = -1 * alpha * beta;
		return (((((ch - 65) + 26) * alpha) + beta) % 26) + 65;
	}
	return ((((ch - 65) * alpha) + beta) % 26) + 65;
}
