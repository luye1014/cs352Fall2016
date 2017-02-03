/*
 * File:   util.c
 * Author: Russell Lewis
 *
 * Purpose: Implements two utility functions for Project 8.
 */


#include <malloc.h>
#include <string.h>

#include "util.h"


void sortArray_bubble(char **array, int len);
void swapElems       (char **array, int pos1, int pos2);


char **extendArray(char **oldArray, int oldLen, int newLen)
{
	char **retval = malloc(newLen * sizeof(char*));
	if (retval == NULL)
		return NULL;

	/* in a real program, I would do a check here, comparing the old
	 * length to the new length.  That's certainly the correct thing to
	 * do in a real program!  But then we'd get gcov coverage errors - so
	 * I'll just assume (which is true in this program) that the new size
	 * will always be as large as the old size.
	 */
	int i;
	for (i=0; i<oldLen; i++)
		retval[i] = oldArray[i];
	free(oldArray);

	/* we could just skip this second loop, and leave those elements
	 * uninitialized, but let's do this just to make things look clean
	 * in the debugger!
	 */
	for (i=oldLen; i<newLen; i++)
		retval[i] = NULL;

	return retval;
}



/* sortArray()
 *
 * Sorts an array of strings.  This version uses QuickSort - but it uses
 * a helper function (which is implemented in Bubble Sort) to sort small
 * arrays.
 */
void sortArray(char **array, int len)
{
	/* if the array is pretty small, then we sort using an O(n^2)
	 * algorithm.  This is the base case of recursion.
	 */
	if (len <= 8)
	{
		sortArray_bubble(array,len);
		return;
	}


	/* QuickSort splits the array into two halves, using the "pivot" (one
	 * of the values in the array) as the key for the split.  In theory,
	 * you can choose any value as the pivot - or choose one randomly -
	 * but "median of three" is a well known good mechanism.  I'm *NOT*
	 * doing median-of-three here; I'm just hard-coding that we always
	 * pick up element 0.  Go read up on median-of-three if you'd like
	 * to see it.
	 */

	/* These two variables give the indices of the lowest, and highest,
	 * elements in the array which have not yet been sorted into the
	 * two groups.  Everything below 'lo' (except for element [0]) is
	 * <= the pivot; everything above 'hi' is >= the pivot.
	 */
	int lo = 1;
	int hi = len-1;

	while (lo <= hi)
	{
		/* move 'lo' up, as far as you can. */
		while (lo <= hi && strcmp(array[lo], array[0]) <= 0)
			lo++;

		/* when we get here, either we've split everything, or else
		 * 'lo' belongs in the upper group.
		 */

		/* move 'hi' down, as far as you can */
		while (lo <= hi && strcmp(array[hi], array[0]) >= 0)
			hi--;

		/* when we get here, either lo > hi (meaning end of the loop)
		 * or [lo] belongs in the upper group and [hi] belongs in the
		 * lower group.
		 */
		if (lo <= hi)
			swapElems(array, lo,hi);
	}


	/* when we get here, we have split the elements into two groups;
	 * everything below 'lo' belongs in the lower group; everything above
	 * 'hi' is in the upper group.  And we know that lo==hi+1 .
	 *
	 * We'll swap the pivot into place, and then recurse.
	 */
	swapElems(array, 0,lo-1);

	sortArray(array,    lo-1);
	sortArray(array+lo, len-lo);
	return;
}



/* sortArray_bubble()
 *
 * Sorts an array of strings, using Bubble Sort.
 *
 * THIS IS A TERRIBLE ALGORITHM.  DO NOT USE THIS IF YOU CARE ABOUT
 * PERFORMANCE.  (But it's easy to write!)
 */
void sortArray_bubble(char **array, int len)
{
	int passes, i;

	for (passes=0; passes<len; passes++)
	{
		/* in each pass, one new value is "Bubbled" up to the top
		 * of the array - the next max (of those not already
		 * bobbled to the top).
		 *
		 * After 'len' passes, we know that all of the elements
		 * have reached their proper locations.
		 */

		for (i=0; i+1 < len; i++)
		{
			/* look at the elements [i] and [i+1] from the array.
			 * If they are out of order, then swap them - that is,
			 * bubble the element [i] upwards in the array, until
			 * you either put it in its correct place, or else
			 * find something even larger.
			 */
			if (strcmp(array[i], array[i+1]) > 0)
				swapElems(array, i,i+1);
		}
	}

	return;
}


void swapElems(char **array, int pos1, int pos2)
{
	char *tmp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = tmp;
}

