/**
 * Author: Lu Ye
 * File: phoneCalls.c
 * Purpose: CSC352 proj07
 * In this project, your program will take several arguments on the command line.
 * These arguments will include one or more file names; the last two arguments
 * will be phone numbers. Your program will read from the files listed (it will not read from stdin).
 * You will open each one in turn, and read its contents; you will store all of
 * the information that you find into a data structure in memory. You will mix
 * together all of the information from all of the files, into a single data structure.
 * After you have read all of the files, you will look at the two phone numbers
 * (the last two arguments on the command line). You will then search through
 * your data structures and find out how many times (if at all) these two numbers
 * have had a phone call. You will report this number.
 * Next, you will look for any case where the two numbers have both contacted
 * a third person (that is, they have a mutual acquaintance). If there is any such
 * third person, you will also report that. (For testing purposes - so we don’t have
 * to sort the output - you will only indicate whether a third person exists. You
 * will not print out what number it is.)
 */

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

/** 
 * Here is creating two struct to build a linked list contains another linked list
 * The main phone number linked list is called Node which contains another node called
 * ConnectedNode. ConnectedNode gave us a view of call number.
 */
typedef struct n2{
  char *value;
  struct n2 *next;
  int count;
} ConnectedNode;

typedef struct n{
  char *value;
  struct n *next;
  ConnectedNode *cNode;
} Node;

/*
 * void insert(Node **head, char *data){
 * Here is a insert function to insert node into a linked list. 
 * If one of data, known as node has been exit in the linked list
 * then you can skip to another data you searched for. 
 */
void insert(Node **head, char *data){
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL){
    perror("Failed to allocate a new node for the linked list");
    free(newNode);
    exit(1);
  }
  newNode->value = data;
  newNode->next = NULL;

  Node *currentList = *head;
  if(*head == NULL){    //if the linked list head is null, then add the target into linked list
    *head = newNode;
  }else if(currentList != NULL && strcmp(currentList->value, data) == 0){
    //fprintf(stderr, "ERROR:duplicate name");
    currentList = currentList;
  }
  else{
    while(currentList->next!=NULL){
      currentList = currentList->next;
      if(strcmp(currentList->value, data) == 0){
       continue;
      }
    }
    currentList->next = newNode;
  }
  free(newNode);
}

/**
 * int compare(Node **numersList1, Node **numersList2){
 * This is a boolean type function to help printYONSummary function
 * This method can compare whether two phone numbers are same or not.
 */
int compare(Node **numersList1, Node **numersList2){
  Node *cur1 = *numersList1;
  Node *cur2 = *numersList2;
  while(cur1!=NULL){
    if(strcmp(cur1->value,cur2->value)==0){
      return 1;
    }
    return compare(&(cur1->next), numersList2);
  }
  return 0;
}

/**
 * int printYONSummary(Node **head, char*cmdNum1, char*cmdNum2){
 * This is a boolean type function which can find whether two phone 
 * numbers in the command line have a mutual object phone numbers
 * If two phone numbers have the same third numbers then print yes.
 * Otherwise, print no.
 */
int printYONSummary(Node **head, char*cmdNum1, char*cmdNum2){
  int flag = 0;
  Node *numersList = NULL;
  Node *numersList2 = NULL;
  Node *cur = *head;
  while(cur!=NULL){
    if(cur->cNode != NULL){
      if(strcmp(cmdNum2, cmdNum1)==0){
        return 1;
      }
      else if(strcmp(cur->value, cmdNum1)==0 && strcmp(cur->cNode->value, cmdNum2)==0){
      }
      else if(strcmp(cur->value, cmdNum2)==0 && strcmp(cur->cNode->value, cmdNum1)==0){
      }
      else if(strcmp(cur->value, cmdNum1)==0){
        insert(&numersList, cur->cNode->value);
      }else if(strcmp(cur->cNode->value, cmdNum1)==0){
        insert(&numersList, cur->value);
      }else if(strcmp(cur->value, cmdNum2)==0){
        insert(&numersList2, cur->cNode->value);
      }else if(strcmp(cur->cNode->value, cmdNum2)==0){
        insert(&numersList2, cur->value);
      }
    }
  cur = cur->next;
  }
  flag = compare(&numersList, &numersList2);
  return flag;  
}

/**
 * Node *insertIntoList(Node *head, char *data, char *linkedObj){
 * This function is creating a linked list contains another linked list
 * that to return the structure. Which gives a exit linked list and add
 * the value into the list.
 */
