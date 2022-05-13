'''
    Stella Beemer
    9/20/21
    Computer Security
    RSA Cracker
    This file contains the fast crack and brute force crack for RSA
'''

from factor_int_with_sympy import factor_int_with_sympy
from inverse_mod import inverse_mod
from math import sqrt

def crack_rsa(e, n):
    """
    Returns the private exponent for the given RSA public key.
    It cracks the encryption using a sophisticated factorization algorithm.
    """
    p, q = factor_int_with_sympy(n)
    phi = (p - 1) * (q - 1)
    d = inverse_mod(e, phi)
    return d


def crack_rsa_brute_force(e, n):
    """
    Returns the private exponent for the given RSA public key.
    It cracks the encryption using brute force.
    """
    primeList = filter(isPrime, range(2, int(sqrt(n))))
    q = -1
    for p in primeList:
        if((n % p) == 0):
            q = n // p
            if(isPrime(q)):
                break;

    if(q != -1):
        phi = (p - 1) * (q - 1)
        d = inverse_mod(e, phi)
    else:
        d = 0
            
    return d

def isPrime(num):
    flag = False
    for i in range(2, int(sqrt(num)) + 1):
        if (num % i == 0):
            flag = True
            break

    if (not flag):
        return True
        
    return False
