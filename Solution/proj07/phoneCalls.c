/*
 * File:   phoneCalls.c
 * Author: Russell Lewis
 *
 * Purpose: Implements code to search through a set of files (representing
 * phone calls) to find certain interesting connections.
 */

#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>



struct    BigList;
struct LittleList;

typedef struct    BigList    BigList;
typedef struct LittleList LittleList;

struct BigList
{
	BigList *next;

	int         phoneNumber;
	LittleList *littleHead;
};

struct LittleList
{
	LittleList *next;

	int phoneNumber;
	int callCount;
};



int parsePhoneNumber(char*);

BigList *addCall(BigList *list, int number1, int number2);

void freeList(BigList *list);



int main(int argc, char **argv)
{
	/* simple sanity checking - are there enough arguments?  Then we'll
	 * also check to see if the last two are valid phone numbers.
	 */
	if (argc < 4)
	{
		fprintf(stderr, "ERROR: Too few arguments.  Minimum args are <file1> <phone1> <phone2>\n");
		return 1;
	}

	int searchPhone1 = parsePhoneNumber(argv[argc-2]);
	int searchPhone2 = parsePhoneNumber(argv[argc-1]);

	if (searchPhone1 == -1 || searchPhone2 == -1)
	{
		fprintf(stderr, "ERROR: One or both of the phone numbers, at the end of the command line, are invalid.  num1='%s' num2='%s'\n", argv[argc-2], argv[argc-1]);
		return 1;
	}


	/* OK, sanity checking is done.  It's now time to start the main loop.
	 * Of course, we need to define the (empty) list first.
	 */
	BigList *bigHead = NULL;
	int      retval  = 0;

	int i;
	for (i=1; i<argc-2; i++)
	{
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL)
		{
			fprintf(stderr, "Arg %d (%s): ", i, argv[i]);
			  perror("Could not open one of the input files");

			retval = 1;
			continue;
		}


		/* we count how many lines are not blank.  If the file has
		 * only empty lines (or no lines at all), then we must report
		 * an error.
		 */
		int nonEmptyLines = 0;


		/* read all of the contents of the file, one at a time.  I'll
		 * use getline() for simplicity.
		 */
		char   *buf    = NULL;
		size_t  bufLen = 0;
		while (getline(&buf, &bufLen, fp) != -1)
		{
			/* We will, almost always, have a newline at the end;
			 * however, it's possible that we might lack one on
			 * the next line.  But whether it's there or not, we
			 * won't use it, so we'll remove it if it exists.
			 */
			int len = strlen(buf);
			if (len > 0 && buf[len-1] == '\n')
			{
				buf[len-1] = '\0';
				len--;
			}

			/* if we get here, then the newline (if any) has been
			 * removed.  If that's all there was, then we skip
			 * ahead to the next line; otherwise, we try to parse
			 * it.  Note that we have to keep track of whether we
			 * ever found any non-empty lines or not.
			 */
			if (len == 0)
				continue;
			else
				nonEmptyLines++;


			/* In this project, we will be *VERY* picky about the
			 * input.  So there are lots of simple reasons why we
			 * can reject it.  If all of these pass, then we will
			 * pass the two remaining 8-character strings to the
			 * parsing function, which will do its own checking.
			 */
			if (len != 17)
			{
				fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", buf);

				retval = 1;
				continue;
			}

			if (buf[8] != ' ')
			{
				fprintf(stderr, "ERROR: The line format is invalid.  Line: '%s'\n", buf);

				retval = 1;
				continue;
			}


			buf[8] = '\0';

			int phone1 = parsePhoneNumber(buf);
			int phone2 = parsePhoneNumber(buf+9);

			if (phone1 == -1 || phone2 == -1)
			{
				fprintf(stderr, "ERROR: One or both of the phone numbers was invalid.  phone1='%s' phone2='%s'\n", buf, buf+9);

				retval = 1;
				continue;
			}


			/* if the phone numbers are identical, we must reject
			 * this line!
			 */
			if (phone1 == phone2)
			{
				fprintf(stderr, "ERROR: Rejecting a line which has duplicate phone numbers.\n");

				retval = 1;
				continue;
			}


			/* if we get here, then everything is valid - it's now
			 * time to insert the phone numbers into the data
			 * structure.
			 *
			 * This call returns the updated list; the only scenario
			 * in which it will return NULL is when there was a
			 * malloc() error - in which case, it will free all of
			 * the memory for the old version of the list.
			 */
			bigHead = addCall(bigHead, phone1,phone2);
			if (bigHead == NULL)
			{
				fprintf(stderr, "ERROR: malloc() failure somewhere in addCall(BigHead,int,int)\n");
				return 1;
			}

			/* UPDATE: remember to do this symmetrically! */
			bigHead = addCall(bigHead, phone2,phone1);
			if (bigHead == NULL)
			{
				fprintf(stderr, "ERROR: malloc() failure somewhere in addCall(BigHead,int,int)\n");
				return 1;
			}
		}


		/* do we have an empty file? */
		if (nonEmptyLines == 0)
		{
			fprintf(stderr, "ERROR: The file '%s' is empty.\n", argv[i]);
			retval = 1;
		}


		/* free the buffer (before we forget about it!) */
		free(buf);

		/* close the file to free resources */
		fclose(fp);
	}


	/* do the first search!  Does number1 exist in the Big List?  And if
	 * so, does number2 exist in the Little List inside it?
	 */
	BigList *curBig = bigHead;
	while (curBig != NULL && curBig->phoneNumber < searchPhone1)
		curBig = curBig->next;

	if (curBig == NULL || curBig->phoneNumber != searchPhone1)
	{
		printf("0\n");   // no match!

		// BUGFIX: If this number doesn't exist, then there's no point
		//         in even attempting the indirect-connection search!
		printf("no\n");
	}
	else
	{
		LittleList *curLittle = curBig->littleHead;
		while (curLittle != NULL && curLittle->phoneNumber < searchPhone2)
			curLittle = curLittle->next;

		if (curLittle == NULL || curLittle->phoneNumber != searchPhone2)
			printf("0\n");   // no match
		else
			printf("%d\n", curLittle->callCount);


		/* do the second search.  This requires that we search for *BOTH* of
		 * the first phone numbers in the Big List (we've already found one of
		 * them); then, we search through the matching Little Lists, looking
		 * for a matching number.  Since both Little Lists are sorted, we can
		 * do this in linear time, using an algorithm a lot like Merge Sort.
		 * (If the little lists weren't sorted, then it would be n^2.)
		 */
		BigList *hit1 = curBig;

		curBig = bigHead;
		while (curBig != NULL && curBig->phoneNumber < searchPhone2)
			curBig = curBig->next;

		if (curBig == NULL || curBig->phoneNumber != searchPhone2)
			printf("no\n");
		else
		{
			/* we've matched both of the numbers.  We now do the
			 * "MergeSort-esque" search of the little lists.
			 */
			LittleList *little1 =   hit1->littleHead;
			LittleList *little2 = curBig->littleHead;


			/* the loop ends if we hit the end of either little list, or
			 * if we find matching nodes.
			 */
			while (little1 != NULL && little2 != NULL &&
			       little1->phoneNumber != little2->phoneNumber)
			{
				/* neither list is NULL, but they also aren't matched;
				 * advanced the one that is earlier than the other.
				 */
				if (little1->phoneNumber < little2->phoneNumber)
					little1 = little1->next;
				else
					little2 = little2->next;
			}


			/* if we get here and one of the pointers is NULL, then we
			 * don't have a match; if they are both non-NULL, then we do!
			 */
			if (little1 == NULL || little2 == NULL)
				printf("no\n");
			else
				printf("yes\n");
		}
	}


	/* we're finally done!  Time to clean up, and then return */

	freeList(bigHead);
	return retval;
}



