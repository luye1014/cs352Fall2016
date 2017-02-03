/*
 * File:   linkedList.c
 * Author: Russell Lewis
 *
 * Purpose: Implements code to execute (and test) a simple linked list.
 */


#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>    /* for perror() */
#include <stdlib.h>   /* for exit()   */


struct LLNode
{
	struct LLNode *next;

	char name[20];
	int  num;
};
typedef struct LLNode LLNode;

/* Style Hint:
 * -----------
 *
 * The above declaration is probably the simplest way to define a
 * struct-and-its-typedef.  However, there are a couple of alternatives.
 *
 * VERSION B
 *
 *      typedef struct LLNode
 *      {
 *          struct LLNode *next;
 *
 *          char name[20];
 *          int  num;
 *      } LLNode;
 *
 * VERSION C
 *
 *      typedef struct LLNode LLNode;   // it's amazing that this is legal
 *      struct LLNode
 *      {
 *          struct LLNode *next;
 *
 *          char name[20];
 *          int  num;
 *      };
 */




/* Style Hint:
 * -----------
 *
 * I (Russ) like to us the x=modify(x) style of code.  In this style, you pass
 * a pointer to the current data structure as a parameter, and return the new
 * pointer at the end.
 *
 * Very often, the pointer that you return will be the same as you started
 * with (since you are inserting or deleting in the middle).  However,
 * sometimes it is different - as when you insert/delete at the head, when you
 * insert into a previously-empty list, or when you remove the last element,
 * etc.
 *
 * The cool thing about the x=modify(x) style is that you don't need a global
 * 'head' pointer - you can have a local head pointer, which changes over
 * time.  For trivial programs, the difference is tiny - but for larger, more
 * realistic programs, it's important because now you can support *MULTIPLE
 * LISTS* without changing the list code!
 */
void             printList(LLNode *head);
LLNode *    insertIntoList(LLNode *head, char *name, int num);
LLNode *    deleteFromList(LLNode *head, char *name);
LLNode *removeHeadFromList(LLNode *head);



/* this is a global - instead of a local of main() - because we have to
 * modify in the various helper functions.
 *
 * We could avoid this by passing a pointer to the retval as a parameter to
 * each function.  That would be the "right" way to do it, perhaps - but it
 * feels like such a hack!
 *
 * If I was writing a linked-list library, I'd have a better design, that
 * doesn't use *ANY* global variables.  But I'll live with it for this
 * program.
 */
int retval = 0;



