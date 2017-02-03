/**
 * Author: LU YE
 * File: scheduling.c
 * CSC352 proj04
 * In this program, you will look for overlaps in the schedule for several people, and
 * build a report about what times they might or might not have available. This
 * will require that you allocate an array of integers, to keep information about
 * each of the slots.
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * void printAverage(int *array, int sizeOfArray):
 * helper method to find the average number after end of file
 */
void printAverage(int *array, int sizeOfArray){
	double sum = 0;
	double result;
	int i;
	for(i=0; i<sizeOfArray;i++){ // go through each numbers in a array you inpy
		sum += array[i]; // add them together as sum
	}
	result = sum/sizeOfArray; // calculate the average
	printf("average: %.2f\n", result);
}

/**
 * void printArray(int *ptr, int size):
 * helper method to print array---> the format is ----> the size of array: slot slot slot...
 * slots are all initiallized zero
 */
void printArray(int *ptr, int size){
	printf("%d:", size);
	int i = 0;
	for (i = 0; i < size; i++){
		printf(" %d", ptr[i]);  //print the current number at that slot
	}
	printf("\n");
}

/**
 * int getMinimum(int *array, int sizeOfArray):
 * helper method to get the minimum number in array
 */
int getMinimum(int *array, int sizeOfArray){
	int i, minValue;
	minValue = array[0];
	for(i = 1; i < sizeOfArray; i++){
		if(array[i] < minValue){
			minValue = array[i];  // go through a array and assign the minimum number to minValue
		}
	}
	return minValue;
}

/**
 * void printMinimum_Slots(int*, int):
 * Find all of minimum slots in a array and print them all
 */
void printMinimum_Slots(int *array, int sizeOfArray){
	int i, minValue;
	printf("minimum-slots:");
	minValue = getMinimum(array, sizeOfArray); // get the minValue from getMinimum function
	for(i=0; i<sizeOfArray;i++){
		if(array[i]==minValue){ // go through array to find if the number is equal to minValue
			printf(" %d", i);   // print the location
		}
	}
	printf("\n");

}

/**
 * int getMaximum(int *array, int sizeOfArray):
 * helper method to get the maximum number in array, similar to getMaximum
 */
int getMaximum(int *array, int sizeOfArray){
	int i, maxValue;
	maxValue = array[0];
	for(i = 1; i < sizeOfArray; i++){
		if(array[i] > maxValue){
			maxValue = array[i];
		}
	}
	return maxValue;
}

/**
 * void printMaximum_Slots(int*, int):
 * Find all of maximum slots in a array and print them all, similar to printMaximum_Slots
 */
void printMaximum_Slots(int *array, int sizeOfArray){
	int i, maxValue;
	printf("maximum-slots:");
	maxValue = getMaximum(array, sizeOfArray);
	for(i=0; i<sizeOfArray;i++){
		if(array[i]==maxValue){
			printf(" %d", i);
		}
	}
	printf("\n");
}

/**
 * void slotIncremented(int beginPoints, int endPoints, int *array){
 * Increase the slots accroding to beginPoints and endPoints you set
 */
void slotIncremented(int beginPoints, int endPoints, int *array){
	int i;
	for(i = beginPoints; i <= endPoints; i++){
		array[i] ++;
	}
}

/**
 * int main():
 * main function to generate the whole program.
 * The input begins with a positive integer, which gives the number of slots in the
 * schedule. It is then followed by any number of pairs of numbers. Each pair
 * represents a range of slots; for instance the pair 3 6 means slots 3,4,5,6. Each
 * range represents an existing appointment held by some person.
 * Also, take care of all the error message in main function.
 * 1) if the fist input is not numeric
 * 2) if the first input is negative
 * 3) if slot number is zero
 * 4) if endpoints is bigger than biginpoints
 * 5) if endpoints or bigin points is bigger than slots size
 * 6) if you input nothing
 * 7) if don't have even numbers input after input the first number
 */
int main(){
	int count = 0;
	int status, input, countOfSlot;
	int endPoints, beginPoints;
	int *array = NULL;
	while((status = scanf("%d", &input)) != EOF){
		if(status != 1){ // your input is not numeric
			fprintf(stderr, "ERROR: Could not read the schedule size from stdin.  rc=0\n");
			return 1;
		}
		else{ // your input is numeric
			if(count==0){
				if(input < 0){ // if the first input is negative then just print the error and end prog
					fprintf(stderr, "ERROR: The schedule size is not valid.  slotCount=%d\n", input);
					return 1;
				}
				if(input == 0){
					fprintf(stderr, "ERROR: The schedule size is not valid.  slotCount=0\n");
					return 1;
				}
				else{ //put the first number to the size of array and malloc array
					countOfSlot = input;
					array = calloc(countOfSlot, sizeof(countOfSlot));
				}
				count++;
			}
			else if(count!= 0 && count %2 == 1){
				beginPoints = input;
				count++;
			}
			else{
				endPoints = input;
				count++;
				if(beginPoints>endPoints){
					fprintf(stderr, "ERROR: start > end.  slotCount=%d : start=%d end=%d\n", 
					countOfSlot, beginPoints, endPoints);
				}
				if(beginPoints>=countOfSlot || endPoints >= countOfSlot || beginPoints < 0 || endPoints < 0){
					fprintf(stderr, "ERROR: One or both of the endpoints of the current range is invalid. slotCount=%d : start=%d end=%d\n", countOfSlot, beginPoints, endPoints);
					endPoints = -1;
					beginPoints = -1;
				}
				slotIncremented(beginPoints, endPoints, array);
			}
		}
	}
	if(count==0){
		fprintf(stderr, "ERROR: Could not read the schedule size from stdin.  rc=-1\n");
		return 1;
	}
	if(count%2 != 1){
		fprintf(stderr, "ERROR: Could not read the next range.  rc=1\n");
		return 1;
	}
	printArray(array, countOfSlot);
	printf("minimum: %d\n", getMinimum(array, countOfSlot));
	printMinimum_Slots(array, countOfSlot);
	printf("maximum: %d\n", getMaximum(array, countOfSlot));
	printMaximum_Slots(array, countOfSlot);
	printAverage(array,countOfSlot);
	return 0;
}

/**
 * end
 */
