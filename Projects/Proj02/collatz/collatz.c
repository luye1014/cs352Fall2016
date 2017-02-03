/*
 * File: collatz.c
 * Author: Lu Ye.
 * Purpose: This class will run the recursive function (3n + 1 if odd,
 * n/2 if even) until reach a number which is less than or equal to the starting number.
 */
#include <stdio.h>
#include <stdlib.h>

/*
* collatz(int x, int startingNum) -- returns a list of the numbers that follow it 
* in the sequence. It assumes that x is your input and startingNum as a reference which 
* defines the end of recursive function. If meet a number which is a odd number --> 3x+1
* otherwise, x/2 to get a new number. Keep traking until reach a number which is less than 
* or equal to the startingNum.
*/
int collatz(int x, int startingNum){
	// check if your input is a odd number
	if(x % 2 != 0){ 
		x = 3 * x + 1;
		while(x > startingNum){
		printf(" %d", x);
		return collatz(x,startingNum);
		}
	}
	// otherwise, the input is an even number
	else{
		x = x/2;
		while(x > startingNum){
		printf(" %d", x);
		return collatz(x,startingNum);
		}
	}
	printf(" %d\n", x);
	return 0;
}
 
/*
* main() -- main function which is generate the whole program. We will check whether the input
* is available or not here. The input must be a positive integer, which is greater than 0.
* A program that executes without encountering any errors should indicate this with a return value 
* (exit status) of 0. If an error is encountered during execution, this should be indicated by a non-zero 
* return value (exit status). The precise exit status in this case should be determined 
* from the assignment specification; if no error exit status is explicitly specified in 
* the assignment spec, use the value 1.
*/
int main(){
	int input, check, error;
	while((check = scanf("%d", &input)) != EOF){
		// check if the input is a non-integer. Program print error and 
		// exit if the input cannot be read as an integer
		if(check != 1){
			fprintf(stderr, "ERROR: An element on the input stream is not an integer.\n" );
			return 1;
		}
		// check if the input is a non-positive integer. Program should not exit
		// if your input is a non-positive input, but print the error
		if(input <= 0){
			fprintf(stderr, "ERROR: The input %d cannot be tested, because it is non-positive.\n", input);
			error = 1;
		}
		else{
			printf("%d:", input);
			collatz(input,input);
		}
	}
	return error;
}