int main()
{
	LLNode *head = NULL;

	while (1)
	{
		/* read in the initial buffer. */
		char line[81];
		if (fgets(line, sizeof(line), stdin) == NULL)
			break;

		/* did the line end with a newline?  If not, then report
		 * an error and die.
		 */
		int lineLen = strlen(line);
		if (line[lineLen-1] != '\n')
		{
			fprintf(stderr, "ERROR: A line in the input was longer than 80 characters (including the newline).\n");
			return 1;
		}


		/* handle truly empty lines.  Note that a bunch of spaces
		 * is *NOT* a truly empty line.
		 */
		if (line[0] == '\n')
			continue;


		/* ok, so the line is valid (at least, the length is valid.
		 *
		 * Now parse it into smaller pieces.  Note that we've made
		 * both of the character buffers longer than required, in
		 * order to detect the possibility that the names might be
		 * too long.
		 */
		char command[40];
		char name   [40];
		int  num;

		int rc = sscanf(line, "%39s %39s %d", command, name, &num);
		if (rc < 1)
		{
			/* Note that we do not add a \n at the end ON PURPOSE.
			 * That's because the line already has one.
			 */

			fprintf(stderr, "ERROR: The following line was not recognized as a valid command (sscanf() could not parse any elements): %s", line);

			retval = 1;
			continue;   // don't end, just go read the next
		}


		/* NOTE: When we get here, we know that we parsed a string
		 *       into the 'command' buffer, but that's all we know.
		 *       We don't know whether there were any other parsable
		 *       parameters or not.  That's OK; in some cases, we
		 *       don't care.  We'll check (as necessary) below, in
		 *       each command's processing.
		 */


		if (strcmp(command, "print") == 0)
		{
			/* for 'print', we don't care whether the other
			 * arguments were valid or not.  Just print the list.
			 */
			printList(head);
		}
		else if (strcmp(command, "insert") == 0)
		{
			if (rc < 3)
			{
				fprintf(stderr, "ERROR: Invalid command.  The 'insert' command requires that there be two parameters: a name, and an integer.  The line was: %s", line);

				retval = 1;
				continue;
			}

			/* is the name field too long?
			 *
			 * Note that it is VALID to use head (even if it is
			 * NULL in a sizeof() command.  sizeof() does *NOT*
			 * actually use the pointer - it just imagines what
			 * the size would be *IF* the pointer were valid.
			 */
			if (strlen(name) > sizeof(head->name)-1)
			{
				fprintf(stderr, "ERROR: Invalid command.  The 'name' parameter was too long.  The line was: %s", line);

				retval = 1;
				continue;   // don't end, just go read the next
			}


			/* perform the update */
			head = insertIntoList(head, name, num);
		}
		else if (strcmp(command, "delete") == 0)
		{
			if (rc < 2)
			{
				fprintf(stderr, "ERROR: Invalid command.  The 'delete' command requires that there be a parameter: the name.  The line was: %s", line);

				retval = 1;
				continue;
			}

			/* is the name field too long?
			 *
			 * It's kind of overkill to do this check, since a
			 * too-long name will, by definition, never match any
			 * name in the list.  But it's a nice, clean way to
			 * report the essential error.  It's not necesasry,
			 * but it's a good habit.
			 */
			if (strlen(name) > sizeof(head->name)-1)
			{
				fprintf(stderr, "ERROR: Invalid command.  The 'name' parameter was too long.  The line was: %s", line);

				retval = 1;
				continue;   // don't end, just go read the next
			}


			head = deleteFromList(head, name);
		}
		else if (strcmp(command, "removeHead") == 0)
		{
			head = removeHeadFromList(head);
		}
		else
		{
			fprintf(stderr, "ERROR: Unrecognized command.  The line was: %s", line);

			retval = 1;
			continue;
		}
	}

	return retval;
}



/* printList(LLNode*)
 *
 * Iterates through the list.  Prints out its length, and then the value in
 * each node of the list.
 */
void printList(LLNode *head)
{
	LLNode *cur;


	/* how long is the list?  Print out the answer once you find it. */
	int count = 0;
	cur = head;
	while (cur != NULL)
	{
		count++;
		cur = cur->next;
	}
	printf("%d:", count);   // don't print space here, do it later.


	/* now, start over from the beginning, and print out all of the
	 * elements.
	 */
	cur = head;
	while (cur != NULL)
	{
		// leading space *BEFORE* each element!
		printf(" %s/%d", cur->name, cur->num);
		cur = cur->next;
	}


	/* print the newline before the end */
	printf("\n");
	return;
}



/* insertIntoList(LLNode*, char*, int)
 *
 * Scans through the list, and inserts a new node in the proper location.
 * Includes code to allocate the node.
 *
 * Returns the new head of the list; often, the head is unchanged (because
 * the new node was inserted someplace after it), but sometimes it is the
 * new node.
 *
 * If the name is a duplicate, then this will print an error to stderr, and
 * set (global) retval to 1; however, it returns an (unmodified) head pointer.
 * Thus, the calling code doesn't have to check the return value for any
 * error condition.
 */
