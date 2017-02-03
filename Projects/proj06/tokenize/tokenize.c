/**
 * File: tokenize.c
 * Author: Lu Ye
 * CSC345
 * Purpose: This program is simple: read lines of text from stdin. Break each line into
 * multiple “tokens” - that is, strings separated by whitespace - and save the
 * strings. After you have read the entire file, print out a quick summary of what
 * you have read, and then all of the tokens.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct a Node
 */
typedef struct Node{
	struct Node *next;
	char *data;
}Node;

void printList(Node *node){
	if(node==NULL){
		printf("0:\n"); //empty list
	}
	else{
		while (node != NULL){
    		printf(" %s/", node->data);
    		node = node->next;
   		}
   		printf("\n");
	}
}
/**
 * void InsertIntoBuf(Node **head, char *input):
 * This function is working for main function. If you read a line by line from the 
 * keyboard, then add that line into a buf with linked list strcuture.
 */
void InsertIntoBuf(Node **head, char *input){
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL){
		perror("Failed to allocate a new node for the linked list");
		exit(1);
	}
	newNode->data = input;
	newNode->next = NULL;

	Node *currentList = *head;
	if(*head == NULL){    //if the linked list head is null, then add the target into linked list
		*head = newNode;
	}
	else{
		while(currentList->next!=NULL){
			currentList = currentList->next;
		}
		currentList->next = newNode;
	}
	printList(head);
}

/**
 * void PrintToken(int numbers, char *str):
 * This function is working for counting tokens for each line. For example:
 * "This is a example" Then to check works one by one. If it meets a whitespace
 * then it means jump to another words.
 */
 void PrintToken(int range, int numbers, char*str){
 	char*head = str;
 	int i;
 	int len = strlen(str);
 	printf("%d\n", (int)strlen(str));
 	for(i=0; i<len;i++){
 		if(head[i]=='\t'||head[i]==' '|| head[i]=='\n'){
 			head[i] = '\0';
 		}
 	}
 	int count = 0, ishead=0;
 	while(count<range){
 		while(head!='\0'){
 			if(ishead==0){
 				printf("%s\n", head);
 				count++;
 				ishead=1;
 				head++;
 			}
 			head++;
 			printf("here1");
 		}
 		printf("here2");
 		ishead=0;
 		head++;
 	}
 }
// void PrintToken(int numbers, char *str){ 
// 	int counLine = numbers;
// 	char *Nodechar = malloc(strlen(str)+1); //need to check return
// 	if (Nodechar == NULL){
// 		perror("Failed to allocate a new node for the linked list");
// 		exit(1);
// 	}
// 	char *copy = strdup(str);

// 	int i = 0, count=0;
// 	while((*copy != '\0') && (*copy != '\n')){ //if currentLine is not end(meets null and newLine)
//  		if((*copy != '\t') && (*copy != ' ')){
//  			Nodechar[i] = *copy;
//  			copy++;
//  			i++;
//  		}else{
//  			if(strcmp(Nodechar,"")!=0){
//  				printf("  Line=%d Token=%d: \"%s\"\n", counLine, count, Nodechar);
//  				count++;
//  			}
//  			copy++;
//  			i=0;
//  			Nodechar = malloc(strlen(str)+1); //malloc a space with enough room
//  			if (Nodechar == NULL){
// 				perror("Failed to allocate a new node for the linked list");
// 				exit(1);
// 			}
//  		}
//  	}
//  	if(strcmp(Nodechar,"")!=0){
//  		printf("  Line=%d Token=%d: \"%s\"\n", counLine, count, Nodechar);
//  	}
// }

/**
 * int countTokenFunction(char *input):
 * In this function, I count the tokens each line. If the target line does not meet a null
 * terminator or a new line. Then determine whether the current characters is whitespace or 
 * not.
 * This is a help function for main method. Which can count the tokens number for each line.
 * In main function, I have a for loop to control the whole line and add each line tokens together
 * to get all numbers of token.
 */
int countTokenFunction(char *input){
	int countTokenEachLine = 0;
	char *inputLine = strdup(input);
	int flag = 0;
	while((*inputLine != '\0') && (*inputLine != '\n')){ //if currentLine is not end(meets null and newLine)
		if((*inputLine != '\t') && (*inputLine != ' ')){
			if(flag == 0){
				countTokenEachLine++; //only add count when meet first character
				flag++;
			}
		}
		else{ //if it not meets tab or whitespace
			flag = 0;
		}
		inputLine++;
		
	}
	return countTokenEachLine;
} 

/**
 * void EachTokenSummary(Node *head)
 * This is a help method for a final summary. Which can print the most inner result we 
 * want to print. Moreover, this function prints the current line number and the index of 
 * tokens and have a function for printing each token.
 */
void EachTokenSummary(Node *head){
	Node *cur = head;
	int count = 0;
	while(cur != NULL){
		int range = countTokenFunction(cur->data);
		printf("Line=%d Tokens: %d\n", count, range);
		PrintToken(range, count, cur->data); // print each token 
		count++;
		cur = cur->next;
	}
}

/**
 * int main():
 * A main function which is generate the whole program. Again!
 * This program is simple: read lines of text from stdin. Break each line into
 * multiple “tokens” - that is, strings separated by whitespace - and save the
 * strings. After you have read the entire file, print out a quick summary of what
 * you have read, and then all of the tokens.
 */
int main(){
	Node *head = NULL;
	char *input = NULL;
	size_t len = 0;
	int countLine = 0, countAllToken = 0;
	while(getline(&input, &len, stdin)!=EOF){
		countAllToken += countTokenFunction(input);  //count all numbers of tokens
		InsertIntoBuf(&head, input);
		input = NULL;
		countLine++;
	}
	printf("Lines=%d Tokens=%d\n", countLine, countAllToken);
	EachTokenSummary(head); //quick summary of what you have read, and then all of the tokens.
	return 0;
}

