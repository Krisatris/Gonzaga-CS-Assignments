'''
    Stella Beemer
    9/20/21
    Computer Security
    RSA Cracker
    This file contains all of the test cases for the RSA Cracker assignment
'''

from test_rsa import test_rsa

def main():
    """
    Displays the results of the test cases using the following format.
    If the expected d value is unknown, displays "Expected: Unknown".
    If the key is too large for the brute-force algorithm, instead of displaying the time, displays "Could not crack the key using brute force.".
    """
    
    print("************************ Test Case 1 - 6 bits ************************\n")

    RsaResult = test_rsa(6, 33, 7, 11)
    
    print("Inputs:")
    print("        n: 33")
    print("        e: 7")
    print()
    print("plaintext:")
    print("        Expected: 11")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 11")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: 3")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 2 - 6 bits ************************\n")

    RsaResult = test_rsa(6, 55, 3, 22)
    
    print("Inputs:")
    print("        n: 55")
    print("        e: 3")
    print()
    print("plaintext:")
    print("        Expected: 22")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 33")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: 27")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 3 - 7 bits ************************\n")

    RsaResult = test_rsa(7, 77, 17, 33)
    
    print("Inputs:")
    print("        n: 77")
    print("        e: 17")
    print()
    print("plaintext:")
    print("        Expected: 33")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 66")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: 53")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 4 - 33 bits ************************\n")

    RsaResult = test_rsa(33, 8093802337, 5292724727, 44)
    
    print("Inputs:")
    print("        n: 8093802337")
    print("        e: 5292724727")
    print()
    print("plaintext:")
    print("        Expected: 44")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 91365999")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: 2418060515")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 5 - 48 bits ************************\n")

    RsaResult = test_rsa(48, 193525589347327, 65537, 55)
    
    print("Inputs:")
    print("        n: 193525589347327")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 55")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 15874205423572")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 6 - 52 bits ************************\n")

    RsaResult = test_rsa(52, 2547701629085297, 65537, 66)
    
    print("Inputs:")
    print("        n: 2547701629085297")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 66")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 1147658972741083")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 7 - 55 bits ************************\n")

    RsaResult = test_rsa(55, 26205577898256853, 65537, 77)
    
    print("Inputs:")
    print("        n: 26205577898256853")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 77")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 11958464572474898")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Brute-force cracking time:      ", RsaResult.brute_force_time, " seconds.\n")


    print("************************ Test Case 8 - 60 bits ************************\n")

    RsaResult = test_rsa(60, 588035197746923243, 65537, 88)
    
    print("Inputs:")
    print("        n: 588035197746923243")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 88")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 464119776098692961")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Could not crack the key ysing brute force.\n")


    print("************************ Test Case 9 - 70 bits ************************\n")

    RsaResult = test_rsa(70, 962650700322326636233, 65537, 99)
    
    print("Inputs:")
    print("        n: 962650700322326636233")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 99")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 830909963088407253419")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Could not crack the key using brute force.\n")


    print("************************ Test Case 10 - 75 bits ************************\n")

    RsaResult = test_rsa(75, 23800004200970185016117, 65537, 1010)
    
    print("Inputs:")
    print("        n: 23800004200970185016117")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 1010")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 7636433958731833065843")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Could not crack the key ysing brute force.\n")


    print("************************ Test Case 11 - 77 bits ************************\n")

    RsaResult = test_rsa(77, 122584996302390602628737, 65537, 1111)
    
    print("Inputs:")
    print("        n: 122584996302390602628737")
    print("        e: 65537")
    print()
    print("plaintext:")
    print("        Expected: 1111")
    print("        Actual:  ", RsaResult.plaintext)
    print("ciphertext:")
    print("        Expected: 41231507207611791000091")
    print("        Actual:  ", RsaResult.ciphertext)
    print("d:")
    print("        Expected: Unknown")
    print("        Actual:  ", RsaResult.d)

    print("Cracking time:                  ", RsaResult.fast_time, " seconds.")
    print("Could not crack the key ysing brute force.\n")
  
    return


if __name__ == "__main__":
    main()
