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
struct node *list = NULL; // A golbal variable for list

/**
 * int sizeofList(struct node *node): Here has a help function for printList to find the
 * size of the list
 */
int sizeofList(struct node *node){
	int count = 0;
	struct node *temp = node;
	while(temp!=NULL){
		temp = temp->next;
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
		printf("0:\n");
		//printf("----->%d\n", error);
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
	new_node->name = strdup(name);
	new_node->numbers = numbers;
	new_node->next = *list;
	*list = new_node;
}

/**
 * void Sort(struct  node**headf): A function to sort the list in order by recusive method
 */
void Sort(struct  node**headf){
	if(*headf==NULL || (*headf)->next==NULL)
	return;
	
	Sort(&(*headf)->next);
	struct node*j=*headf;
	
	char* d=(*headf)->name;
	int n=(*headf)->numbers;
	
	while(j->next!=NULL && strcmp((j->next->name),d)<0)
	{
		j->name=j->next->name;
		j->numbers=j->next->numbers;
		j=j->next;
	}
	j->name=d;
	j->numbers = n;
}


/**
 * void removeHead(): this function is going to remove the first element in the linked list
 */
void removeHead(struct node** list){
  struct node* temp = *list;
  if(*list != NULL){
    *list = (*list)->next;
    free(temp);
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
		if(strcmp(ptr->name, curName)==0){
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
	//char *insert = "insert";
	char name[21];
	int numbers, res; 
	int flag = 0;
	int error = 0; 
	while(getline(&input, &len, stdin) != EOF){
		if(strlen(input) > 80){
			fprintf(stderr, "ERROR: A line in the input was longer tthan 80 characters (including the newline).\n");
			return 1;
		}
		res = sscanf(input, "%s %20s %d", commands, name, &numbers);
		// printf("res:%d\n", res);
		if(strcmp(input, "\n")==0){
			
		}
		else if(strcmp(commands, "print") == 0){
			if(res>=1){
				Sort(&list);
				printList(list, error);
			}
		}
		else if(strcmp(commands, "insert") == 0){
			if(res <= 2){
				fprintf(stderr, "ERROR: Invalid command.  The 'insert' command requires that there be two parameters: a name, and an integer.  The line was: insert %s", input);
				error = 1;
			}
			else if(strlen(name) >= 20){
				fprintf(stderr, "ERROR: Invalid command.  The 'name' parameter was too long.  The line was: %s", input);
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
		else if(strcmp(commands, "delete") == 0){
			if(res<=1){
				fprintf(stderr, "ERROR: Invalid command.  The 'delete' command requires that there be a parameter: the name.  The line was: delete\n");
				error = 1;
			}
			else{
				deleteNode(&list, name);
			}	
		}
		else if(strcmp(commands,"removeHead") == 0){
			removeHead(&list);
		}
		else{
			
			fprintf(stderr, "ERROR: Unrecognized command.  The line was: %s -----> sizeof:%d", input, sizeof(input));
	 		error = 1; //checked
			}
		 	
		}
	}
	return error;
}

