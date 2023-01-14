'''
 Name: Stella Beemer
 Class: CPSC 353
 Date Submitted: January 29, 2021
 Assignment: Project 1                                                                     
 Description: This program encrypts and decrtpys a plain text via a transposition cipher
'''

import string
import random

'''
Generates a random key that maps the alphabet to another random letter
returns: key_str that maps alphabet
'''
def key_gen():
    seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    key_str = ''.join(random.sample(seed, 26))
    return key_str

'''
Encrypts plain text string using key from key_gen()
plain_txt: string to be encrypted, key: key generated from key_gen()
returns: encrypted string
'''
def encrypt(plain_txt, key):
    perm = [ord(x) - 64 for x in key]
    plain_num = str21st(plain_txt)
    encrypt_num = [perm[plain_num[i]] - 1 for i in range(len(plain_txt))]
    encrypt_txt = lst2str(encrypt_num)
    print("encrypt_txt is: " + encrypt_txt)
    return encrypt_txt

'''
Turns strings into list of corresponding ord values
s: string to be converted
returns: list of ord values
'''
def str21st(s):
    return [ord(x) - 65 for x in s]

'''
Turns list of ord values into corresponding string of letters
lst: list of ord values
returns: string of letters
'''
def lst2str(lst):
    return ''.join([chr(int(x) + 65) for x in lst])

'''
decrypts plain text string using key from key_gen()
plain_txt: string to be decrypted, key: key generated from key_gen()
returns: decrypted string
'''
def decrypt(cipher_txt, key):
    perm = [ord(x) - 64 for x in key]
    inv_perm = Permutation(perm).inverse()
    decrypt_num = str21st(cipher_txt)
    decrypt_num = [inv_perm[decrypt_num[i]] - 1 for i in range(len(cipher_txt))]
    decrypt_txt = lst2str(decrypt_num)
    print("decrypt_txt is: " + decrypt_txt)
    return decrypt_txt

def main():
    plain_txt = "XJKTITNF"
    key = key_gen()
    encrypt_txt = encrypt(plain_txt, key)
    plain_txt = "YJKTITNF"
    encrypt_txt = encrypt(plain_txt, key)
    plain_txt = "YKKTITNF"
    encrypt_txt = encrypt(plain_txt, key)
    plain_txt = "YKLTITNF"
    encrypt_txt = encrypt(plain_txt, key)
    #decrypt(encrypt_txt, key)

main()
