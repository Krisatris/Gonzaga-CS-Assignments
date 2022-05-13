'''
    Stella Beemer
    9/20/21
    Computer Security
    RSA Cracker
    This file contains the encryption and decryption functions for RSA
'''

def rsa_encrypt(plaintext, e, n):
    """RSA-encrypts the given plaintext."""
    return pow(plaintext, e, n)


def rsa_decrypt(ciphertext, d, n):
    """RSA-decrypts the given ciphertext."""
    return pow(ciphertext, d, n)
