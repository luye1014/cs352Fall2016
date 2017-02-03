/*
 * File:    arrFlex.c
 * Authors: Russell Lewis
 *
 * Purpose: Solution to Project 9.
 */


#include <malloc.h>
#include <memory.h>

#include "arrFlex.h"


/* private helper function.  'static' means that it is not available for
 * linking to other C files.
 */
static int arrFlex_realloc(ArrFlex *obj, int newSize);


ArrFlex *arrFlex_new()
{
	ArrFlex *retval = malloc(sizeof(ArrFlex));
	if (retval == NULL)
		return NULL;

	retval->capacity = 16;
	retval->curSize  = 0;

	retval->arr      = malloc(retval->capacity * sizeof(char));
	if (retval->arr == NULL)
	{
		free(retval);
		return NULL;
	}

	return retval;
}

void arrFlex_free(ArrFlex *obj)
{
	free(obj->arr);
	free(obj);
}


int arrFlex_set(ArrFlex *obj, int index, char val)
{
	if (index < 0 || index >= obj->curSize)
		return -1;

	obj->arr[index] = val;
	return 0;
}

int arrFlex_get(ArrFlex *obj, int index)
{
	if (index < 0 || index >= obj->curSize)
		return -1;

	return obj->arr[index];
}


ArrFlex *arrFlex_clone(ArrFlex *obj)
{
	ArrFlex *retval = malloc(sizeof(ArrFlex));
	if (retval == NULL)
		return NULL;

	retval->capacity = obj->capacity;
	retval->curSize  = obj->curSize;

	retval->arr = malloc(retval->capacity * sizeof(char));
	if (retval->arr == NULL)
	{
		free(retval);
		return NULL;
	}

	memcpy(retval->arr, obj->arr, obj->curSize * sizeof(char));

	return retval;
}


int arrFlex_size(ArrFlex *obj)
{
	return obj->curSize;
}

#if 0
int arrFlex_isEmpty(ArrFlex *obj)
{
	return obj->curSize == 0;
}


void arrFlex_clear(ArrFlex *obj)
{
	obj->curSize = 0;
	return;
}
#endif


int arrFlex_add(ArrFlex *obj, char newVal)
{
	if (obj->curSize == obj->capacity)
	{
		int rc = arrFlex_realloc(obj, obj->capacity*2);
		if (rc != 0)
			return -1;
	}

	obj->arr[obj->curSize] = newVal;
	obj->curSize++;

	return 0;
}


int arrFlex_append(ArrFlex *obj, ArrFlex *arrayToAdd)
{
	int newLen = obj->curSize + arrayToAdd->curSize;
	if (newLen > obj->capacity)
	{
		int rc = arrFlex_realloc(obj, newLen);
		if (rc != 0)
			return -1;
	}

	memcpy(obj->arr + obj->curSize,
	       arrayToAdd->arr,
	       arrayToAdd->curSize * sizeof(char));

	obj->curSize += arrayToAdd->curSize;

	return 0;
}


int arrFlex_insert(ArrFlex *obj, int index, char val)
{
	/* check if the index is invalid */
	if (index < 0 || index > obj->curSize)
		return -1;

	/* if the array capacity is full, then extend it */
	if (obj->curSize == obj->capacity)
		if (arrFlex_realloc(obj, obj->curSize*2) != 0)
			return -1;

	/* shift over the values that are already in the array;
	 * then extend the array.
	 */
	int i;
	for (i=obj->curSize-1; i>=index; i--)
		obj->arr[i+1] = obj->arr[i];
	obj->curSize++;

	/* finally, insert into the correct location. */
	obj->arr[index] = val;

	return 0;
}


int arrFlex_delete(ArrFlex *obj, int index)
{
	/* check if the index is invalid */
	if (index < 0 || index >= obj->curSize)
		return -1;

	/* shift over the values that are already in the array;
	 * then shorten the array.
	 */
	int i;
	for (i=index; i+1<obj->curSize; i++)
		obj->arr[i] = obj->arr[i+1];
	obj->curSize--;

	return 0;
}


ArrFlex *arrFlex_subArray(ArrFlex *obj, int start, int end)
{
	if (start < 0 || start > end || end > obj->curSize)
		return NULL;

	/* calculate the new len.  The capacity is the same value - except
	 * that it must be at least 16.  (A zero-length capacity would never
	 * grow!)
	 */
	int newLen = end-start;
	int cap    = newLen < 16 ? 16 : newLen;
	
	ArrFlex *retval = malloc(sizeof(ArrFlex));
	if (retval == NULL)
		return NULL;

	retval->arr = malloc(cap * sizeof(char));
	if (retval->arr == NULL)
	{
		free(retval);
		return NULL;
	}

	retval->capacity = cap;
	retval->curSize  = newLen;

	int i;
	for (i=start; i<end; i++)
		retval->arr[i-start] = obj->arr[i];

	return retval;
}


char *arrFlex_toString(ArrFlex *obj)
{
	char *retval = malloc(obj->curSize+1);
	if (retval == NULL)
		return NULL;

	memcpy(retval, obj->arr, obj->curSize);
	retval[obj->curSize] = '\0';

	return retval;
}



static int arrFlex_realloc(ArrFlex *obj, int newSize)
{
	char *newBuf = malloc(newSize * sizeof(char));
	if (newBuf == NULL)
		return -1;

	int i;
	for (i=0; i<obj->curSize; i++)
		newBuf[i] = obj->arr[i];

	free(obj->arr);
	obj->arr      = newBuf;
	obj->capacity = newSize;

	return 0;
}

