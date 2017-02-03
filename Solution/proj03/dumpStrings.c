/*
 * File:   dumpStrings.c
 * Author: Russell Lewis
 *
 * Purpose: Reads strings from stdin; prints out each of the characters in the
 *          string, and calculates the length.
 */


#include <stdio.h>
#include <string.h>


int main()
{
	char buf[32];

	/* loop until we hit EOF.  This use of scanf() does *NOT* have to
	 * worry about the "infinite loop" problem shown in the slides,
	 * because %s will read anything (other than whitespace).
	 */
	while (scanf("%s", buf) != EOF)
	{
		/* 'len' will count the number of valid characters; we'll
		 * use it as a counter - and also as the loop index.
		 */
		int len;
		for (len=0; buf[len] != '\0'; len++)
		{
			printf("index=%d char='%c' dec=%d hex=0x%02x\n",
			       len, buf[len], buf[len], buf[len]);
		}

		/* when we get here, 'len' is equal to the number of non-NULL
		 * characters in the string.
		 */
		printf("count=%d strlen=%d\n", len, (int)strlen(buf));

		/* blank line after each output */
		printf("\n");
	}

	return 0;
}

