#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

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

//int countForSameNumber = 0;

void printList(Node *head){
  Node *cur = head;
  while(cur!=NULL){
    printf("|%s|", cur->value);
 //    while(cur->cNode!=NULL){
  if(cur->cNode != NULL){
    printf("->%s->",cur->cNode->value);
  }
 //     cur->cNode = cur->cNode->next;
  // }
    cur = cur->next;
  }
  printf("\n");
}

// int countNumber(Node **head, char*cmdNum1, char*cmdNum2){
//   // printf("%s %s\n",cmdNum2, cmdNum1 );
//   // printList(head);
//   int count = 0;
//   Node *cur = *head;
//   //printList(cur);
//   while(cur!=NULL){
//     if(strcmp(cur->value, cmdNum1)==0||strcmp(cur->value, cmdNum2)==0){
//       if(cur->cNode != NULL){
//         if(strcmp(cur->cNode->value, cmdNum1)==0||strcmp(cur->cNode->value, cmdNum2)==0){
//         count++;
//         }
//       //cur->cNode = cur->cNode->next;
//       } 
//     }
//     cur = cur->next;
//   }
//   return count;
//   //printf("|%s|", cur->value);
//   //printf("\n");
// }

int countNumber(Node **head, char*cmdNum1, char*cmdNum2){
  int count = 0;
  Node *cur = *head;
  if(strcmp(cmdNum2, cmdNum1) != 0){
    while(cur!=NULL){
      if(strcmp(cur->value, strdup(cmdNum1)) == 0 && strcmp(cur->cNode->value, strdup(cmdNum2)) == 0){
        count++;
      }else if(strcmp(cur->value, strdup(cmdNum2)) == 0 && strcmp(cur->cNode->value, strdup(cmdNum1)) == 0){
        count++;
      }
    cur = cur->next;
    }
  }
  return count;

}

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
    //fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
  }
  else{
    while(currentList->next!=NULL){
      currentList = currentList->next;
      if(strcmp(currentList->value, data) == 0){
        //fprintf(stderr, "ERROR: Could not insert into the list: duplicate name");
      }
    }
    currentList->next = newNode;
  }

}

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

int printYONSummary(Node **head, char*cmdNum1, char*cmdNum2){
  int flag = 0;
  Node *numersList = NULL;
  Node *numersList2 = NULL;
  Node *cur = *head;
  // printList(*head);
  // printf("--->%s\n", cmdNum2);
  // printf("--->%s\n", cmdNum1);
  while(cur!=NULL){
    if(cur->cNode != NULL){
      // printf("%s\n", cur->value);
      // printf("%s\n", cur->cNode->value);
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
  // count++;
  cur = cur->next;
  }
  // printList(numersList);
  // printList(numersList2);
  //if(strcmp(cmdNum2, cmdNum1)!=0){
    flag = compare(&numersList, &numersList2);
  // }else{
  //   if(countForSameNumber>0){
  //     flag = 1;
  //   }
  // }
  return flag;
    
}

Node *insertIntoList(Node *head, char *data, char* linkedObj)
{
  Node  *cur       =  head;
  Node **ptrInPrev = &head;

  while (cur != NULL && strcmp(cur->value, data) < 0)
  {
    ptrInPrev = &cur->next;
    cur       =  cur->next;
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
            // if((strcmp(line, "\n")==0)){
            //   continue;
            // }
            char *targetNum = strtok(line, " \n");
            if(targetNum=='\0'){
              continue;
            }
            char *targetNum2 = strtok(NULL, "\n");
            if(targetNum2=='\0'){
              fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", targetNum);
              status = 1;
              continue;
            }
            if(strlen(targetNum)!=8||strlen(targetNum2)!=8){
              fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", aline);
               status = 1;
               continue;
            }
            // if(checkNumberformat(targetNum)==1||checkNumberformat(targetNum2)==1){//wrong format
            //   fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", copyLine);
            //   status = 1;
            // // }else if(checkNumberformat(targetNum2)==1){//wrong format
            // //   fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", targetNum2);
            // }
            if(strcmp(targetNum, "\n")!=0&&strcmp(targetNum,"\t")!=0&&strcmp(targetNum," ")!=0){
              // if(strcmp(targetNum2,targetNum)==0){
              //   fprintf(stderr, "ERROR: Rejecting a line which has duplicate phone numbers.\n");
              //   status = 1;
              // }else{
              if(checkNumberformat(targetNum)==1 || checkNumberformat(targetNum2)==1){ //This line check the number format
                fprintf(stderr, "ERROR: One or both of the phone numbers was invalid.  phone1='%s' phone2='%s'\n", targetNum, targetNum2);
                status = 1;
                continue;
              }
              else if(strcmp(targetNum2,targetNum)==0){
                fprintf(stderr, "ERROR: Rejecting a line which has duplicate phone numbers.\n");
                status = 1;
                continue;
              }
              head = insertIntoList(head, strdup(targetNum), strdup(targetNum2));
             // printList(head);
              //}
            }
          } 
          else{
             // if ((line)[strlen(line)-1] == '\n'){//end with a new line
                char *invalidLine = strtok(line, "\n");
                fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", invalidLine);
              //   status = 1;
              // }else{
              //   fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", line);
              //   status = 1;
              // }
          }
      }
      count += countNumber(&head, argv[i], argv[i+1]);
      resultcount = count;
      flag += printYONSummary(&head, argv[i], argv[i+1]);
      fclose(fileStream);
    }   
  }
  printf("%d\n", resultcount);
  if(flag>=1){
    printf("yes\n");
  }else{
    printf("no\n");
  }
  //fclose(fileStream);
  return status;
}