/* parsePhoneNumber()
 *
 * Input:  a string
 * Output: an integer, which is the phone number parsed into a
 *         seven-digit decimal number
 *
 * This will agressively parse check the input.  It then parses the input as
 * two integers, and converts them into an integer as if it was a simple,
 * seven digit number.
 */
int parsePhoneNumber(char *str)
{
	if (strlen(str) != 8)
		return -1;

	if ( ! isdigit(str[0]) || ! isdigit(str[1]) ||
	     ! isdigit(str[2]) ||   str[3] != '-'   ||
	     ! isdigit(str[4]) || ! isdigit(str[5]) ||
	     ! isdigit(str[6]) || ! isdigit(str[7]))
	{
		return -1;
	}

	int num0 = str[0] - '0';
	int num1 = str[1] - '0';
	int num2 = str[2] - '0';
	int num3 = str[4] - '0';
	int num4 = str[5] - '0';
	int num5 = str[6] - '0';
	int num6 = str[7] - '0';

	return num0 * 1000000 +
	       num1 * 100000  +
	       num2 * 10000   +
	       num3 * 1000    +
	       num4 * 100     +
	       num5 * 10      +
	       num6 * 1      ;
}



/* addCall()
 *
 * Input:  The old Big List, and two integers to add.
 * Output: The updated Big List
 *
 * This might require that we allocate a new node into the Big List (or maybe
 * it might not); it might also require that we allocate a new node to the
 * Little List (or it might not).
 *
 * This returns NULL if there is a memory error; it will also clean up the
 * entire list if this happens.
 */
