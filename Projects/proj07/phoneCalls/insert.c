#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

typedef struct n2{
  char *value;
  struct n2 *nextcNode;
  int count;
} ConnectedNode;

typedef struct n{
  char *value;
  struct n *next;
  ConnectedNode *cNode;
} Node;



void printList(Node *head){
  Node *cur = head;
  while(cur!=NULL){
    printf("|%s|", cur->value);
    printf("->%s->",cur->cNode->value);
    cur = cur->next;
  }
  printf("\n");
}

// void insertCNode(Node **head, char *num2){
//  ConnectedNode *newNode = malloc(sizeof(ConnectedNode));
//  if (newNode == NULL){
//    perror("Failed to allocate a new node for the linked list");
//    exit(1);
//  }
//  newNode->value = num2;
//  newNode->nextcNode = NULL;

//  Node *cur = *head;
//  if(cur->cNode ==NULL){
//    cur->cNode = newNode;
//  }else{
//    while(cur->cNode!=NULL){
//      if(strcmp(cur->cNode->value, num2) == 0){
//        fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
//        return;
//      }
//      cur->cNode = cur->cNode->nextcNode;
//     }
//     cur->cNode = newNode;

//  }

// }

// void insertIntoList(Node **head, char*num2, char*num1){
//  Node *newNode = malloc(sizeof(Node));
//  if (newNode == NULL){
//    perror("Failed to allocate a new node for the linked list");
//    exit(1);
//  }
//  newNode->value = num1;
//  newNode->next = NULL;

//  Node *currentList = *head;
//  if(*head == NULL){    //if the linked list head is null, then add the target into linked list
//    *head = newNode;
//    insertCNode(head, strdup(num2));
//  }else if(currentList != NULL && strcmp(currentList->value, num1) == 0){
//    fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
//  }
//  else{
//    while(currentList->next!=NULL){
//      currentList = currentList->next;
//      if(strcmp(currentList->value, num1) == 0){
//        //fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
//        return;
//      }
//    }
//    currentList->next = newNode;
//    insertCNode(head, strdup(num2));
//  }
// }

void insertConnectedNum(Node **head, char*num2, char*num1){
  ConnectedNode *newNode = malloc(sizeof(ConnectedNode));
  if (newNode == NULL){
    perror("Failed to allocate a new node for the linked list");
    exit(1);
  }
  newNode->value = num2;
  newNode->nextcNode = NULL;

  Node *cur = *head;
  if(strcmp(cur->value, num1) == 0){
    //printf("lalalal%s\n", num1);
    cur->cNode = newNode;
  }else{
    while(cur->next!=NULL){
      cur = cur->next;
      if(strcmp(cur->value, num1) == 0){
      //  printf("lalalal2%s\n", num1);
        cur->cNode = newNode;
      }
    }
  }
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
  }else if(currentList != NULL && strcmp(currentList->value, data) == 0){
    fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
  }
  else{
    while(currentList->next!=NULL){
      currentList = currentList->next;
      if(strcmp(currentList->value, data) == 0){
        //fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
        return;
      }
    }
    currentList->next = newNode;
  }
}


int checkNumberformat(char *str){
  //Each phone number must be of the form xxx-xxxx

  if(strlen(str) != 8 ){
    return 1; //wrong length->wrong format
  }
  int count = 0;
  while(count < 8){
    if( (count!=3) && (str[count] >= '0') && (str[count] <= '9') ){
      count++;
    }else if((count==3) && (str[count]=='-')){
      count++;
    }else{
      return 1; //wrong format with no number
    }
  }
  return 0;
}
int main(int argc, char**argv){
  FILE *fileStream;


  size_t len = 0;
  char *line = NULL;
  Node *head = NULL;
  //ConnectedNode *list = NULL;


  int i, j;
  if(argc<4){ //check the format.need to ask pro whether send message ?????????
    fprintf(stderr, "ERROR: Too few arguments.  Minimum args are <file1> <phone1> <phone2>\n");
    return 1;
  }
  for(i = 0; i < argc-2; i++){ //only catch the programname and filename
  }
  if(checkNumberformat(argv[i])==1 || checkNumberformat(argv[i+1])==1){ //This line check the number format
    printf("ERROR: One or both of the phone numbers, at the end of the command line, are invalid.  num1='%s' num2='%s'\n", argv[i], argv[i+1]);
    return 1;
  }
  //after check the format, check what we need

  for(j=1; j<argc-2;j++){
    fileStream = fopen(argv[j], "r");
    if(fileStream == NULL){
      fprintf(stderr, "Arg %d (%s): Could not open one of the input files: No such file or directory\n", j, argv[j]);
      continue;
    }
    while(getline(&line, &len, fileStream)!=EOF){
          char *targetNum = strtok(line, " \t\r\n");
        if (targetNum != NULL) {
            insertIntoList(&head, strdup(targetNum));
        }
        //point to second number
        char *targetNum2 = strtok(NULL, " \t\r\n");
        if(targetNum2!=NULL){
          insertConnectedNum(&head, strdup(targetNum2), strdup(targetNum));
        }
        // char *targetNum = strtok(line, " \t\r\n");
        // char *targetNum2 = strtok(NULL, " \t\r\n");
        // insertIntoList(&head, strdup(targetNum2), strdup(targetNum));

        }
      printList(head);
  }
  return 0;
}



