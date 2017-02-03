/*
 * File: bst352.c
 * Author: Lu Ye
 * In this project, you will implement a Binary Search Tree in C. Your tree will
 * contain integers; you can use the C type int, and you’ll convert strings to
 * integers with the %d format specifier of sscanf.
 * For testcases, we’ll go back to the early part of this semester - we’ll be
 * reading from stdin, so each testcase will be a simple file. Each file will be
 * a series of lines; each line will be a single character (giving a command to
 * perform), sometimes followed by an integer. There will be commands to insert
 * (obviously!), search, find min and max, and delete. There will also be commands
 * to print the tree in two forms: a pre-order traversal, and an in-order traversal.
 * Using these commands, we’ll be able to track how you modify the data structure
 * over time, and ensure that you update it properly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Build a truct which contains the left node and right node also its value
 */
typedef struct TreeNode{
	int value;
	struct TreeNode *left;
 	struct TreeNode *right;
}TreeNode;

int status = 0;
/**
 * TreeNode *insert(TreeNode *root, int number):
 * Insert the value into the tree. If the value already exists, then print a
 * message to stderr but do not modify the tree.
 */
TreeNode *insert(TreeNode *root, int number){ //smaller one is on the left
	TreeNode *new_Node = malloc(sizeof(TreeNode));
	if (new_Node == NULL){
		perror("Failed to allocate a new node for the linked list");
		exit(1);
	}
	new_Node->value = number;
	new_Node->left = NULL;
	new_Node->right = NULL;
	if(root == NULL){ // if you have a empty tree
		return new_Node;
	}else{
		if(root->value == number){
			fprintf(stderr, "ERROR: Could not insert %d into the tree because it already exists.\n", number);
			status = 1;
		}
		else if(root->value > number){
			root->left = insert(root->left, number);
		}else{
			root->right = insert(root->right, number);
		}
	}
	free(new_Node);
	return root;
}

/**
 *
 * void preOrder(TreeNode *root):
 *
 * Print out a pre-order traversal of the tree, all on one line, with one space
 * before every value (including the first). Do not print any trailing whitespace,
 * except for a newline. If the tree is empty, print out a single blank
 * line
 */
