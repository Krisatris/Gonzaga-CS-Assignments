'''
Cole Olafson and Stella Beemer
Project6 Sage Code for questions 1-2 and 6-8
'''

import random

def main():

    #problem 1, 2
    p = 11
    q = 13
    e = 17
    m = 99
    n = p * q
    phi = (p - 1)*(q - 1)
    e = ZZ.random_element(phi)
    while gcd(e, phi) != 1:
        e = ZZ.random_element(phi)
    bezout = xgcd(e, phi)
    d = Integer(mod(bezout[1], phi))
    print("d for 1 is: ", d)
    
    #encrypt m for 2A
    encrypt = power_mod(m, e, n)
    print("encrypted m is: ", encrypt)

    #decrypt for 2B
    decrypt = power_mod(encrypt, d, n)
    print("decrypt is: ", decrypt)
    
    # function used to generate nums for problem 6 & 7
    #highestPrimes()

    #problem 8
    decrypt(32027765990299027162150892550886239549296091878738047455334362661345559872662809370835197541763334314984066626219269537)


def highestPrimes():
    lowerBound = 2 ** 100
    upperBound = 2 ** 200
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

    print("public key n: ", n, ", e: ", e)
    print("private key p: ", p, ", q: ", q, ", d: ", d)

def decrypt(cipher_txt):
    d = 129469923348147885545630112028241213719658515016127234355250399712206972535921986959339680557507918262749701719968904797
    n = 166066992554537626488471016854404428587182899266808770584421555998663010283668328380427366319755667933868184047642336221
    cipher_num = power_mod(cipher_txt, d, n)
    print(num_to_txt(cipher_num))

#num_in is a decimal integer composed as described above 
def num_to_txt(num_in):
  #returns the list described above 
  msg_idx = num_in.digits(256)
  #maps each index to its associated character in the ascii table 
  m = map(chr,msg_idx)
  #transforms the list to a string
  m = ''.join(m)
  return m

main()