'''
Name: Cole Mark Olafson and Stella Beemer
Class: CPSC 353
Date Submitted: April 10, 2021
Assignment: Project 10                                                                     
Description: This program demonstrates the Diffie-Hellman key exchange protocol
'''

import random;

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
    g = mod(primitive_root(p), p)
    return p, g

'''
Pre: p, g are returned by param_gen
Post: Returns computed A and and variable a, as defined in class and in McAndrew
'''
def Alice(p,g):
    a = random.randint(1, p)
    A = g^a
    return A, a

'''
Pre: p, g are returned by param_gen
Post: Returns computed B and variable b as  defined in class and in McAndrew
'''
def Bob(p,g):
    b = random.randint(1, p)
    B = g^b
    return B, b

'''
Pre: p is returned by param_gen, a by Alice, and B by Bob
Post: Returns k_alice as defined in class and in McAndrew
'''
def Alice_Key(p,a,B):
    k_alice = B^a
    return k_alice

'''
Pre: p is returned by param_gen, b by Bob, and A by Alice
Post: Returns k_Bob as defined in class and in McAndrew
'''
def Bob_Key(p,b,A):
    k_Bob = A^b
    return k_Bob

def main():
    p, g = param_gen(100);
    A, a = Alice(p, g)
    B, b = Bob(p, g)
    k_alice = Alice_Key(p, a, B)
    k_bob = Bob_Key(p, b, A)
    print("shared keys: ")
    print(k_alice)
    print(k_bob)
    print("do both keys match? ", k_alice == k_bob)

main()