LLNode *insertIntoList(LLNode *head, char *name, int num)
{
	/* search for the correct position.  Note the use of a pointer-pointer
	 * here to eliminate the need for special-case code dealing with an
	 * empty list.
	 */

	/* Style Note:
	 * -----------
	 * A pointer-pointer is an unusual but efficient way to implement
	 * this.  Without a pointer-pointer, you have to cover two cases:
	 *      - We need to append to the tail (including the case of
	 *        an empty string)
	 *      - We need to insert *BEFORE* a node
	 *
	 * You thus tend to compare the key value to the key in the *NEXT*
	 * element, which is a little hard to read.  And worse, you have to
	 * insert in two ways: sometimes you modify the head, and sometimes
	 * you don't.
	 *
	 * The pointer-pointer eliminates that problem.  The pointer-pointer
	 * always stores the pointer that we will modify if we insert "here".
	 * When the loop begins, this actually points to the head pointer -
	 * meaning that when we insert, we are modifying the head pointer
	 * directly!  However, as soon as we move into the list, the
	 * pointer-pointer points to a 'next' field *INSIDE* one of the other
	 * structs.
	 *
	 * In general, 'cur' stores the node we're looking at (which could
	 * be NULL), and 'ptrInPrev' points at the pointer *VARIABLE* that
	 * we used to find 'cur'.
	 */

	LLNode  *cur       =  head;
	LLNode **ptrInPrev = &head;

	while (cur != NULL && strcmp(cur->name, name) < 0)
	{
		ptrInPrev = &cur->next;
		cur       =  cur->next;
	}


	/* when we get here, either 'cur' is NULL, or cur->name is greater
	 * than or equal to name.  If they are equal, then print an error;
	 * if not, then insert *BEFORE* cur.  Note that it's possible that
	 * 'cur' might be the head of the list, but that won't matter.
	 */
	if (cur != NULL && strcmp(cur->name, name) == 0)
	{
		fprintf(stderr, "ERROR: Could not insert into the list: duplicate name '%s'\n", name);

		retval = 1;
		return head;
	}


	/* allocate the node; fill in its fields; then add it to the list */
	LLNode *newNode = malloc(sizeof(LLNode));
	if (newNode == NULL)
	{
		perror("Failed to allocate a new node for the linked list");
		exit(1);
	}

	strcpy(newNode->name, name);
	newNode->num = num;

	newNode->next = cur;
	*ptrInPrev = newNode;

	/* if we inserted in the middle, then 'ptrInPrev' was part of a
	 * previous node struct, and so the head hasn't changed.  But if
	 * we inserted at the head, then 'ptrInPrev' actually pointed at our
	 * own 'head' parameter!
	 *
	 * Either way, 'head' still/now contains the head of the updated list.
	 */
	return head;
}



/* deleteFromList(LLNode*, char*)
 *
 * Scans through the list, and deletes the appropriate node (the one that
 * matches this name).  It also frees the memory for that node.
 *
 * Returns the new head of the list; often, the head is unchanged (because
 * the new node was deleted someplace after it), but sometimes the head has
 * changed.  If the list is now empty, this will return NULL.
 *
 * If the name is not found, then this will print an error to stderr, and
 * set (global) retval to 1; however, it returns an (unmodified) head pointer.
 * Thus, the calling code doesn't have to check the return value for any
 * error condition.
 */
LLNode *deleteFromList(LLNode *head, char *name)
{
	/* search through the list; we keep a pointer-pointer to the
	 * pointer that we will modify if/when we delete a node.
	 */
	LLNode  *cur       =  head;
	LLNode **ptrInPrev = &head;

	while (cur != NULL && strcmp(cur->name, name) < 0)
	{
		ptrInPrev = &cur->next;
		cur       =  cur->next;
	}

	/* when we get here, either 'cur' is NULL, or 'cur->name' is less than
	 * or equal to 'name.'  If 'cur' is NULL or if 'cur->name' is less
	 * than 'name,' then the name didn't exist in the list.
	 */
	if (cur == NULL || strcmp(cur->name, name) > 0)
	{
		fprintf(stderr, "ERROR: Could not delete '%s' from the list, it did not exist.\n", name);

		retval = 1;
		return head;
	}


	/* remove the element.  Note that the solution here uses free() -
	 * since that's always a good idea - even though the spec doesn't
	 * require it.
	 */
	*ptrInPrev = cur->next;   // could be NULL
	free(cur);

	/* see the comment at the end of insert() above; 'head' is now the
	 * pointer to the updated list, no matter what we removed.
	 */
	return head;
}



/* removeHeadFromList(LLNode*)
 *
 * Removes the head node from the list, and frees the memory; returns the new
 * head pointer.  If the list is now empty, this will return NULL.
 *
 * If the list was already empty, then this will print an error to stderr, and
 * set (global) retval to 1; however, it returns an (unmodified) head pointer.
 * Thus, the calling code doesn't have to check the return value for any
 * error condition.
 */
LLNode *removeHeadFromList(LLNode *head)
{
	if (head == NULL)
	{
		fprintf(stderr, "ERROR: Could not remove the head from the list; the list was empty.\n");

		retval = 1;
		return head;
	}

	LLNode *retval = head->next;   // could be NULL

	/* like in delete(), we free() the node, even though the spec
	 * doesn't require that.
	 */
	free(head);

	return retval;
}
