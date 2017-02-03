/*
 * File:   primePair.c
 * Author: Russell Lewis
 *
 * Purpose: In a range of integers, list all of the numbers which are the
 *          product of exactly two primes, along with the factorization.
 */


#include <stdio.h>


/*
 * firstPrime(int)
 *
 * Given a positive integer, returns the first prime factor; if the number is
 * prime, then it returns the number itself.
 *
 * For simplicity, this function allows for val=1; even though 1 is not
 * prime, it still returns 1.  In no other scenario will it ever return 1.
 */
int firstPrime(int val)
{
	int i;
	for (i=2; i*i <= val; i++)
		if (val % i == 0)
			return i;

	return val;
}


int main(void)
{
	/* read the two values that we expect */

	int start, end;
	int rc;

	rc = scanf("%d %d", &start, &end);
	if (rc != 2)
	{
		fprintf(stderr, "ERROR: Input should be exactly: <start> <end>\n");
		return 1;
	}

/*
	rc = scanf("%d", &dummy);
	if (rc != EOF)
	{
		fprintf(stderr, "ERROR: Input should be exactly: <start> <end>\n");
		return 1;
	}
 */

	if (start > end)
	{
		fprintf(stderr, "ERROR: Start must be <= end\n");
		return 1;
	}

	if (start < 2)
	{
		fprintf(stderr, "ERROR: Start must be >= 2\n");
		return 1;
	}


	/* loop over all of the integers in the range */
	int i;
	for (i=start; i<=end; i++)
	{
		/* find the first prime factor of the number; divide that out,
		 * and then find the second prime factor.  If the 2nd result
		 * is the number - and not 1 - then there are exactly two
		 * prime factors.
		 */
		int first  = firstPrime(i);
		int second = firstPrime(i/first);

		if (first*second == i && second != 1)
			printf("%d: %d %d\n", i, first, second);
	}


	return 0;
}

