/**
 * File: removeSome.c
 * Author: Lu Ye 
 * CSC345 proj02
 * In this program, you will read strings from the stdin. For each string you will
 * first check to see if it is entirely made up of letters and/or decimal digits. If
 * it is entirely made up of letters, you will print out the letters, but with all of
 * the vowels removed. If it is entirely made up of decimal digits, then you will
 * print out the digits in reverse order, but with all of the even-numbered digits
 * removed. (That is, remove the 0’s, 2’s, 4’s, 6’, and 8’s, wherever they are found
 * in the string). If you read a word which is neither all letters nor all decimal
 * digits, you will print that word out (with an error message) to stderr.
 */
 
#include <stdio.h>
#include <string.h>

/**
 * int checkAllNumber(str):
 * This method is to check whether your string is all number. return 1 if your
 * input is all letter.
 */ 
int checkAllNumber(char *str){
	char *ptr = str;
	while(*ptr != '\0'){
		if(!(*ptr >= '0' && *ptr <= '9')){ // number can be 0-9
			return 1;
		}
		ptr++;
	}
	return 0;
}

/**
 * int checkAllLetter(str):
 * This method is to determine all letters or not. return 1 if your input is not
 * all letters.
 */
int checkAllLetter(char *str){
	char *ptr = str;
	while(*ptr != '\0'){
		 if(!((*ptr <= 'z'&& *ptr >= 'a') || (*ptr <= 'Z' && *ptr >= 'A'))){ //letters can be a-z and A-Z
		 	return 1;
		 }
		 ptr++;
	}
	return 0;
}

/**
 * void removeVowel(str):
 * void removeVowel:read a string and get rid of all vowel letters
 */
void removeVowel(char *str){
	char *ptr = str;
	while(*ptr != '\0'){
		if(*ptr == 'a' || *ptr == 'e' || *ptr == 'i' || *ptr == 'o' || *ptr == 'u'||
		   *ptr == 'A' || *ptr == 'E' || *ptr == 'I' || *ptr == 'O' || *ptr == 'U'){
			ptr++; 	// if we meet vowel letters then just skip it
		}else{
			printf("%c", *ptr);
			ptr++;
		}
	}
	printf("\n");
}
/**
 * void reverse(str):
 * Help method for removeEven function which is reverse a string.
 */
void reverse(char *str){
	char *copy = strdup(str); // in order to protect the original string
	while(*copy != '\0'){
		copy++;
	}
	copy--;
	while(*str != '\0'){
		*str = *copy;
		str++;
		copy--;
	}
}
/**
 * void removeEven(str):
 * You have two tasks in this method, one is remove all of even numbers and 
 * another one is reverse the string you input. And reverse function above will
 * help you to reverse string.
 */
void removeEven(char *str){
	reverse(str);
	char buff[32];
	int count = 0;
	char *ptr = str;
	while(*ptr != '\0'){
		if((*ptr - '0') % 2 != 1){ //check if the number is a even number
			ptr++;
		}else{
			buff[count] = *ptr; //otherwise, make it '\0'
			count++;
			ptr++;
		}
	}
	buff[count] = '\0';
	printf("%s\n", buff);
}
/**
 * int main():
 * Main function to check your input is valid or not. A valid strin should be all letters or all numbers
 * and send a error message if your input is wrong. Then print out what you need.
 */
int main(){
	int status = 0;
	char buf[32];
	while(scanf("%s",buf)!= EOF){
		//check if your strin is not all number or not all letters then send a message to stderr
		if((checkAllNumber(buf) == 1) && (checkAllLetter(buf) == 1)){
			fprintf(stderr, "ERROR: The string '%s' does not appear to be either made of entirely letters, or entirely digits.\n", buf);
			status = 1;
		//otherwise, print what you need
		}else if(!checkAllLetter(buf)){
			removeVowel(buf);
		}else{
			removeEven(buf);
		}
	}
	return status;
}

/**
 * End
 */
