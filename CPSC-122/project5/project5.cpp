/*
Class: CPSC 122-02
Team Member 1: Stella Beemer
Team Member 2: No one
GU Username: sbeemer2
Submitted By: Stella Beemer
File Name: project5.cpp 
Program creates a C-String class with
        constructor, destructor, display, 
        copy, length, isEqual, find, and concat
To Build: g++ project5.cpp project5Tst.cpp
To Execute: ./a.out test1 test2 isEqualTst copyTst findTst concatTst
*/
#include <iostream>
using namespace std;

#include "project5.h"

/*
Pre:  strIn is a null-terminated array of characters
Post: An instance of Mystring is created and set to the contents of strIn
*/ 
MyString::MyString(char const* strIn) {
    //determine the length of MyString instance
    length = 0;
    while(strIn[length] != '\0')
        length++;

    //dynamically allocate memory for MyString instance
    str = new char[length + 1];

    //copy contents of strIn to MyString instance
    int i = 0;
    while(i < length) {
        str[i] = strIn[i];
        i++;
    }
    str[i] = '\0';
}

/*
Pre:  An instance of MyString exists 
Post: Invoked automatically when a static instance of MyString 
      goes out of scope. Invoked when a dynamic instance of MyString
      is deleted.  
*/ 
MyString::~MyString() {
    delete []str;
}

/*
Pre:  An instance of MyString exists
Post: Contents of the instance of myString is displayed on the screen
*/ 
void MyString::myDisplay() {
    for (int i = 0; i < length; i++)
        cout << str[i];
    cout << endl;
}

/*
Pre:  An instance of MyString exists whose length <= length of strIn
Post: The contents of strIn overwrites the contents of the instance
      of MyString pointed to by the member variable str.  str is 
      terminated by the null character.   
*/
void MyString::myStrcpy(char const* strIn){
    int strInLength = 0;
    while(strIn[strInLength] != '\0')
        strInLength++;

    char* temp = new char[strInLength + 1];
    int i = 0;
    while(i < strInLength) {
        temp[i] = strIn[i];
        i++;
    } 

    delete [] str;
    str = temp;
    temp = NULL;
    length = strInLength;
}

/*
Pre:  An instance of MyString exists
Post: Returns the number of characters, excluding the null character
      in MyString. 
*/
int MyString::myStrlen() {
    return length;
}

/*
Pre:  An instance of MyString exists. strIn is a null-terminated
      string.
Post: Returns true if the strings are equivalent, false otherwise 
*/
bool MyString::isEqual(char const* strIn) {
    int strInLength = 0;
    int i = 0;
    while(strIn[i] != '\0') {
        strInLength++;
        i++;
    }
    if(strInLength != length) 
        return false;

    for(int j = 0; j < length; j++) {
        if(strIn[i] != str[i]) 
            return false;
    }
    return true;
}

/*
Pre:  An instance of MyString exists
Post: If strIn is a substring of the instance of MyString, returns
      the index of its starting positon, -1 otherwise
*/
int MyString::find(char const* strIn) {
    int strInLength = 0;
    while(strIn[strInLength] != '\0')
        strInLength++;

    int startIndex = -1;
    int i = 0;
    
    while(startIndex == -1 && i < length) {
        if(str[i] == strIn[0]) {
            startIndex = i;
            int j = startIndex;
            i = 0;
            while(j < (startIndex + strInLength) && startIndex != -1) {
                if(str[j] != strIn[i])
                    startIndex = -1;
            i++;
            j++;
            }
        }
        i++;
    }
    return startIndex;
    /*
    int j = startIndex;
    i = 0;
    if(startIndex != -1) {
        while(j < (startIndex + strInLength)) {
            if(str[j] != strIn[i])
                return -1;
            i++;
            j++;
        }
    }
    return startIndex;
    */
}

/*
Pre:  An instance of MyString exists. strIn is a null-terminated string
Post: strIn is concatenated with the instance of MyString.  Ex.
      MyString is ABC. strIn is DEF.  MyString is still a null-terminated
      string, but contains: ABCDEF. 
*/
void MyString::concat(char const* strIn) {
    int strInLength = 0;
    while(strIn[strInLength] != '\0')
        strInLength++;

    char* temp = new char[length + strInLength + 1];
    int i = 0;
    while(i < length) {
        temp[i] = str[i];
        i++;
    }
    while(i >= length && i < (length + strInLength)) {
        temp[i] = strIn[i - length];
        i++;
    }
    temp[i] = '\0';

    delete [] str;
    str = temp;
    temp = NULL;
    length += strInLength;
}