void preOrder(TreeNode *root){
	if(root == NULL){
		return;
	}else{
		printf(" %d", root->value);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/**
 * void InOrder(TreeNode *root):
 *
 * This is the same as the p command - except that it is an in-order traversal.
 */
void InOrder(TreeNode *root){
	if(root == NULL){
		return;
	}else{
		InOrder(root->left);
		printf(" %d", root->value);
		InOrder(root->right);
	}
}

/**
 * void seach(TreeNode *root, int number) 
 *
 * Search for a given value in the tree. Print out the line
 * <int> found
 * if it is found; print out the line
 * <int> NOT found
 * if not. Both messages should be printed to stdout - that is, it is not an
 * error if the value is not found.
 */
void seach(TreeNode *root, int number){
	if(root == NULL){ // if you have a empty tree
		printf("%d NOT found\n", number);
		//return 1;
	}else{
		if(root->value == number){
			printf("%d found\n", number);
		}
		else if(root->value > number){
			return seach(root->left, number);
		}else{
			return seach(root->right, number);
		}
	}
}
/**
 * void minimum(TreeNode *root)
 *
 * Print out the minimum value in the tree, followed by a newline. If the tree
 * is empty, print out an error message to stderr, but continue running.
 */
void minimum(TreeNode *root){
	if(root == NULL){
		fprintf(stderr, "ERROR: Cannot calculate min because the tree is empty.\n");
		status = 1;
	}else{
		while(root->left!=NULL){
		root = root->left;
		}
		printf("%d\n", root->value);
	}
}
/**
 * void maxmum(TreeNode *root)
 *
 * Print out the maximum value in the tree, followed by a newline. If the
 * tree is empty, print out an error message to stderr, but continue running.
 */
void maxmum(TreeNode *root){
	if(root == NULL){
		fprintf(stderr, "ERROR: Cannot calculate min because the tree is empty.\n");
		status = 1;
	}else{
		while(root->right!=NULL){
		root = root->right;
		}
		printf("%d\n", root->value);
	}
}

/**
 * TreeNode *delete(TreeNode *root, int number)
 *
 * Delete the value from the tree. If the value does not exist, then print a
 * message to stderr but do not modify the tree
 */
TreeNode *delete(TreeNode *root, int number) {
    TreeNode *temp;
    if(root == NULL){
    	fprintf(stderr,"ERROR: Could not delete %d from the tree because it does not exist.\n", number);
    	status = 1;
    }else if(root->value > number){
    	root->left = delete(root->left, number);
    }else if(root->value < number){
    	root->right = delete(root->right, number);
    }else{//the node has been found
    	if(root->left!=NULL && root->right!=NULL){//case 1: two children
    		printf("Don't need extra credit\n");
    	}else{//case 2 and 3
    		temp = root;
    		if(root->left==NULL){
    			root = root->right;
    			free(temp);
    		}else{
    			if(root->right == NULL){
    				root = root->left;
    			}
    			free(temp);
    		}
    	}
    }
    return root;
}


/**
 * int countWord(char *token)
 * 
 * This is a help method for main method which is check the number of word each line
 */
int countWord(char *token){
	int i = 0, counter = 0, flag = 0;
	for (i = 0; i < strlen(token); i++){
		if(flag == 0 && token[i]!=' ' && token[i]!='\t' && token[i]!='\n'){
			counter++;
			flag = 1;
		}
		else if(token[i]==' ' || token[i]=='\t' || token[i]=='\n'){
			flag = 0;
		}
	}
	return counter;
}

/**
 * void freeALL(TreeNode *root):
 *
 * free node
 */
void freeALL(TreeNode *root){
	if(root == NULL){
		return;
	}else{
		freeALL(root->left);
		freeALL(root->right);
		free(root);
	}
}
/**
 * int main(int argc, char const *argv[])
 * 
 * Mian function to generate the whole function
 *
 * For testcases, we’ll go back to the early part of this semester - we’ll be
 * reading from stdin, so each testcase will be a simple file. Each file will be
 * a series of lines; each line will be a single character (giving a command to
 * perform), sometimes followed by an integer. There will be commands to insert
 * (obviously!), search, find min and max, and delete. There will also be commands
 * to print the tree in two forms: a pre-order traversal, and an in-order traversal.
 * Using these commands, we’ll be able to track how you modify the data structure
 * over time, and ensure that you update it properly
 */
int main(int argc, char const *argv[]){
	TreeNode *root = NULL;
	char *input= NULL;
	size_t len = 0;
	int num, rc;
	char command[32];
	char *token;

	while(getline(&input, &len, stdin) != EOF){
		char *temp=input;
		while((token = strtok(input, ";")) != NULL){
			rc = sscanf(token, "%31s %d", command, &num);

			//printf("--->%d\n",countWord(token));
			if(command[0]!='m' && command[0]!='M' && command[0]!= 'p'&&command[0]!='P'){
				if(rc < 0){
					//white space, do nothing
				}else if(countWord(token)>2){
					(token)[strlen(token)-1] = '\0';
					fprintf(stderr, "ERROR: The command '%s' had too many terms.\n", token);
					status = 1;
				}else if(countWord(token)<2){
					if(strlen(command)==1){
						if(strcmp(command, "i") != 0 && strcmp(command, "d") != 0 && strcmp(command, "s") != 0){
							//printf("hereyes\n");
							(token)[strlen(token)-1] = '\0';
							fprintf(stderr, "ERROR: Unrecognized command name in the command '%s'\n", token);
							status = 1;
						}else{
							fprintf(stderr, "ERROR: The command '%s' requires an integer parameter.  Error in the command '%s'.\n", command, command );
							status = 1;
						}
					}
					else{
						if((token)[strlen(token)-1] =='\n'){
							(token)[strlen(token)-1] = '\0';
						}
						fprintf(stderr, "ERROR: Unrecognized command name in the command '%s'.\n", token);
							status = 1;
					}
				}else{
					if(rc != 2){
						(token)[strlen(token)-1] = '\0';
						fprintf(stderr, "ERROR: The command '%s' had a parameter which was not an integer\n", token);
						status = 1;
					}else{//correct command dealing with values
						if(command[0]=='i'){
							root = insert(root, num);
						}else if(command[0]=='d'){
							root = delete(root, num);
						}else if(command[0]=='s'){
							seach(root,num);
						}
					}
				}
			}else{
				if(rc < 0){

				}else if(countWord(token)!=1){
					(token)[strlen(token)-1] = '\0';
					fprintf(stderr, "ERROR: The command '%s' MUST NOT have any parameter.  Error in the command '%s'.\n", command, token);
					status = 1;
				}
				else{//other command line - just one letter
					if(command[0]=='m'){
						minimum(root);
					}else if(command[0]=='M'){
						maxmum(root);
					}else if(command[0]== 'p'){
						preOrder(root);
						printf("\n");
					}else if (command[0]=='P'){
						InOrder(root);
						printf("\n");
					}
				}
				
			}
			input = NULL;
		}
		free(temp);
	}
	free(input);
	freeALL(root);
	return status;
}


