# Matrix Operations with Multithreading

## Overview

This project provides a C program to perform matrix operations using multithreading. The program reads multiple matrices from standard input, performs a specified matrix operation (`ADD`, `MUL`, `AND`, `OR`), and prints the result. The operations are executed in parallel using POSIX threads (pthreads), making use of multiple threads to handle pairs of matrices concurrently.

## Matrix Format

Matrices are read from standard input in the following format:

(rows,cols
,element2,...,elementN)

javascript
Copy code

Where `rows` and `cols` specify the dimensions of the matrix, and `element1, element2, ..., elementN` specify the matrix elements in row-major order. Complex numbers are supported in the form `a+bi` or `a-bi`.

### Example

A 2x2 matrix with all elements as `1` can be represented as:

(2,2:1,1,1,1)

markdown
Copy code

## Operations

The program supports the following operations:

- **ADD**: Matrix addition
- **MUL**: Matrix multiplication
- **AND**: Element-wise bitwise AND (operates on matrices with binary values, i.e., 0 or 1)
- **OR**: Element-wise bitwise OR (operates on matrices with binary values, i.e., 0 or 1)

## Usage

1. Compile the program with `gcc -o Ex3q3a Ex3q3a.c -lpthread`.
2. Run the program and provide matrices followed by the operation you want to perform:

./Ex3q3a

css
Copy code

Example input for adding matrices:

(2,2:1,1,1,1)
(2,2:2,2,2,2)
ADD

css
Copy code

Example input for matrix multiplication:

(2,2:1,0,0,1)
(2,2:0,1,1,0)
MUL

vbnet
Copy code

End the input with `END` to indicate the end of matrices.

## Files

- **Ex3q3a.c**: Source code file containing the implementation of matrix operations and multithreading.
- **run_me4.sh**: Shell script to automate the build and run process.
- **README.md**: This readme file with project overview and instructions.

## Compiling and Running

To compile the program:

```bash
gcc -o Ex3q3a Ex3q3a.c -lpthread
To run the program:

bash
Copy code
./Ex3q3a
Provide matrices in the specified format and enter the operation to perform. End the input with END.

Example
bash
Copy code
$ ./Ex3q3a
(2,2:1,1,1,1)
(2,2:1,1,1,1)
MUL
Output
makefile
Copy code
(2,2:1,1,1,1)
Notes
The AND and OR operations are intended for matrices with binary values (0 or 1).
Ensure that the number of matrices provided is even, as the program processes pairs of matrices.
The program uses threads to perform matrix operations concurrently for efficiency.
