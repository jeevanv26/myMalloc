Properties for my malloc program to be correct:
1. malloc function allocates memory for request byte size or lets user know that their is no more heap space 
2. free function frees allocated memory and also checks for multiple error cases such as input address is not one returned my malloc, input address isn't the start of a data chunk, and memory at address is already freed
3. free function handles coalescing of adjacent free chunks
4. initialization stage is done in malloc 

The first program in memgrind.c is done as the instructions said so.

My second program: checks to see if coalescing works on a little bigger chunks than we did in the first program. Also, the free error cases were tested

My third program: this test makes sure that if the heap runs out of space, there is an error message.


