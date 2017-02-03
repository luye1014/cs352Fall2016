/* File: makeThis.c
 * Author: Eric Anson
 * Purpose: write my own version of the make program
*/

#include "graphTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* char *trimEnd(char *str) - removes white space from the end of str by placing
 * a '\0' to change where the string ends. It returns str
*/
char *trimEnd(char *str) {
  int len;
  len = strlen(str)-1;
  while (len >= 0 && isspace(str[len])) 
    --len;
  str[++len] = '\0';
  return str;
} 

/* int readFile(FILE *mfile)
   reads the make file and builds the dependency graph. If there is an
   error in the file it returns 0, otherwise it returns 1
*/
int readFile(FILE *mfile) {
  char *buff=NULL;
  char *ptr, *endPtr, *tptr;
  size_t sz=0;
  node *lastNode=NULL;
  int done;

  while(getline(&buff, &sz, mfile) > 0) {
    trimEnd(buff);
    if (strlen(buff) == 0)
      continue;		//blank line
    ptr = buff;
    while (isspace(*ptr))
      ++ptr;
    if (buff[0] == '\t') {
      if (lastNode == NULL) {
        fprintf(stderr,"Error in file, command with no target\n");
        free(buff);
        return 0;
      }
      addCmd(lastNode, ptr);
    } else { 
      for (endPtr = ptr; *endPtr != '\0' && *endPtr != ':'; ++endPtr) ;
      if (endPtr == ptr) {
        fprintf(stderr,"Missing target in line: %s\n", ptr);
        free(buff);
        return 0;
      }
      if (*endPtr != ':') {
        fprintf(stderr,"Illegal line: %s\n", buff);
        free(buff);
        return 0;
      }
      *endPtr = '\0';
      tptr = endPtr-1;
      while (isspace(*tptr)) {
        *tptr = '\0';
        --tptr;
      }
      for (tptr = ptr; *tptr; ++tptr) {
        if (isspace(*tptr)) {
          fprintf(stderr, "Multiple targets defined: %s\n", ptr);
          free(buff);
          return 0;
        }
      }
      if ((lastNode = findNode(ptr)) == NULL) {
        lastNode = addNode(ptr);
      } else if (lastNode->target) {
          fprintf(stderr,"Repeated target: %s\n", ptr);
          free(buff);
          return 0;
      }
      lastNode->target = 1;
      done = 0;
      while (!done) {
        ptr = endPtr+1;
        while (isspace(*ptr))
          ++ptr;
        if (*ptr == '\0')
          break;
        endPtr = ptr+1;
        while (*endPtr != '\0' && !isspace(*endPtr))
          ++endPtr;
        if (*endPtr == '\0')
          done = 1;
        *endPtr = '\0';
        addDep(lastNode, ptr);
      }
    }
  }
  free(buff);
  return 1;
}

int main(int argc, char *argv[])
{
  char *target = NULL;
  char *fileName = "makefileDefault";
  FILE *mFile;

  if (argc > 4) {
    fprintf(stderr, "Usage: %s [-f <file>] [target]\n", argv[0]);
    return 1;
  }

  /* Usually you would check your arguments in a loop. However, since there
     are so few possibilities in this case, I'm using an if block */
  if (argc == 2) {
    if (!strcmp(argv[1],"-f")) {
      fprintf(stderr,"Missing file name\n");
      return 1;
    }
    target = argv[1];
  } else if (argc == 3) {
    if (strcmp(argv[1],"-f")) {	//not correct options
      fprintf(stderr, "Usage: %s [-f <file>] [target]\n", argv[0]);
      return 1;
    }
    fileName = argv[2];
  } else if (argc == 4) {
    if (!strcmp(argv[1],"-f")) {
      fileName = argv[2];
      target = argv[3];
    } else if (!strcmp(argv[2],"-f")) {
      fileName = argv[3];
      target = argv[1];
    } else {
      fprintf(stderr, "Usage: %s [-f <file>] [target]\n", argv[0]);
      return 1;
     }
  }

  mFile = fopen(fileName,"r");
  if (mFile == NULL) {
    perror(fileName);
    return 1;
  }
  if (!readFile(mFile)) {
    fclose(mFile);
    freeGraph();
    return 1;
  }
  fclose(mFile);
//  printList();
  if (target == NULL) {
    if (hd != NULL) {
      target = hd->name;
    } else {
      fprintf(stderr, "%s: *** No Target \n", argv[0]);
      return 1;	//no need to free since list is empty
    }
  }
  travGraph(target);
  freeGraph();
  return errSeen;
}