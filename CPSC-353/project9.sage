'''
Name: Cole Mark Olafson and Stella Beemer
Class: CPSC 353
Date Submitted: April 10, 2021
Assignment: Project 9                                                                     
Description: This program demonstrates a functional El Gamel Cipher
'''

import random;
import math;

'''
Pre:  size is an exponent, as in 2^size.
Post: program returns El Gamal parameters, 
      large prime, p and primitive root, a mod p as defined in class and in McAndrew
'''
def param_gen(size):
    lowerBound = 2 ** size
    upperBound = 2 ** (size + 100)
    p = random.randint(lowerBound, upperBound)
    p = next_prime(p)
    a = mod(primitive_root(p), p)
    return p, a

'''
Pre:  p and a are returned by param_gen
Post: returns private key, A, and public key, B as defined in class and in McAndrew
'''
def key_gen(p,a):
    A = random.randint(1, p)
    B = a^A
    return A, B

'''
Pre:  a and p are returned from param_gen, B from key_gen.  plaintext is a text string.  Its numerical 
      equivalent (see “Ancillary Functions,” below) must be less than p.
Post: returns the encryption of plaintext C1 and C2, as defined in class and in McAndrew.
'''
def encrypt(plaintext, a, p, B):
    k = random.randint(2**10, 2**50)
    C1 = power_mod(a, k, p)
    C2 = []
    m = txt_to_num(plaintext)
    chunks = int(math.log10(p))
    lst = split_str(m, chunks)
    for i in range(len(lst)):
        C2.append(lst[i] * power_mod(B, k, p) % p);
    return C1, C2

'''
Pre:  C forms the ciphertext returned from encrypt (chunked in list), p is returned by gen_param,   A is the private key 
      returned by key_gen, all as defined in class and in McAndrew.
Post: returns the text string decryption of the ciphertext, using the El Gamal  algorithm
'''
def decrypt(C1, C2, p, A):
    m = []
    for i in range(len(C2)):
        m.append(power_mod(C1, p - 1 - A, p) * C2[i] % p)
        m[i] = num_to_txt(Integer(m[i]))
    return "".join(m)

#Converts a decimal digit sequence to a string
#msg_in is an int
def num_to_txt(num_in):
    #returns the list described above 
    msg_idx = num_in.digits(256)
    #maps each index to its associated character in the ascii table 
    m = map(chr,msg_idx)
    #transforms the list to a string
    m = ''.join(m)
    return m

#Converts a string to a decimal digit sequence
#msg_in is a string
def txt_to_num(msg_in):      
    #transforms string to the indices of each letter in the 8-bit ASCII table
    #ex: "AB" becomes [65,66]
    msg_idx = list(map(ord,msg_in))

    #The integers in the list, since they are ASCII, are in the range 0..255
    #These are treated, collectively, as a base 256 integer, but from left to right
    #rather than right to left
    #This sequence of integers is converted to base 10 
    #ex: [65,66] = 65*256^0 + 66*256^1 = 16961
    num = ZZ(msg_idx,256)
    return num

'''
pre:  seq is the int to split into smaller chunks, chunk is how many digits should be in
      each chunk
post: returns a list with the smaller chunks as entries
'''
def split_str(seq, chunk):
    lst = []
    divide = 10 ** chunk
    if(divide == 1):
        print("0 entered as chunk, incrementing to 1")
        divide = 10
    while(seq > 0):
        curr = seq % divide
        lst.insert(0, curr)
        seq = seq // divide
    return lst

def main():
    p, a = param_gen(100)
    A, B = key_gen(p, a)
    C1, C2 = encrypt("yeeeeeeeeeeeeeeeeeeeeeeet", a, p, B)
    print("encrypted key is: ", [C1, C2])
    print(decrypt(C1, C2, p, A))

main()