# 42-Get_Next_Line

## Introduction

This project is about programming a function that returns a line read from a file descriptor. We will learn static variables in C.

## Mandatory Part

|Function name       |get_next_line                                                                           |
|--------------------|----------------------------------------------------------------------------------------|
|Prototype:          |`char *get_next_line(int fd);`                                                          |
|Turn in files:      |get_next_line.c, get_next_line_utils.c, get_next_line.h                                 |
|Parameters:         |fd: The file descriptor to read from                                                    |
|Return value:       |Read line: correct behavior, NULL: there is nothing else to read, or an error occurred  |
|External functions: |read, malloc, free                                                                      |
|Description:        |Write a function that returns a line read from a file descriptor                        |

- Repeated calls (e.g., using a loop) to the `get_next_line()` function should let us read the text file pointed
to by the file descriptor, one line at a time.
- The function should return the line that was read. If there is nothing else to read or if an error occurred,
it should return NULL.
- Ensure the function works as expected both when reading a file and when reading from the standard input.
- The returned line should include the terminating \n character, except if the end of file was reached and does not end with a \n character.
- The header file get_next_line.h must at least contain the prototype of the `get_next_line()` function.
- All the helper functions can be added in the get_next_line_utils.c file.

- Add this option to the compiler call: `-D BUFFER_SIZE=n`. It will define the buffer size for `read()`.
- We must be able to compile this project with and without the `-D BUFFER_SIZE` flag in addition to the usual flags. We can choose the default value of our choice
- We will compile the code as follows (a buffer size of 42 is used as an example):
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`
- We consider that `get_next_line()` has an undefined behavior if the file pointed to by the file descriptor changed since the last call whereas `read()` didn’t reach the end of file.
- We also consider that `get_next_line()` has an undefined behavior when reading a binary file. However, we can implement a logical way to handle this behavior if we want to.
- `lseek()` and global variables are forbidden.
