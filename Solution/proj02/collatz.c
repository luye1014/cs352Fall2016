/*
 * File:   collatz.c
 * Author: Russell Lewis
 *
 * Purpose: Tests the Collatz Conjecture; reads integers from stdin, and
 *          demonstrates that they (eventually) fall below the start point
 *          for each one.
 *
 *          Actually, this program doesn't *ASSUME* that every integer will
 *          eventually fall below its starting point - it allows for the
 *          possibility of it returning (which is good, if the input is 1!).
 *          But we know, from other people, that the Collatz Conjecture holds
 *          to very large numbers - larger than we can test here.
 *
 *          BUG: I don't do overflow detection when I do the 3n+1 calculation.
 */


#include <stdio.h>


int main(void)
{
	int retval = 0;   // we'll change this if and when we hit an error


	/* we break out of the loop manually, based on the scanf() retval */
	while (1)
	{
		int startVal;
		int rc = scanf("%d", &startVal);


		/* was there an error reading the input? */
		if (rc == 0)
		{
			fprintf(stderr, "ERROR: An element on the input stream is not an integer.\n");

			retval = 1;
			break;
		}


		/* did we hit EOF? */
		if (rc == EOF)
		{
			/* NOT an error! */
			break;
		}


		/* was the input an integer...but not positive? */
		if (startVal <= 0)
		{
			fprintf(stderr, "ERROR: The input %d cannot be tested, because it is non-positive.\n", startVal);

			retval = 1;
			continue;
		}


		/* do the experiment! */
		printf("%d:", startVal);
		int cur = startVal;

		do
		{
			if (cur % 2 == 0)
				cur /= 2;
			else
				cur = 3*cur + 1;

			printf(" %d", cur);
		} while (cur > startVal);


		/* we fell below (or equal to) the start point */
		printf("\n");
		fflush(NULL);
	}

	/* We left the while() loop because we hit EOF, or a non-iteger
	 * input.
	 */


	return retval;
}
