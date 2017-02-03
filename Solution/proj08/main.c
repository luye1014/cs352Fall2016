/*
 * File:   main.c
 * Author: Russell Lewis
 *
 * Purpose: Implements the main() function (and other I/O-related code) for
 *          Project 8.
 */

#include <stdio.h>
#include <malloc.h>

#include "util.h"



int main(int argc, char **argv)
{
	int f;
	for (f=1; f<argc; f++)
	{
		FILE *fp = fopen(argv[f], "r");
		if (fp == NULL)
		{
			printf("The file '%s' did not exist.\n", argv[f]);
			continue;
		}


		char **array = malloc(16 * sizeof(char*));
		int    capacity = 16;
		int    count    = 0;

		if (array == NULL)
		{
			perror("Could not allocate the initial array");
			return 1;
		}


		while (1)
		{
			char   *buf    = NULL;
			size_t  bufLen = 0;

			int len = getline(&buf, &bufLen, fp);

			if (len == -1)
			{
				/* EOF */
				fclose(fp);

				/* it appears that getline() allocates a
				 * buffer, even when it's going to return
				 * EOF.  Strange.
				 */
				free(buf);
				break;
			}


			/* if the string has a newline at the end, then
			 * remove it!
			 */
			if (len > 0 && buf[len-1] == '\n')
				buf[len-1] = '\0';


			/* record the string into the array.  But if the
			 * array is full, then expand it first.
			 */
			if (count == capacity)
			{
				array = extendArray(array, count, count*2);
				if (array == NULL)
				{
					perror("Could not expan array");
					return 1;
				}

				capacity *= 2;
			}

			array[count] = buf;
			count++;
		}


		/* now, sort the array and then print it all out.  Free the
		 * buffers as we use them.
		 */
		sortArray(array, count);

		printf("The file '%s' had %d lines.\n", argv[f], count);

		int i;
		for (i=0; i<count; i++)
		{
			printf("%s\n", array[i]);
			free(array[i]);
		}


		/* finally, free the array itself. */
		free(array);
	}

	return 0;
}

