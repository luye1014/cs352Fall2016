/*
 * File: primePair.c
 * Author: Lu Ye.
 * Purpose: In this class, you will scan a range, which are two numbers that you 
 * input, and print out all of the numbers which are the product of exactly two primes.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * isPrime(int val) -- determine whether one number is prime or not. if the number 
 * is prime then return 1. Otherwise, return 0.
 * If a number is prime, which means the factors of the number are one and itself.
 */

int isPrime(int val){
	int x;
	for(x = 2; x < val; x++){
		if(val % x == 0){
			return 0;
		}
	}
	return 1;
}

/*
 * firstFactor(int val) -- give a number and print out all product of exactly two
 * primes. 
 * Use for loop to keep tracking the number's factor. And then determine the factor
 * is prime or not. If the first factor is prime then we know the 
 * number / first factor = second factor. Determine the second factor whether is prime.
 * If these two numbers are all prime. Print them out.
 */
int firstFactor(int val){
	int factor1 = 0;
	int factor2 = 0;
	int i; 
	for(i = 2; i < val; i++){
		if(val % i == 0){
			if(isPrime(i)==1){
				factor1 = i;
				factor2 = val / i;
			}
			if(isPrime(factor2)==1){
				printf("%d: %d %d\n", val, factor1, factor2);
				return 0;
			}
		}
	}
	return 0;
}

/*
* main() -- main function which is generate the whole program. Scanf() numbers from 
* keyboard. Determine the numbers or should say your input whether avaiable or not.
* If your input is not a number then send message to stderr. And then to check your 
* input length --> your input length must be 2. And also we need to pay attention to 
* the first number your input must be bigger than 2 and the second input must be 
* smaller than the first input.
*/
int main(){
	int check, input, input1, input2;
	int inputNum = 0; 
	while((check = scanf("%d", &input))!= EOF){
		if(check != 1){
			fprintf(stderr, "ERROR: Input should be exactly: <start> <end>\n");
			return 1;
		}
		if(inputNum == 0){
			input1 = input;
		}
		if(inputNum == 1){
			input2 = input;
		}
		inputNum++;
		if(inputNum > 2){
			fprintf(stderr, "ERROR: Input should be exactly: <start> <end>\n");
			return 1;
		}
	}
	if(inputNum < 2){
		fprintf(stderr, "ERROR: Input should be exactly: <start> <end>\n");
			return 1;
	}
	if(input1 < 2){
		fprintf(stderr, "ERROR: Start must be >= 2\n");
		return 1;
	}
	if(input1 > input2){
		fprintf(stderr, "ERROR: Start must be <= end\n");
		return 1;
	}
	while(input1 <= input2){
		firstFactor(input1);
		input1++;
	}
	return 0;
}
