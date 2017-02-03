/**
 * Author: Lu Ye
 * File: linkedList.c
 * CSC352 proj05
 * In this program, you will implement a sorted linked list. You will read
 * a series of commands from stdin, which will insert and
 * delete elements, and do some other simple operations. You will also implement
 * a “print” feature, which will print the current contents of the list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct node: struct a node with two value-name and favorite numbers
 */
struct node{
	char *name;
	int numbers;
	struct node *next;
};
struct node *list = NULL; // A global variable for list
int error = 0;            // A global variable to help change error status

/**
 * int sizeofList(struct node *node): Here has a help function for printList to find the
 * size of the list
 */
int sizeofList(struct node *node){
	int count = 0;
	struct node *temp = node;
	while(temp!=NULL){
		temp = temp->next; //if can find the next node
		count++;
	}
	return count;
}

/**
 * void printList(struct node *node): This function is to print the current list.
 */
void printList(struct node *node, int error){
	int count = sizeofList(node);
	if(node==NULL){
		printf("0:\n"); //empty list
	}
	else{
		printf("%d:", count);
		while (node != NULL){
    		printf(" %s/%d", node->name, node->numbers);
    		node = node->next;
   		}
   		printf("\n");
	}
}

/**
 * void insert(struct node **list, char *name, int numbers): A function that you add the node in
 * front of the list
 */
void insert(struct node **list, char *name, int numbers){
	struct node * new_node = malloc(sizeof(struct node));
	new_node->name = strdup(name); // protect the original list
	new_node->numbers = numbers;
	new_node->next = *list; // list is coming after new_node
	*list = new_node;
}

/**
 * void Sort(struct  node**listHead): A function to sort the list in order by recusive method
 */
void Sort(struct  node**listHead){
	if(*listHead==NULL || (*listHead)->next==NULL) return; // if the empty list or only one node, then return the current list
	Sort(&(*listHead)->next);
	struct node *temp = *listHead;
	char* SortedNam = (*listHead)->name;
	int SortedNum = (*listHead)->numbers;
	
	while(temp->next!=NULL && strcmp((temp->next->name), SortedNam)<0){
		temp->name = temp->next->name;
		temp->numbers = temp->next->numbers;
		temp = temp->next;
	}
	temp->name = SortedNam;
	temp->numbers = SortedNum;
}


/**
 * void removeHead(): this function is going to remove the first element in the linked list
 */
void removeHead(struct node** list){
	struct node* temp = *list;
  	if(*list != NULL){ //if the list is null then remove head from the list
   		*list = (*list)->next;
    	free(temp);
  	}
  	else{
  		fprintf(stderr, "ERROR: Could not remove the head from the list; the list was empty.\n");
  		error = 1;
  	}
}

/**
 * deleteNode(&list, name): This is a function to delete a specific name you give, delete 
 * the whole node
 */
void deleteNode(struct node** list, char *name){
	struct node *temp = *list;
	struct node *prev = malloc(sizeof(struct node)); //for saving the previous node
	char *copyName = strdup(name); //the name that you want to delete
	if(*list==NULL){ //if the list is null means error reported
		fprintf(stderr, "ERROR: Could not delete '%s' from the list, it did not exist.\n", name);
		error = 1;
	}
	else if(strcmp(temp->name, copyName)==0){ //the first node of list is the node you want to dele
		*list = temp->next;
		return;
	}else{ // 1 2 3 4 n     5
		while(temp != NULL && strcmp(temp->name, copyName)!=0){
		prev = temp;
		temp = temp->next;
		}
		
		if(temp == NULL){
			fprintf(stderr, "ERROR: Could not delete '%s' from the list, it did not exist.\n", name);
			error = 1;
		}
		else{
			prev->next = temp->next;
		}
	}
}


/**
 * int dupName(): to check your insert the name that you inserted before
 */
int dupName(struct node *list, char *name){
	struct node *ptr = list;
	ptr = ptr->next;
	char *curName = strdup(name);
	while(ptr!=NULL){
		if(strcmp(ptr->name, curName)==0){ //if the target is equal the current
			return 1;
		}else{
			ptr = ptr->next;
		}
	}
	return 0;
}

/**
 * int main(): main function to generate the whole program and also in the main function we need to take 
 * care of all of error cases.
 */
int main(){
	char *input= NULL;
	size_t len = 0;
	char *commands = malloc(sizeof(char));
	char name[21];
	int numbers, res; 
	int flag = 0;
 
	while(getline(&input, &len, stdin) != EOF){
		if(strlen(input) > 80){
			fprintf(stderr, "ERROR: A line in the input was longer tthan 80 characters (including the newline).\n");
			return 1;
		}
		if ((input)[strlen(input)-1] != '\n'){
		fprintf(stderr, "ERROR: A line in the input was longer tthan 80 characters (including the newline).\n");
		return 1;
		}
		res = sscanf(input, "%10s %20s %d", commands, name, &numbers);
		if(res<0){ // res = -1, can's recognize successfully
			if(strcmp(input, "\n")==0){
				error = error;
			}else{
				fprintf(stderr, "ERROR: The following line was not recognized as a valid command (sscanf() could not parse any elements): %s\n", input);
				error = 1;
			}
		}
		else if(strcmp(commands, "print") == 0){ // recognize command print
			if(res>=1){
				Sort(&list); //sort list before printing
				printList(list, error);
			}
		}
		else if(strcmp(commands, "insert") == 0){// recognize command insert
			if(res <= 2){
				fprintf(stderr, "ERROR: Invalid command.  The 'insert' command requires that there be two parameters: a name, and an integer.  The line was: insert %s\n", input);
				error = 1;
			}
			else if(strlen(name) >= 20){
				fprintf(stderr, "ERROR: Invalid command.  The 'name' parameter was too long.  The line was: %s\n", input);
				error = 1;
			}
			else{
				insert(&list, name, numbers);
				if(dupName(list, name) == 1 && flag == 1){
					fprintf(stderr, "ERROR: Could not insert into the list: duplicate name '%s'\n", name);
					error = 1;
					removeHead(&list);
				}
				flag = 1;
			}
		}
		else if(strcmp(commands, "delete") == 0){ // recognize command delete
			if(res<=1){
				fprintf(stderr, "ERROR: Invalid command.  The 'delete' command requires that there be a parameter: the name.  The line was: delete\n");
				error = 1;
			}
			else{
				deleteNode(&list, name);
			}	
		}
		else if(strcmp(commands,"removeHead") == 0){ // recognize command removeHead
			Sort(&list);  //Sort the list in a correct order and move the head
			removeHead(&list);
		}
		else{
			fprintf(stderr, "ERROR: Unrecognized command.  The line was: %s\n", input);
		 	error = 1; //checked		
		}
	}
	return error;
}

/**
 * End
 */

