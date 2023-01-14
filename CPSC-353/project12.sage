'''
 Name: Cole Mark Olafson and Stella Beemer
 Class: CPSC 353
 Date Submitted: May 5, 2021
 Assignment: Project 12                                                                     
 Description: This program demonstrates a functional MD2 hash function
'''

'''
pre:  message is a string determined by the user
post: returns message as bytes with padding needed for the m2 hash
'''
def padding(message):
    message_bytes = bytearray(message, 'utf-8')
    padding = 16 - (len(message_bytes) % 16)
    message_bytes += bytearray(padding for _ in range(padding))
    return message_bytes

'''
pre:  message_bytes is bytearray with padding determined by padding()
      S is the s_box determined by make_S()
post: returns message_bytes with required checksum needed for m2
'''
def checksum(message_bytes, S):
    check_sum = [0 for i in range(16)]
    N = len(message_bytes)
    L = 0
    for i in range(N // 16):
        for j in range(16):
            c = message_bytes[16*i + j]
            check_sum[j] = check_sum[j] ^^ S[c ^^ L]
            L = check_sum[j]

    message_bytes = list(message_bytes)
    message_bytes += check_sum
    return message_bytes

'''
pre:  message_bytes is bytearray with padding determined by padding()
      S is the s_box determined by make_S()
post: returns the hashed message
'''
def hash(message_bytes, S):
    X = [0 for i in range(48)]
    N = len(message_bytes) 
    for i in range(N // 16):
        for j in range(16):
            X[j + 16] = message_bytes[16*i + j]
            X[j + 32] = message_bytes[j + 16] ^^ X[j]
        t = 0
        for j in range(18):
            for k in range(48):
                t = X[k] ^^ S[t]
                X[k] = t
            t = (t + j) % 256
    
    hash_msg = []
    for i in range(16):
        hash_msg.append(chr(X[i] % 26 + 65))
    return hash_msg

'''
pre:  nothing needs to be passed in
post: returns the s_box list S determined using random digits of pi
'''
def make_S():
    S = [i for i in range(256)]
    pi_str = str(numerical_approx(pi, digits=1000))
    digits_Pi = [int(s) for s in pi_str if s != "."]

    k = 2
    while k < 257:
        j = rand(k, digits_Pi)
        tmp = S[j]
        S[j] = S[k - 1]
        S[k - 1] = tmp
        k += 1

    return S

'''
helper function for make_S()
pre:  n is the current iteration of the loop in make_S()
      digits_Pi is the list of digits of pi determined in make_S()
post: returns a pseudo-random digit based on digits of pi
'''
def rand(n, digits_Pi):
    x = next(iter(digits_Pi))
    y = 10

    if n > 10:
        x = x * 10 + next(iter(digits_Pi))
        y = 100
    if n > 100:
        x = x * 10 + next(iter(digits_Pi))
        y = 1000

    if x < (n * (y // n)):
        return x % n
    else:
        return rand(n)

'''
pre:  message is a string determined by the user
post: prints the hashed message
'''
def md2(message):
    message_bytes = padding(message)
    S = make_S()
    message_bytes = checksum(message_bytes, S)
    hashed_message = hash(message_bytes, S)
    return hashed_message