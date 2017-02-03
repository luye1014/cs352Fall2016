/**
 * File: tokenize.c
 * Author: Lu Ye
 * CSC345 v2
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
}

/**
 * void PrintToken(int numbers, char *str):
 * This function is working for counting tokens for each line. For example:
 * "This is a example" Then to check works one by one. If it meets a whitespace
 * then it means jump to another words.
 */
void PrintToken(int numbers, char *str){ 
	int countLine = numbers;
	int count = 0, i = 0, index = 0, j = 0;
    int len = strlen(str);
    char **res = calloc(strlen(str)+1, sizeof(char*)); //one for null terminator
    if(res == NULL){
		perror("Failed to allocate a new node for the linked list");
		exit(1);
	}
    char temp = ' ';
    for(i = 0; i < len; i++){
        if((str[i] == ' ')||(str[i] == '\t') ||(str[i] == '\n')){//determine whether the char at this position is whitespace or not
            temp = str[i];
            str[i] = '\0';
        }else if(str[i] != '\0' && (temp == ' '||temp=='\t')){
            res[index] = &str[i];//otherwise put it into result array
            index++;
            temp = str[i];
        }
    }
    while(res[j] != '\0'){//print it out
        printf("  Line=%d Token=%d: \"%s\"\n", countLine, count, res[j]);
        j++;
        count++;
    }
}

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
		printf("Line=%d Tokens: %d\n", count, countTokenFunction(cur->data));
		PrintToken(count, cur->data); // print each token 
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