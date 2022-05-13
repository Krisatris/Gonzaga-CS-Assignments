'''
    Stella Beemer
    9/20/21
    Computer Security
    RSA Cracker
    This file contains the function to run the RSA encrypt, decrypt, and crack
    functions (including the timing functions)
'''

from rsa_encryption import rsa_encrypt, rsa_decrypt
from rsa_cracker import crack_rsa, crack_rsa_brute_force
from timeit import default_timer as timer

class RsaTestResult:
    """
    Members:

    d (int): The private exponent obtained by cracking RSA.
    ciphertext (int): The ciphertext obtained by encrypting the given plaintext with the given public key {e, n}.
    plaintext (int): The plaintext obtained by decrypting the ciphertext with the cracked d value.
    fast_time (float): The time in seconds taken by the fast cracking algorithm.
    brute_force_time (float): The time in seconds taken by the brute-force cracking algorithm.  (This will be None if brute force was not used.)
    """

    def __init__(self, d, plaintext, ciphertext, fast_time, brute_force_time):
        self.d = d
        self.plaintext = plaintext
        self.ciphertext = ciphertext
        self.fast_time = fast_time
        self.brute_force_time = brute_force_time


def test_rsa(key_size, n, e, plaintext):
    """
    Tests RSA encryption and cracking with the given values.
    Returns a fully populated RsaTestResult object (except RsaTestResult.brute_force_time, which will be None for any keys larger than 55 bits).
    """
    # encrypt the plaintext and obtain cipher text
    ciphertext = rsa_encrypt(plaintext, e, n)

    # find d and time it takes to crack rsa quickly
    start = timer()
    d = crack_rsa(e, n)
    fast_time = timer() - start

    # decrypt ciphertext using d from above
    decrypt_plaintext = rsa_decrypt(ciphertext, d, n)

    # find brute force time if key_size is 55 bits or less
    if(key_size < 56): 
        start_brute = timer()
        d_brute = crack_rsa_brute_force(e, n)
        brute_time = timer() - start_brute
        #print("brute force d = ", d_brute) - used this to confirm my brute function works correctly
    else:
        brute_time = 0
    
    return RsaTestResult(d, decrypt_plaintext, ciphertext, fast_time, brute_time)
