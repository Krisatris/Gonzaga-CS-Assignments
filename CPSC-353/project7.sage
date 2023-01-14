'''
 Name: Cole Mark Olafson and Stella Beemer
 Class: CPSC 353
 Date Submitted: March 28, 2021
 Assignment: Project 7                                                                     
 Description: This program demonstrates a functional RSA Cipher
 Comments: because the decrypt function needs the chunked ints to be in the same groupings
           they were in when encrypted to accurately decrypt, the encrypted text is returned
           as a list of ints. a utility print function is included to print the encrypted text
'''

import random
import math

'''
Pre:  size is an exponent, as in 2^size.
Post: program returns the RSA public key,(n,e)  and the private key, d. 
'''
def key_gen(size):
    lowerBound = 2 ** size
    upperBound = 2 ** (size + 100)
    p = random.randint(lowerBound, upperBound)
    q = random.randint(lowerBound, upperBound)
    p = next_prime(p)
    q = next_prime(q)
    n = p * q

    phi = (p - 1)*(q - 1);
    e = ZZ.random_element(phi)
    while gcd(e, phi) != 1:
        e = ZZ.random_element(phi)

    bezout = xgcd(e, phi)
    d = Integer(mod(bezout[1], phi))

    return n, d, e

'''
Pre:  plain_text is a text string, chosen by the user.  
      “Than you can understand,” is an example.  There are no limits on its size.  
      e, n are returned by key_gen 
Post: returns the encryption of plain_text, using the RSA algorithm.
'''
def encrypt(plain_text, e, n):
    m = txt_to_num(plain_text)
    chunks = int(math.log10(n))
    lst = split_str(m, chunks)
    for i in range(len(lst)):
        lst[i] = power_mod(lst[i], e, n)
    return lst

'''
Pre: d, n are returned by key_gen.  c is returned by encrypt.
Post: returns the decryption of the cipher_text, using the RSA algorithm
'''
def decrypt(c, d, n):
    for i in range(len(c)):
        c[i] = txt_to_num(c[i])
        c[i] = power_mod(c[i], d, n)
        c[i] = num_to_txt(c[i])
    x = "".join(c)
    return x

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

'''
pre:  lst_m is the list of the encrypted message
post: prints both the num and txt representations of the encrypted text
'''
def print_encrypted_m(lst_m):
    print("encrypted text as nums:")
    for i in range(len(lst_m)):
        print(lst_m[i])
    print("encrypted text as txt:")
    for i in range(len(lst_m)):
        lst_m[i] = num_to_txt(lst_m[i])
    print("".join(lst_m))

def main():
    n, d, e = key_gen(100)
    e_message = encrypt("xjktitnf", e, n)
    print_encrypted_m(e_message)
    e_message = encrypt("yjktitnf", e, n)
    print_encrypted_m(e_message)
    e_message = encrypt("ykktitnf", e, n)
    print_encrypted_m(e_message)
    e_message = encrypt("ykltitnf", e, n)
    print_encrypted_m(e_message)

    #d_message = decrypt(e_message, d, n)
    #print(d_message)

main()