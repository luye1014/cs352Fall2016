/* File: graphTools.c
 * Author: Eric Anson
 * Purpose: This program contains functions for manipulating the graph
*/

#include "graphTools.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int errSeen=0;
node *hd=NULL;

/* freeGraph() frees the memory taken by the dependency graph */
void freeGraph() {
  node *nptr, *nptr2;
  edge *eptr, *eptr2;
  command *cptr, *cptr2;

  nptr = hd;
  while (nptr != NULL) {
    nptr2 = nptr->next;
    free(nptr->name);
    cptr = nptr->commands;
    while (cptr != NULL) {
      cptr2 = cptr->next;
      free(cptr->str);
      free(cptr);
      cptr = cptr2;
    }
    eptr = nptr->deps;
    while (eptr != NULL) {
      eptr2 = eptr->next;
      free(eptr);
      eptr = eptr2;
    }
    free(nptr);
    nptr = nptr2;
  }
  return;
}

/*postOrder(node *n) does a postorder search of node n, this is a
  recursive routine */
void postOrder(node *n) {
  edge *dep;
  command *cmd;

  n->visited = 1;
  for (dep = n->deps; dep != NULL; dep = dep->next) {
    if (dep->dep->visited == 1) {
      fprintf(stderr,"makeThis: Circular %s <- %s dependency dropped\n",n->name,dep->dep->name);
      errSeen = 1;
    } else if (!dep->dep->visited) {
      postOrder(dep->dep);
    }
  }
  printf("%s\n", n->name);
  for (cmd = n->commands; cmd != NULL; cmd = cmd->next)
    printf("  %s\n", cmd->str);
  n->visited = 2;
}

/* travGraph(char *t) Does a post-order traversal of the dependency graph
  starting at the target t
*/
void travGraph(char *t) {
  node *root;

  for (root = hd; root != NULL; root = root->next)
    if (!strcmp(root->name, t))
      break;
  if (root == NULL || !root->target) {
    fprintf(stderr,"Target %s not found\n", t);
    errSeen = 1;
    return;
  }
  postOrder(root);
  return;
}

/* node *findNode(char *targ) looks for a node with name targ in the
 * linked list. It returns a pointer to the node if found or NULL if not */
node *findNode(char *targ) {
  node *ptr;
  for (ptr = hd; ptr != NULL; ptr = ptr->next) {
    if (!strcmp(targ, ptr->name))
      return ptr;
  }

  return ptr;
}

/* node addNode(char *targ) adds a node to the bottom of the linked list
   copies targ to its name, and returns a pointer to the new node */
node *addNode(char *targ) {
  node **last = &hd;
  node *ptr = hd;

  while (ptr != NULL) {
    last = &(ptr->next);
    ptr = ptr->next;
  }
  ptr = malloc(sizeof(node));
  if (ptr == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }
  ptr->name = strdup(targ);
  ptr->deps = NULL;
  ptr->visited = 0;
  ptr->target = 0;
  ptr->commands = NULL;
  ptr->next = NULL;
  *last = ptr;
  return ptr;
}

/*adds a element to the list of commands and copies str to the str 
  and returns a pointer to the new command*/
command *addCmd(node *targ, char *str) {
  command **last;
  command *ptr;
  last = &targ->commands;
  ptr = targ->commands;
  while(ptr != NULL) {
    last = &(ptr->next);
    ptr = ptr->next;
  }
  ptr = malloc(sizeof(command));
  if (ptr == NULL) {
    fprintf(stderr,"Out of memory\n");
    exit(1);
  }
  *last = ptr;
  ptr->next = NULL;
  ptr->str = strdup(str);
  return ptr;
}

/*adds a element to the list of edges pointing to the target with name dep
  and returns a pointer to the new edge*/
edge *addDep(node *targ, char *dep) {
  edge **last;
  edge *ptr;
  node *depNode;

  depNode = hd;
  while (depNode != NULL) {
    if (strcmp(depNode->name, dep) == 0)
      break;
    depNode = depNode->next;
  }
  if (depNode == NULL) {
    depNode = addNode(dep);
  }
  last = &targ->deps;
  ptr = targ->deps;
  while(ptr != NULL) {
    last = &(ptr->next);
    ptr = ptr->next;
  }
  ptr = malloc(sizeof(edge));
  if (ptr == NULL) {
    fprintf(stderr,"Out of memory\n");
    exit(1);
  }
  *last = ptr;
  ptr->next = NULL;
  ptr->dep = depNode;
  return ptr;
}

/* void printList() prints the list for debugging purposes */
void printList() {
  node *nptr = hd;
  command *cmd;
  edge *dep;

  while (nptr != NULL) {
    printf("%s\n", nptr->name);
    printf("  Dependencies:\n");
    for (dep = nptr->deps; dep != NULL; dep = dep->next)
      printf("    %s\n", dep->dep->name);
    printf("  Commands\n");
    for (cmd = nptr->commands; cmd != NULL; cmd = cmd->next)
      printf("    %s\n", cmd->str);
    nptr = nptr->next;
  }
}