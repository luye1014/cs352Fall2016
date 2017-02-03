/*
 * File:   removeSome.c
 * Author: Russell Lewis
 *
 * Purpose: Reads strings from stdin; filters out the vowels from words, and
 *          the even digits from numbers; prints out the result (where numbers
 *          are printed out reversed).
 */


#include <stdio.h>
#include <ctype.h>


int handleLetters(char *buf);
int handleDigits (char *buf);


int main()
{
	char buf[32];
	int  retval = 0;

	/* loop until we hit EOF.  This use of scanf() does *NOT* have to
	 * worry about the "infinite loop" problem shown in the slides,
	 * because %s will read anything (other than whitespace).
	 */
	while (scanf("%s", buf) != EOF)
	{
		/* check to see if the string is all-letters or all-numbers */
		if (isalpha(buf[0]))
		{
			/* try to handle this as a set of all-digits.  If
			 * the return value is nonzero, then there was an
			 * error, which we need to record for later.
			 */
			if (handleLetters(buf) != 0)
				retval = 1;
		}
		else if (isdigit(buf[0]))
		{
			/* same as previous block, only digits */
			if (handleDigits(buf) != 0)
				retval = 1;
		}
		else
		{
			fprintf(stderr, "ERROR: The string '%s' does not appear to be either made of entirely letters, or entirely digits.\n", buf);
			retval = 1;
		}
	}

	return retval;
}


int handleLetters(char *buf)
{
	int i;

	/* check to see if the string is *ENTIRELY* made of letters.  If not,
	 * then immediately report an error and return out.
	 */
	for (i=1; buf[i] != '\0'; i++)
	if (! isalpha(buf[i]))
	{
		fprintf(stderr, "ERROR: The string '%s' does not appear to be either made of entirely letters, or entirely digits.\n", buf);
		return 1;
	}

	/* if we get here, then the entire string is entirely made of letters.
	 * Do a second pass (we could have done this in the first pass, if
	 * we wanted) where we remove the vowels.
	 */
	int kept = 0;  // how many of the letters have we kept intact?
	for (i=0; buf[i] != '\0'; i++)
	{
		if (buf[i] == 'a' || buf[i] == 'A' ||
		    buf[i] == 'e' || buf[i] == 'E' ||
		    buf[i] == 'i' || buf[i] == 'I' ||
		    buf[i] == 'o' || buf[i] == 'O' ||
		    buf[i] == 'u' || buf[i] == 'U')
		{
			continue;  // skip over this character
		}


		/* otherwise, copy this character to the left.  (If kept==i,
		 * this is a harmless NOP.)
		 */
		buf[kept] = buf[i];
		kept++;
	}

	/* before we print, set the null terminator in the proper location.
	 * Note that it's possible that the new string might be zero length.
	 */
	buf[kept] = '\0';
	printf("%s\n", buf);

	return 0;
}


int handleDigits(char *buf)
{
	int i;

	/* check to see if the string is *ENTIRELY* made of letters.  If not,
	 * then immediately report an error and return out.
	 */
	for (i=1; buf[i] != '\0'; i++)
	if (! isdigit(buf[i]))
	{
		fprintf(stderr, "ERROR: The string '%s' does not appear to be either made of entirely letters, or entirely digits.\n", buf);
		return 1;
	}

	/* if we get here, then the entire string is entirely made of digits.
	 * Do a second pass (we could have done this in the first pass, if
	 * we wanted) where we remove the even digits.
	 */

// TODO: reverse the string!

	int kept = 0;  // how many of the letters have we kept intact?
	for (i=0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '0' || buf[i] == '2' || buf[i] == '4' ||
		    buf[i] == '6' || buf[i] == '8')
		{
			continue;  // skip over this character
		}


		/* otherwise, copy this character to the left.  (If kept==i,
		 * this is a harmless NOP.)
		 */
		buf[kept] = buf[i];
		kept++;
	}

	/* to print in reverse order, we need to iterate *backwards* through
	 * the string.  'kept' gives the index of the first character *AFTER*
	 * the string.
	 */
	for (i=kept-1; i>=0; i--)
		printf("%c", buf[i]);
	printf("\n");

	return 0;
}