BigList *addCall(BigList *list, int number1, int number2)
{
	BigList  *cur   =  list;
	BigList **pPrev = &list;

	/* our list is sorted (for efficiency) */
	while (cur != NULL && cur->phoneNumber < number1)
	{
		pPrev = &cur->next;
		cur   =  cur->next;
	}


	/* we either have found a match - or else we need to allocate a new
	 * node.
	 */
	if (cur == NULL || cur->phoneNumber > number1)
	{
		BigList *newNode = malloc(sizeof(BigList));
		if (newNode == NULL)
		{
			freeList(list);
			return NULL;
		}

		/* we allocate a node; put it into the list. */
		newNode->phoneNumber = number1;
		newNode->littleHead  = NULL;

		newNode->next = cur;
		*pPrev        = newNode;

		cur = newNode;
	}


	/* when we get here, 'cur' matches 'phone1' - either because we
	 * it already exists, or because we created it.
	 *
	 * Now, we search the little list for the correct place to insert
	 * phone2.  As with the Big List, it is sorted.
	 */
	LittleList  *cur2   =  cur->littleHead;
	LittleList **pPrev2 = &cur->littleHead;

	while (cur2 != NULL && cur2->phoneNumber < number2)
	{
		pPrev2 = &cur2->next;
		cur2   =  cur2->next;
	}

	if (cur2 == NULL || cur2->phoneNumber > number2)
	{
		LittleList *newNode = malloc(sizeof(LittleList));
		if (newNode == NULL)
		{
			freeList(list);
			return NULL;
		}

		newNode->phoneNumber = number2;
		newNode->callCount   = 0;

		newNode->next = cur2;
		*pPrev2       = newNode;

		cur2 = newNode;
	}


	/* when we get here, 'cur2' points at the proper node in the
	 * Little List.  Record that the call happened!
	 */
	cur2->callCount++;


	/* we've added the record to the Big List - now return the list,
	 * which may have been updated.
	 */
	return list;
}



/* freeList()
 *
 * Input:  The current list (which might be NULL)
 *
 * Frees all of the nodes (both Big and Little) in the current list.
 */
void freeList(BigList *list)
{
	BigList *curBig = list;
	while (curBig != NULL)
	{
		LittleList *curLittle = curBig->littleHead;
		while (curLittle)
		{
			/* free this little list node */
			LittleList *tmp = curLittle;
			curLittle = curLittle->next;

			free(tmp);
		}


		/* free the big list node before we move on. */
		BigList *tmp = curBig;
		curBig = curBig->next;

		free(tmp);
	}

	return;
}


