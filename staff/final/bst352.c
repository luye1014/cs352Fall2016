#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * File: bst352.c
 * Author: Lu Ye
 */

typedef struct TreeNode{
	int value;
	struct TreeNode *left;
 	struct TreeNode *right;
}TreeNode;

int status = 0;

TreeNode *insert(TreeNode *root, int number){ //smaller one is on the left
	TreeNode *new_Node = malloc(sizeof(TreeNode));
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
	return root;
}

void preOrder(TreeNode *root){
	if(root == NULL){
		return;
	}else{
		printf(" %d", root->value);
		preOrder(root->left);
		preOrder(root->right);
	}
}
void InOrder(TreeNode *root){
	if(root == NULL){
		return;
	}else{
		InOrder(root->left);
		printf(" %d", root->value);
		InOrder(root->right);
	}
}

void seach(TreeNode *root, int number){
	//printf("%d\n", target);
	if(root == NULL){ // if you have a empty tree
		printf("%d NOT found\n", number);
		//return 1;
	}else{
		if(root->value == number){
			printf("%d found\n", number);
			//return 0;
		}
		else if(root->value > number){
			return seach(root->left, number);
		}else{
			return seach(root->right, number);
		}
	}
}

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

TreeNode *findMax(TreeNode *node){
	if(node->right == NULL){
		return node;
	}
	return findMax(node->right);
}

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
    		printf("Don't want the bonus\n");
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

int main(int argc, char const *argv[]){
	TreeNode *root = NULL;
	char *input= NULL;
	size_t len = 0;
	int num, rc;
	char *command = malloc(sizeof(char));
	char *token;

	while(getline(&input, &len, stdin) != EOF){
		while((token = strtok(input, ";")) != NULL){
			rc = sscanf(token, "%31s %d", command, &num);
			if(command[0]!='m' && command[0]!='M' && command[0]!= 'p'&&command[0]!='P'){
				if(rc < 0){
					//white space, do nothing
					// printf("aa?\n");
				}else if(countWord(token)>2){
					(token)[strlen(token)-1] = '\0';
					fprintf(stderr, "ERROR: The command '%s' had too many terms.\n", token);
					status = 1;
				}else if(countWord(token)<2){
					if(strlen(command)==1){
						if(command[0]!='i' && command[0]!='d' && command[0]!='s'){
							printf("hereyes\n");
							(token)[strlen(token)-1] = '\0';
							fprintf(stderr, "ERROR: Unrecognized command name in the command '%s'\n", token);
							status = 1;
						}else{
							fprintf(stderr, "ERROR: The command '%s' requires an integer parameter.  Error in the command '%s'.\n", command, command );
							status = 1;
						}
					}else{
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
				}else if(countWord(command)!=1){
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

	}
	return status;
}


