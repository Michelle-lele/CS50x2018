'''
Implement a program that encrypts messages using Vigenère’s cipher, per the below.

$ ./vigenere ABC
plaintext:  HELLO
ciphertext: HFNLP

'''
import sys
from cs50 import get_string

# accepts only 2 command prompt arguments, first is the program itself, second should be alphabetical key
if len(sys.argv) != 2:
    print("Usage: ./vigenere k")
    sys.exit(1)

# check if string contains only alphabetical symbols
if sys.argv[1].isalpha() == False:
    print("Error! Please provide string of only alphabetical symbols")
    sys.exit(1)

keys = sys.argv[1]
key = []

# convert characters to their index number A,a = 0, Z,z = 25
global counter
counter = 0

for c in keys:
    if c.isupper() == True:
        key.append(ord(c) - ord('A'))
        counter += 1
        # print(key)
    else:
        key.append(ord(c) - ord('a'))
        counter += 1
        # print(key)

# prompt user for plaintext
plaintext = get_string("plaintext: ")
print("ciphertext: ", end='')
# loops for each character in the plaintexts provided
counter = 0

# convert plaintext to cyphertext and print
for c in plaintext:
    # ensure that key wraps
    if counter > (len(keys) - 1):
        counter = 0

    # check if the symbol is a character
    if c.isalpha() == True:
        # check if character is uppercase
        if c.isupper():
            letter = ((ord(c) - ord("A")) + key[counter]) % 26
            # print(letter)
            c = chr(letter + ord('A'))
            # print(counter)
            counter += 1
            print(c, end='')
        else:
            letter = ((ord(c) - ord("a")) + key[counter]) % 26
            # print(letter)
            c = chr(letter + ord('a'))
            # print(counter)
            counter += 1
            print(c, end='')
    else:
        print(c, end='')

print()