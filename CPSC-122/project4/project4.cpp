/*
Class: CPSC 122-02
Team Member 1: Stella Beemer
Team Member 2: No one
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project4.cpp 
Program reads an inp;ut file into an array
        sorts the input file using selection sort and dynamic memory 
        writes the sorted array to an output file 
To Build: g++ project4.cpp -o project4
To Execute: ./project4 infile outfile lineNum 
*/

#include <iostream>
#include <fstream> 
#include <string>
#include <cstdlib>
using namespace std;

void fileOpen(fstream&, char[], char);
void readData(fstream&, char[], string[], int);
void writeData(fstream&, char[], string[], int);
void selSort(string[], int);
int findSmallest(string[], int, int);
void swap(string[], int, int);

int main(int argc, char* argv[]) {
	fstream fin;
	fstream fout;
	string line;
	string * data;
	int size = atoi(argv[3]);
	data = new string[size];

	if (argc != 4)
	{ 
		cout << "Incorrect number of command line arguments" << endl;
		exit(EXIT_FAILURE);
	}

	readData(fin, argv[1], data, size);

	selSort(data, size);

	writeData(fout, argv[2], data, size);

	return 0;
}

void readData(fstream& file, char fileName[], string data[], int size) {
	fileOpen(file, fileName, 'r');
	for (int i = 0; i < size; i++)
		getline(file, data[i]);
	file.close();
}

void writeData(fstream& file, char fileName[], string data[], int size) {
	fileOpen(file, fileName, 'w');
	for (int i = 0; i < size; i++)
		file << data[i] << endl;
	file.close();
}

void fileOpen(fstream& file, char name[], char mode) {
	string fileType;

	if (mode == 'r')
		fileType = "input";
	if (mode == 'w')
		fileType = "output";

	if (mode == 'r')
		file.open(name, ios::in);  //available thorugh fstream
	if (mode == 'w')
		file.open(name, ios::out);  //available through fstream;

	if (file.fail()) { //error condition 
		cout << "Error opening " << fileType << " file" << endl; 
		exit(EXIT_FAILURE);
	}
}

/*
Pre:  data is an array of strings
Post: data is in sorted order
*/
void selSort(string data[], int size) {
	int cur;
	int smallI;
	for(cur = 0; cur < size - 1; cur++) {
		smallI = findSmallest(data, cur, size);
		swap(data, cur, smallI);
	} 
}

/*
Pre:  data is an arrray of strings, cur begins the subarray under consideration
Post: returns the smallest item in the array, beginnig with cur
*/
int findSmallest(string data[], int cur, int size) {
	int smallestI = cur;
	for(int i = cur; i < size; i++)
		if(data[i] < data[smallestI]) 
			smallestI = i;
	return smallestI;
}


/*
Pre:  data is an arrray of strings, cur and idxSmallest are indices 
Post: what was in postion cur is now in position idxSmallest and vice-versa 
*/
void swap(string data[], int cur, int idxSmallest) {
	string temp = data[cur];
	data[cur] = data[idxSmallest];
	data[idxSmallest] = temp;
}
