/* File: graphTools.h
 * Author: Eric Anson
 * Purpose: Header file for makeThis project
*/

#ifndef _GRAPHTOOLS_H
#define _GRAPHTOOLS_H

//Typedefs
typedef struct comms {
  char *str;
  struct comms *next;
} command;

typedef struct n {
  char *name;
  struct e *deps;
  int visited;
  int target;		//tells whether this is a target or dependent
  command *commands;
  struct n *next;
} node;

typedef struct e {
  node *dep;
  struct e *next;
} edge;

//Globals
extern int errSeen;
extern node *hd;

//prototypes

command *addCmd(node *, char *);
edge *addDep(node *, char *);
node *addNode(char *targ);
node *findNode(char *targ);
void freeGraph();
void printList();
void travGraph(char *);
#endif