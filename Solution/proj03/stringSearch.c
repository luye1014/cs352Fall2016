/*
 * File:   stringSearch.c
 * Author: Russell Lewis
 *
 * Purpose: Reads a first string from stdin; then compares that string to all
 *          other strings on stdin.  Prints out strings which match the
 *          original, which match the original (reversed), or are a duplicate
 *          of the *previous* string read (regardless of the first string).
 */


#include <stdio.h>
#include <string.h>


int my_strcmp    (char *str1, char *str2);
int my_strcmp_rev(char *str1, char *str2);


int main()
{
	/* read the original string from the input; we'll keep this forever.
	 * If it doesn't exist, then it's a terminal error.
	 */
	char origStr[32];
	if (scanf("%31s", origStr) != 1)
	{
		fprintf(stderr, "ERROR: Could not read the first string from stdin!\n");
		return 1;
	}


	/* this is the buffer which will be used to store the previous string,
	 * so that we can perform the "dup" check.  In order to do the dup
	 * check on the next string, we'll need to have the origStr in there
	 * as well.
	 */
	char prevStr[32];
	strncpy(prevStr, origStr, sizeof(prevStr));


	/* loop until we've eaten all of stdin */
	int  retval = 0;
	char curStr[32];

	int strings=0;
	int matches=0, dups=0, revs=0;

	while (scanf("%31s", curStr) != EOF)
	{
		strings++;

		/* perform the three tests.  Note how the first uses a
		 * standard C library function, and the other two use
		 * functions that I've written, as required by the spec.
		 */

		if (strcmp(origStr, curStr) == 0)
		{
			printf("Mat: %s\n", curStr);
			matches++;
		}

		if (my_strcmp_rev(origStr, curStr) == 0)
		{
			printf("Rev: %s\n", curStr);
			revs++;
		}

		if (my_strcmp(prevStr, curStr) == 0)
		{
			printf("Dup: %s\n", curStr);
			dups++;
		}


		/* save curStr back into prevStr */
		strcpy(prevStr, curStr);
	}

	printf("Totals: strings=%d : m=%d r=%d d=%d\n",
	       strings, matches, revs, dups);

	return retval;
}


int my_strcmp(char *str1, char *str2)
{
	int i;

	for (i=0; str1[i] != '\0' && str2[i] != '\0'; i++)
		if (str1[i] != str2[i])
			return str1[i] - str2[i];

	/* when we get here, one of the two strings (maybe both) are at
	 * the null terminator.  If they *BOTH* are at the null terminator,
	 * then the difference here will be zero; else it will be non-zero.
	 */
	return str1[i] - str2[i];
}


int my_strcmp_rev(char *str1, char *str2)
{
	/* calculate the length of the two strings.  If the lengths are not
	 * the same, then we'll return nonzero immediately; if they *ARE*
	 * the same, then we'll run a loop to perform the comparison (though
	 * they will be reversed.
	 *
	 * Yeah, we could have unified the two loops into one...but that would
	 * be harder.  The first loop is pretty easy, since I can scan both
	 * strings *FORWARD*, even though we'll later reverse one of them.
	 */
	int len;
	for (len=0; str1[len] != '\0' && str2[len] != '\0'; len++)
	{ 
		/* NOP */
	}

	/* are *BOTH* at the null terminator, or just one of them? */
	if (str1[len] != '\0' || str2[len] != '\0')
		return str1[len] - str2[len];


	/* if we get here, then the two lengths are identical...now we'll
	 * compare the contents; we'll scan through str2 in reverse.
	 */

	int i;
	for (i=0; str1[i] != '\0'; i++)
		if (str1[i] != str2[len-1-i])
			return str1[i] - str2[len-1-i];

	/* if we get here, then the two strings were the same (though
	 * reversed).
	 */
	return 0;
}


