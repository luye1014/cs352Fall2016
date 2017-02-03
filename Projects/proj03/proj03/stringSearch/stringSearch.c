/**
 * File: stringSearch.c
 * Author: Lu Ye 
 * CSC345 proj02
 * In this program, you will first read a single string from the input. You will then
 * read additional strings. Print to output any string which exactly matches the
 * original word, which matches it in reverse order, or which exactly matches the
 * previous string read. In each case, we have provided a message that you must
 * print, along with the string, to explain why you printed it.
 */

#include <stdio.h>
#include <string.h>
 
/**
 * int Mat(searchString, str):
 * To determine whether the current string is match the first string you input.
 * return 1 if searchingString is equal to current string. And then print out the message.
 */
int Mat(char *searchString, char* str){
	if(strcmp(searchString, str)==0){ //compare two strings using strcmp() function
		printf("Mat: %s\n", str);
		return 1; //return 1 if match and print message
	}
	return 0; 
}

/**
 * void reverse(str):
 * Help method for Rev, which can reverse a char array. 
 */
void reverse(char *str){
	char *copy = strdup(str); //copy original string to protect it
	while(*copy != '\0'){
		copy++;
	}
	copy--;
	while(*str != '\0'){
		*str = *copy; //assign values from the last position
		str++;
		copy--;
	}
}

/**
 * int compareTo(searchString, str):
 * Compare two strings whether equal or not. If strings are equal then return 1, return 0 otherwise.
 */
int compareTo(char *searchString, char *str){
	char *copy1 = strdup(str); 			//copy original string to protect it
	char *copy2 = strdup(searchString); //copy original string to protect it
	while(*copy1 == *copy2){
		if(*copy2 == '\0' || *copy1 == '\0'){
			break;
		}
		copy2++;
		copy1++;
	}
	//look at if the last value is '\0' to check two strings have the same length
	if(*copy1 == '\0' && *copy2 == '\0'){
		return 1;
	}
	return 0;
}
/**
 * int Rev(searchString, str):
 * This method is a major method for determing str you input whether is same as the first one or not.
 */
int Rev(char *searchString, char *str){
    char *copy = strdup(str); 			//copy original string to protect it
	reverse(copy);						//reverse string so you can compare two in a correct order
	if(compareTo(copy, searchString)==1){
		printf("Rev: %s\n", str);
		return 1;
	}
	else{
		return 0;
	}
}

/**
 * int Dup(previousStr, buf):
 * This method is a major method for determing str you input whether is same as the previous one or not.
 */
int Dup(char *previousStr, char *buf){
	char *originalString = strdup(previousStr);
	if(compareTo(previousStr, buf)==1){    // compare two strings without using strcmp() function
		printf("Dup: %s\n", originalString);
		return 1;
	}
	else{
		return 0;
	}

}

/**
 * int main():
 * Main function to generate the whole program. Print to output any string which exactly matches 
 * the original word, which matches it in reverse order, or which exactly matches the
 * previous string read. If you input a empty string then send a error message to strerr.
 */
int main(){
	char buf[32];
	char searchString[32];
	char previousStr[32];
	int count = 0;
	int countM = 0;
	int countR = 0;
	int countD = 0;
	while(scanf("%31s", buf)!=EOF){ // the longer length you can have is 32 chars
		if(count==0){                                                
			strcpy(searchString, buf);
			strcpy(previousStr, searchString);
		}
		else{
			if(Mat(searchString, buf)==1){ 
				countM++;       // count Matched number
			}
			if(Rev(searchString, buf)==1){
				countR++;		// count Reversed number
			}
			if(Dup(previousStr, buf)==1){
				countD++;		// count duplicated number 
			}
			strcpy(previousStr, buf);
		}
	count++;
	}
	// send error message if you did not read any string
	if(count==0){
		fprintf(stderr, "ERROR: Could not read the first string from stderr!\n");
		return 1;
	}
	count--;
	printf("Totals: strings=%d : m=%d r=%d d=%d\n", count, countM, countR, countD);
	return 0;	
}

/**
 * End
 */
