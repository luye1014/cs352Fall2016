/*
 * File:   linkedList.c
 * Author: Russell Lewis
 *
 * Purpose: Implements code to execute (and test) a simple linked list.
 */


#include <stdio.h>
#include <malloc.h>


typedef struct Line Line;
struct Line
{
	Line     *next;
	int       tokenCount;
	char    **tokens;
};



Line *breakIntoTokens(char *buf);

int main()
{
	int retval = 0;

	Line *head = NULL;
	Line *tail = NULL;

	int totalLines  = 0;
	int totalTokens = 0;


	/* read through the input, one line at a time.  I do this inside the
	 * while() loop, instead of inside the condition, because we need to
	 * reset to a fresh buffer every time - since the buffer we read in
	 * the previous line is saved (implicitly) through the linked list
	 * above.
	 */
	while (1)
	{
		char   *buf = NULL;
		size_t  len = 0;

		int rc = getline(&buf, &len, stdin);
		if (rc == -1)
			break;    // EOF


		/* we use a function to break the line into tokens.  It
		 * malloc()s everything that we need to do; we add it to
		 * the linked list, at the end.
		 */
		Line *newLine = breakIntoTokens(buf);
		if (newLine == NULL)
		{
			// NOTE TO GRADERS:
			//
			// This code only runs if malloc() fails, and so
			// breakIntoTokens() returns NULL.  We assume that
			// breakIntoTokens() has reported the error; we
			// only need to terminate the program.
			return 1;
		}


		/* if this is the first line that we've read, then this line
		 * becomes the head (and tail); otherwise, we chain this to
		 * the old tail.
		 */
		if (head == NULL)
			head = tail = newLine;
		else
		{
			tail->next = newLine;
			tail       = newLine;
		}


		totalLines  ++;
		totalTokens += newLine->tokenCount;
	}


	/* now, print out all of the information! */
	printf("Lines=%d Tokens=%d\n", totalLines, totalTokens);

	Line *curLine = head;
	int   lineNo  = 0;

	while (curLine != NULL)
	{
		printf("Line=%d Tokens: %d\n", lineNo, curLine->tokenCount);

		int t;
		for (t=0; t<curLine->tokenCount; t++)
			printf("  Line=%d Token=%d: \"%s\"\n", lineNo,t, curLine->tokens[t]);

		curLine = curLine->next;
		lineNo++;
	}


	return retval;
}



/* breakIntoTokens(char*)
 *
 * Input:  A String
 * Output: A Line object
 *
 * Scans through a string, and identifies all of the tokens.  Adds null
 * temrinators as needed to break the string into smaller pieces; stores
 * an array of pointers to tokens, which is saved inside the Line object
 * which is (allocated and) returned.
 */
Line *breakIntoTokens(char *buf)
{
	/* there are a couple of ways to do this.  One option would be to
	 * gradually expand our array of token-pointers over time, as we
	 * find new tokens; another (the one we choose here) is to scan
	 * the string first, counting tokens.  Once we know the count, we
	 * can malloc the array once - and we'll never need to reallocate it.
	 */

	int count = 0;

	int pos   = 0;
	while (buf[pos] != '\0')
	{
		/* consume whitespace, until we hit either a null terminator,
		 * or non-whitespace characters.
		 */
		while (buf[pos] == ' '  ||
		       buf[pos] == '\t' ||
		       buf[pos] == '\n')
		{
			pos++;
		}

		/* if we are at a null terminator, then we're done with the
		 * count.
		 */
		if (buf[pos] == '\0')
			break;

		/* we are *NOT* at a null terminator!  We have found a new
		 * token (update the count) and then consume the characters
		 * of the token.  The token ends at whitespace or a null
		 * terminator.
		 */
		count++;

		while (buf[pos] != ' '  &&
		       buf[pos] != '\t' &&
		       buf[pos] != '\n' &&
		       buf[pos] != '\0')
		{
			pos++;
		}
	}


	/* when we get here, 'count' is the number of tokens in the line
	 * (could be zero).  It's time to malloc() everything: a struct for
	 * the linked list, and (if the count is nonzero) an array.
	 */
	Line *retval = malloc(sizeof(Line));
	if (retval == NULL)
	{
		fprintf(stderr, "ERROR: Could not malloc() a new Line\n");
		return NULL;
	}


	/* no matter what 'count' is, we set next to NULL, since this is a
	 * brand-new list element, at the tail of the list.  We can also
	 * store the count now.
	 */
	retval->next = NULL;
	retval->tokenCount = count;


	if (count == 0)
	{
		/* simple case: no need to allocate the array. */
		retval->tokens = NULL;
		return retval;
	}


	/* general case: we need to allocate an array.  It might be tiny,
	 * or it might be huge.
	 */
	retval->tokens = malloc(count * sizeof(char*));
	if (retval->tokens == NULL)
	{
		fprintf(stderr, "ERROR: Could not allocate an array for token pointers.\n");

		free(retval);    // always a good idea to clean up!
		return NULL;
	}


	/* read all of the token pointers into the array.  While we sweep
	 * through the buffer, we'll also terminate the tokens that we find.
	 */
	pos = 0;
	int i;
	for (i=0; i<count; i++)
	{
		/* scan forward through the string until we find a
		 * non-whitespace character.
		 */
		while (buf[pos] == ' '  ||
		       buf[pos] == '\t' ||
		       buf[pos] == '\n')
		{
			pos++;
		}


		/* we are at the beginning of a token; record the pointer. */
		retval->tokens[i] = buf+pos;


		/* scan forward through the string until we find the end of
		 * the token - which could be whitespace, or a null
		 * termintor.
		 */
		while (buf[pos] != ' '  &&
		       buf[pos] != '\t' &&
		       buf[pos] != '\n' &&
		       buf[pos] != '\0')
		{
			pos++;
		}


		/* when we get here, we are at the first character *AFTER* a
		 * token; normally, it will be whitespace (perhaps newline),
		 * but theoretically it might be a null terminator.  Termiante
		 * the token, then step beyond it before we start looking for
		 * the next token in the string.
		 */
		buf[pos] = '\0';
		pos++;
	}


	return retval;
}

