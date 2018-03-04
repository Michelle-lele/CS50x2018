# Questions

## What's `stdint.h`?

stdint.h is a header file in the C standard library introduced in the C99 standard library
to allow programmers to write more portable code by providing a set of typedefs that
specify exact-width integer types, together with the defined minimum and maximum
allowable values for each type, using macros. This header is particularly useful for
embedded programming which often involves considerable manipulation of hardware specific
I/O registers integer data of fixed widths, specific locations and exact alignments.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The C99 standard includes definitions of several new integer types to enhance the portability of programs.
The already available basic integer types were deemed insufficient,
because their actual sizes are implementation defined and may vary across different systems.

uint8_t - Unsigned int data type of size 8 bytes.
uint32_t - Unsigned int data type of size 32 bytes.
int32_t - Signed int data type of size 32 bytes.
uint16_t - Unsigned int data type of size 16 bytes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 8
DWORD - 32
LONG - 32
WORD - 16

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

66 & 77

## What's the difference between `bfSize` and `biSize`?

bfSize is the size, in bytes, of the bitmap file.
biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

In line 24 NULL will be returned if the file doesn't exist
in line 32 NULL will be returned if error is returned while attempting to write-
for example if we have no permissions to write the file

## Why is the third argument to `fread` always `1` in our code?

We want to read only once from BITMAPFILEHEADER

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

padding = (4 - (3*3)%4) %4
Answer is 3

## What does `fseek` do?

Use fseek when you want to change the offset of the file pointer fp.
This is an extremely useful tool. Normally, when reading in from a file,
the pointer continues in one direction, from the start of the file to the end.
fseek, however, allows you to change the location of the file pointer.

offset refers to how many bytes you want to change the current position of the file pointer fp.
You can go both forward with positive numbers, or backward with negative numbers.

## What is `SEEK_CUR`?

It is constant used in fseek that moves file pointer position to given location.
