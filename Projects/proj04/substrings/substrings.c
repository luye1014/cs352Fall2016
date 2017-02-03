/**
 * Author: LU YE
 * File: substrings.c
 * CSC352 proj04
 * In this program, you will read in a single long string (we’ll call it the “Master
 * String”), and then compare multiple other strings to it, checking to see if any
 * are substrings of the first string. In this program you will read entire lines and
 * save them as your strings--instead of using scanf() to read whitespace-delimited strings.
 * 
 */
#include <stdio.h>
#include <string.h>

/**
 * int substrings(char *MasterString, char *input):
 * help function to generate the whole program that to give a string that is a original string
 * you want to compare with and another input is a string you currently input. Then compare the
 * current string whether is the substring of the original string. If the current string is the 
 * substring of the origial one then print the index of the same char(where is the beginning) 
 * located. Otherwise, return -1.
 */
int substrings(char *MasterString, char *input){
	char *ptr1 = strdup(MasterString), *ptr2 = strdup(input);
	int i,j;
  	for(i = 0; i<strlen(MasterString)-1; i++){ // search through the whole length of original string
  		if(*ptr1 == *ptr2){
  			char *temp1 = strdup(ptr1); //give a copy of the original string
  			char *temp2 = strdup(input); 
  			for(j = 0; j<strlen(input)-1; j++){ //search through the whole length of current string
  				if(*temp1 == *temp2){
  					temp2++;
  					temp1++;
  				}
  				else{
  					break;
  				}
  			}
  			// until you find the last index of current string j is equal to current string length, return index
  			if((strlen(input)-1) == j){
  				return i;
  			}
  		}
  		ptr1++;
  	}
  	return -1;
}

/**
 * int main():
 * main function to generate the whole function, take care of the error message here. If your input 
 * are all come with no problem, then print the index where the current string is in the origial string.
 */
int main(){
	char *input = NULL;
    char *MasterString = NULL;
	size_t len = 0;
	int count = 0;	
	int status;
	while(getline(&input, &len, stdin)!= EOF){
		if(count == 0 && (*input == '\n')){  //users input nothing for the first line, send error and exit
			fprintf(stderr, "Master String is empty\n");
			return 1;
		}
		else if(count != 0 && (*input == '\n')){ // keep reading id input a new line
			status = 0;
		}
		else{
			if(count == 0){
				MasterString = strdup(input);
			}
			else{
				printf("%d\n", substrings(MasterString, input));
		    }
		}
		count++;
	}
	if(count == 0){ //if count == 0 which means user input nothing before end of file
		fprintf(stderr, "Master String is empty\n");
		return 1;
	}
	return status;
}

/**
 * end
 */