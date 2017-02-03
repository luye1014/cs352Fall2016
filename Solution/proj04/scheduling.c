/*
 * File:   scheduling.c
 * Author: Russell Lewis
 *
 * Purpose: Implements a hyper-simplified scheduling program; calculates the
 *          overlaps between a set of ranges in a space of discrete slots.
 */


#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>

int main()
{
	int  slotCount;
	int *slots;

	int  rc;
	int  i;

	int  retval = 0;


	/* read the schedule size first.  Then verify its length. */
	rc = scanf("%d", &slotCount);
	if (rc != 1)
	{
		fprintf(stderr, "ERROR: Could not read the schedule size from stdin.  rc=%d\n", rc);
		return 1;
	}

	if (slotCount < 1)
	{
		fprintf(stderr, "ERROR: The schedule size is not valid.  slotCount=%d\n", slotCount);
		return 1;
	}


	/* allocate the array */
	slots = malloc(slotCount * sizeof(int));
	if (slots == NULL)
	{
		fprintf(stderr, "ERROR: Could not malloc() the array for the schedule.  slotCount=%d\n", slotCount);
		return 1;
	}


	/* read all of the ranges from stdin */
	while (1)
	{
		int start,end;
		rc = scanf("%d %d", &start, &end);

		if (rc == EOF)
			break;    // normal termination, not an error

		if (rc != 2)
		{
			fprintf(stderr, "ERROR: Could not read the next range.  rc=%d\n", rc);
			return 1;
		}

		if (start < 0 || start >= slotCount ||
		    end   < 0 || end   >= slotCount)
		{
			fprintf(stderr, "ERROR: One or both of the endpoints of the current range is invalid.  slotCount=%d : start=%d end=%d\n", slotCount, start, end);
			retval = 1;
			continue;   // skip over it, and read the next pair.
		}

		if (start > end)
		{
			fprintf(stderr, "ERROR: start > end.  slotCount=%d : start=%d end=%d\n", slotCount, start, end);
			retval = 1;
			continue;   // go read the next range.
		}


		/* increment all of the elements in this range */
		for (i=start; i<=end; i++)
			slots[i]++;
	}


	/* print the summary */
	printf("%d:", slotCount);
	for (i=0; i<slotCount; i++)
		printf(" %d", slots[i]);
	printf("\n");


	/* scan through to find some of the basic elements */
	int min = slots[0], max = slots[0];
	for (i=1; i<slotCount; i++)
	{
		if (slots[i] < min)
			min = slots[i];
		if (slots[i] > max)
			max = slots[i];
	}

	printf("minimum: %d\n", min);

	printf("minimum-slots:");
	for (i=0; i<slotCount; i++)
		if (slots[i] == min)
			printf(" %d", i);
	printf("\n");

	printf("maximum: %d\n", max);

	printf("maximum-slots:");
	for (i=0; i<slotCount; i++)
		if (slots[i] == max)
			printf(" %d", i);
	printf("\n");

	int sum = 0;
	for (i=0; i<slotCount; i++)
		sum += slots[i];
	printf("average: %.2f\n", ((float)sum)/slotCount);

	return retval;
}

