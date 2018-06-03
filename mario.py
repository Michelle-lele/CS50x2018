from cs50 import get_int

#if height's not positive number or less than 24, promp user
while True:
    #get user input for pyramid height
    print("Height: ", end = '')
    height = get_int()
    if height >= 0 and height <= 23:
        break
row = 1
for row in range(height):
    #print as much spaces as needed depending on specified height
    print(" " * (height - row - 1), end = '')
    print("#" * (row + 1), end = '')
    print("  ", end = '')
    print("#" * (row + 1))
