/*
 * File:   scanList.c
 * Author: Russell Lewis
 *
 * Purpose: Reads in a set of integers; then, given a set of other integers,
 *          counts how many times each of the "other" integers shows up in the
 *          first list.
 */


#include <stdio.h>
#include <malloc.h>


int main()
{
	int  arrLen;
	int *arr;

	int rc;
	int i;


	/* read the array length parameter; check its value */
	rc = scanf("%d", &arrLen);
	if (rc != 1)
	{
		fprintf(stderr, "ERROR: Could not read the array-size input.  rc=%d\n", rc);
		return 1;
	}

	if (arrLen < 0)
	{
		fprintf(stderr, "ERROR: The array-length parameter is negative.  arrLen=%d\n", arrLen);
		return 1;
	}


	/* allocate the array */
	arr = malloc(arrLen * sizeof(int));
	if (arr == NULL)
	{
		fprintf(stderr, "ERROR: Could not malloc() an array of length %d.\n", arrLen);
		return 1;
	}


	/* fill up the array */
	for (i=0; i<arrLen; i++)
	{
		rc = scanf("%d", &arr[i]);
		if (rc != 1)
		{
			fprintf(stderr, "ERROR: Could not read element %d into the array.  rc=%d\n", i, rc);
			return 1;
		}
	}

	printf("Comparison array (%d elements):", arrLen);
	for (i=0; i<arrLen; i++)
		printf(" %d", arr[i]);
	printf("\n");


	/* scan through the rest of the input. */
	while (1)
	{
		int searchFor;

		rc = scanf("%d", &searchFor);
		if (rc == EOF)
			break;   // normal termination, not an error
		if (rc == 0)
		{
			fprintf(stderr, "ERROR: Could not read one of the search elements from stdin.\n");
			return 1;
		}


		/* the value is valid; search for it. */
		int count = 0;
		for (i=0; i<arrLen; i++)
			if (arr[i] == searchFor)
				count++;
		printf("Number: %d count=%d\n", searchFor, count);
	}

	return 0;
}

