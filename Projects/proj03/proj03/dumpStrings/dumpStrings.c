/**
 * File: dumpString.c
 * Author: Lu Ye 
 * CSC345 proj02
 * In this program, you will read each string with scanf(), into a buffer. You will then 
 * iterate through the string, and print out each character: you will print out the character 
 * itself, and its decimal and hexadecimal values. At the end of each string, you will
 * report some simple metadata about the string. The metadata including index, number in char, 
 * number in decimal and number in hex number.
 */

#include <string.h>
#include <stdio.h>

/**
 * int resultPrint(buf)
 * Help method for main function to print out the message you want to search for.
 */  
int resultPrint(char buf[]){
	int i, len;
	len = strlen(buf); // get string length you inpu
	for(i = 0; i < len ; i++){
		printf("index=%d char='%c' dec=%d hex=0x%x\n" , i, buf[i], buf[i], buf[i]);
	}
	printf("count=%d strlen=%d\n\n", i, len);
	return 0;
}

/**
 * int main():
 * Main function which is search for string you input.
 */
int main(){
	char buf[32];
	while(scanf("%s", buf) != EOF){ // run until end of file
		resultPrint(buf);
	}
	return 0;
}

/**
 * end
 */
