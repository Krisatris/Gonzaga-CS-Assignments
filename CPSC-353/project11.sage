'''
 Name: Cole Mark Olafson and Stella Beemer
 Class: CPSC 353
 Date Submitted: April 20th, 2021
 Assignment: Project 7                                                                     
 Description: This program demonstrates a functional sDes Cipher
'''

from sage.crypto.block_cipher.sdes import SimplifiedDES

def main():
    sdes = SimplifiedDES()
    K = "1010000010"
    P = "01010101"
    print(sdes.encrypt(sdes.string_to_list(P), sdes.string_to_list(K)))

main()