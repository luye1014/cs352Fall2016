/**
 * Author: LU YE
 * File: scanList.c
 * CSC352 proj04
 * In this program, you will read in an array of integers. You will then read in a
 * series of other integers; for each integer you read, you will count how many
 * times it showed up in the original array.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * void printArray(int*, int):
 * helper function for main method. Give the array that you have deal with 
 * and then you print them all.
 * 
 */
void printArray(int *ptr, int size){
	printf("Comparison array (%d elements):", size);
	int i = 0;
	for (i = 0; i < size; i++){
		printf(" %d", ptr[i]);
	}
	printf("\n");
}

/**
 * int mySearch(int *, int, int)
 * helper function that you can put in a array of integer that you want to search for and 
 * put a integer to see how many times it shower up. Return the count.
 * 
 */
int mySearch(int *ptr, int size, int toFind){
	int i = 0;
	int count = 0;
	for (i = 0; i < size; i++){
		if(ptr[i] == toFind){
			count++;
		}
	}
	return count;
}

/**
 * int main():
 * main function to generate the whole program, you will see the error message handlled in 
 * main function. 1) When your first input is not numeric than send a error message and exit.
 * 2) if your first input is negative number than send a error message and exit.
 * 3) if you enter the first number as your array size successfully. Then the numbers you read 
 * is not equal or bigger than the size. Then send a error message and exit.
 */
int main(){
	int input, status;
	int sizeToMalloc = 0;
	int count = 0;
	int sizeOfArray = 0;
	int *array = NULL;

	while((status = scanf("%d", &input))!=EOF){
		if(status!= 1){
			fprintf(stderr, "ERROR: Could not read the array-size input.  rc=0\n");
			return 1;
		}
		else{ // if your first input is numeric, then...
			if(count == 0){ // consider about the first integer you input
				if(input < 0){ // if your first is negative, send message and exit
					fprintf(stderr, "ERROR: The array-length parameter is negative.  arrLen=%d\n", input);
					return 1;
				}
				else{ // otherwise, put your first input as size
					sizeToMalloc = input;
					array = malloc(sizeToMalloc * sizeof(int));
					count++;
					if(sizeToMalloc == 0){ // if size=0, no matter what you read as the following, the count is always 0
						printf("Comparison array (0 elements):\n");
					}
				}
			}else{ // starting from the second input you read
				if(count <= sizeToMalloc){ // put your integer into array unitil the numbers reach the size
					array[sizeOfArray] = input;
					sizeOfArray++;
					if(count==sizeToMalloc){
						printArray(array, sizeToMalloc);
					}

				}
				else{ // otherwise, compare
					int result = mySearch(array, sizeOfArray, input);
					printf("Number: %d count=%d\n", input, result);
				}
				count++;
			}
		}
	}
	// check if the numbers you input is equal or bigger than the size of array after end of file.
	if (count <= sizeToMalloc){
		fprintf(stderr, "ERROR: Could not read element %d into the array.  rc=-1\n", count);
		return 1;
	}
	return 0;
}

/**
 * end
 */