Node *insertIntoList(Node *head, char *data, char *linkedObj){
  Node  *cur =  head;
  Node **ptrInPrev = &head;

  while (cur != NULL && strcmp(cur->value, data) < 0){
    ptrInPrev = &cur->next;
    cur =  cur->next;
  }

  ConnectedNode *conNode = malloc(sizeof(ConnectedNode));
    if (conNode == NULL){
      perror("Failed to allocate a new node for the linked list");
      free(conNode);
      exit(1);
    }
    conNode->value = linkedObj;
    conNode->next = NULL;

  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL){
    perror("Failed to allocate a new node for the linked list");
    free(newNode);
    exit(1);
  }
  newNode->value = data;
  newNode->next = cur;
  *ptrInPrev = newNode;
  newNode->cNode =conNode;
  return head;
}
/**
 * int countNumber(Node **head, char*cmdNum1, char*cmdNum2){
 * Here has a help method for main method to count how many target
 * phone numbers once had a conversation.
 */
int countNumber(Node **head, char*cmdNum1, char*cmdNum2){
  int count = 0;
  Node *cur = *head;
  if(strcmp(cmdNum2, cmdNum1) != 0){
    while(cur!=NULL){
      if(strcmp(cur->value, cmdNum1) == 0 && strcmp(cur->cNode->value, cmdNum2) == 0){
        count++;
      }else if(strcmp(cur->value, cmdNum2) == 0 && strcmp(cur->cNode->value, cmdNum1) == 0){
        count++;
      }
    cur = cur->next;
    }
  }
  return count;
}

/**
 * int checkNumberformat(char *str){
 * A help method works for main function which give it a phone number to check whether 
 * the parameter is valid or not.
 */
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

/**
 * int main(int argc, char**argv){
 * Here is a main function which is generating the whole program.
 * Also it generates some error that could occur in this program.
 */
int main(int argc, char**argv){
  FILE *fileStream;
  size_t len = 0;
  char *line = NULL;
  Node *head = NULL;
  char *temp1 = NULL, *temp2 = NULL;
  int count = 0, flag = 0, status = 0, resultcount = 0;
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
      status = 1;
    }else{
      count = 0;
      while(getline(&line, &len, fileStream)!=EOF){
          char *copyLine = strdup(line);
          char *aline = strtok(copyLine, "\n");
          if(((line[0] >= '0') && (line[0] <= '9'))||(strcmp(line, "\n")==0)){
            char *targetNum = strtok(line, " \n");
            if(targetNum=='\0'){
              free(copyLine);
              continue;
            }
            char *targetNum2 = strtok(NULL, "\n");
            if(targetNum2=='\0'){
              fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", targetNum);
              free(copyLine);
              status = 1;
              continue;
            }
            //printf("%d\n", (int)strlen(targetNum2));
            if(strlen(targetNum)!=8 || strlen(targetNum2)!=8){
              fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", aline);
              free(copyLine);
              //printf("what\n");
              status = 1;
              continue;
            }
            if(strcmp(targetNum, "\n")!=0&&strcmp(targetNum,"\t")!=0&&strcmp(targetNum," ")!=0){
              if(checkNumberformat(targetNum)==1 || checkNumberformat(targetNum2)==1){ //This line check the number format
                fprintf(stderr, "ERROR: One or both of the phone numbers was invalid.  phone1='%s' phone2='%s'\n", targetNum, targetNum2);
                status = 1;
                free(copyLine);
                continue;
              }
              else if(strcmp(targetNum2,targetNum)==0){
                fprintf(stderr, "ERROR: Rejecting a line which has duplicate phone numbers.\n");
                status = 1;
                free(copyLine);
                continue;
              }else{
                temp1 = strdup(targetNum);
                temp2 = strdup(targetNum2);
                head = insertIntoList(head, temp1, temp2);
              }
            }
          } 
          else{
            char *invalidLine = strtok(line, "\n");
            fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", invalidLine);
            free(copyLine);
            status = 1;
            continue;
          }
          free(copyLine);
      }
      count += countNumber(&head, argv[i], argv[i+1]); //add count number
      resultcount = count;
      flag += printYONSummary(&head, argv[i], argv[i+1]); //set a flag here to check print yes or no
      fclose(fileStream);
    }   
  }
  printf("%d\n", resultcount);
  if(flag>=1){
    printf("yes\n");
  }else{
    printf("no\n");
  }
  // free memory as following
  free(line);
  Node *temp;
  while(head!=NULL){
    temp = head->next;
    free(head->cNode->value);
    free(head->cNode);
    free(head->value);
    free(head);
    head = temp;
  }
  return status;
}
//end
