#include <stdio.h>
#include <string.h> 
#include <stdlib.h>


typedef struct n{
  char *value;
  struct n *next;
} Node;


void printList(Node *head){
  Node *cur = head;
  while(cur!=NULL){
    printf("%s/", cur->value);
    cur = cur->next;
  }
  printf("\n");
}

void insertIntoList(Node **head, char *data){
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL){
    perror("Failed to allocate a new node for the linked list");
    exit(1);
  }
  newNode->value = data;
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


int main(int argc, char**argv){
  FILE *fileStream;


  size_t len = 0;
  char *line = NULL;
  Node *head = NULL;


  int j;
  for(j=1; j<argc-2;j++){
    fileStream = fopen(argv[j], "r");
    if(fileStream == NULL){
      fprintf(stderr, "could not open");
      continue;
    }
    while(getline(&line, &len, fileStream)!=EOF){ /////////////Line 101
          char *targetNum = strtok(line, " \t\r\n");;
          printf("*****%s\n", targetNum);
          insertIntoList(&head, targetNum);
          }
      }
      //printList(head);
  }
  return 0;
}