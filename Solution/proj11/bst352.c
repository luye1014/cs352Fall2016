/*
 * File:    bst352.c
 * Authors: Russell Lewis
 *
 * Purpose: Solution to Project 11.
 */


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>



typedef struct BSTNode BSTNode;

struct BSTNode
{
	BSTNode *left;
	BSTNode *right;
	int val;
};



/* I hate globals - they don't scale properly to large, complex systems.
 * But it's a terribly *easy* solution.  The "correct" solution probably
 * would be to add an int* parameter to every function call, but that's
 * just ugly!
 */
int retval = 0;



BSTNode *bst_processCommand(BSTNode*, char*);
void     bst_free          (BSTNode*);

BSTNode *bst_insert  (BSTNode*, int val);
BSTNode *bst_delete  (BSTNode*, int val);
void     bst_search  (BSTNode*, int val);
int      bst_min     (BSTNode*);
int      bst_max     (BSTNode*);
void     bst_preOrder(BSTNode*);
void     bst_inOrder (BSTNode*);



int main()
{
	BSTNode *root = NULL;

	/* NOTE: I re-use the buffer, over and over */
	char   *buf    = NULL;
	size_t  bufLen = 0;
	while (getline(&buf, &bufLen, stdin) != -1)
	{
		int len = strlen(buf);

		/* skip any line which is zero length - which would almost
		 * certainly mean that the next call is EOF.
		 */
		if (len == 0)
			continue;

		/* if the last character is a newline (which is almost always),
		 * then remove it.
		 */
		if (buf[len-1] == '\n')
		{
			buf[len-1] = '\0';
			len--;
		}


		/* search for any semicolons, which break the line into smaller
		 * pieces.  If we find any, then split the line there.
		 */
		int startIndx = 0;
		for (int i=0; i<len; i++)
		{
			if (buf[i] == ';')
			{
				/* we found a semicolon.  Break up the string,
				 * send the left-hand command, and then update
				 * startIndx so that the next string will start
				 * after this.
				 *
				 * We use the
				 *    x = change(x)
				 * style for *processing the command*, which is
				 * strange, but it works.
				 */

				buf[i] = '\0';
				root = bst_processCommand(root, buf+startIndx);
				startIndx = i+1;
			}
		}

		/* when we get here, we have hit the end of the string; if
		 * there were any semicolons, then we sent the commands
		 * *BEFORE* the semicolon, but not the one after.  Likewise,
		 * if there were *no* semicolons, we haven't sent anything
		 * at all.
		 */
		root = bst_processCommand(root, buf+startIndx);


		/* loop back and read the next line from stdin */
	}


	/* we're done!  Free the line, and then the BST */
	free(buf);
	bst_free(root);

	return retval;
}



BSTNode *bst_processCommand(BSTNode *root, char *str)
{
	/* BUGFIX:
	 *
	 * We need to be able to recognize the "word word word" case.  The
	 * original implementation here simply used "%s %d %s", which could
	 * not distinguish between "word" and "word non-numeric-word ..."
	 *
	 * This two-stage process is kind of a hack, but it works.  In the
	 * end, we have rejected any command with 3 or more words, as well
	 * as any with a non-numeric second word.  The rc is either 1 or 2,
	 * meaning indicating whether or not a numeric parameter was given.
	 */
	char cmd  [32];
	char word2[32];
	char word3[32];

	int rc = sscanf(str, "%31s %31s %31s", cmd, word2, word3);

	/* check the return code for some obvious answers! */
	if (rc == EOF)
		return root;    // empty string, NOP
	if (rc < 1)
	{
		retval = 1;
		fprintf(stderr, "ERROR parsing the command '%s'.\n", str);
		return root;    // no change
	}
	if (rc > 2)
	{
		retval = 1;
		fprintf(stderr, "ERROR: The command '%s' had too many terms.\n", str);
		return root;    // no change
	}


	/* if we get here, then rc is 1 or 2; now, was the 2nd word a number?
	 * Check both for a number, and also watch out for trailing
	 * non-numeric text after that number.
	 */
	int   val;
	if (rc == 2)
	{
		int rc2 = sscanf(word2, "%d%31s", &val,word3);
		if (rc2 != 1)
		{
			retval = 1;
			fprintf(stderr, "ERROR: The command '%s' had a parameter which was not an integer\n", str);
			return root;    // no change
		}
	}


	/* if we get here, then rc is 1 or 2; if rc is 2, then 'val' has the
	 * numeric parameter.  We've done all of the error checking, except
	 * to see if having a numeric parameter is desired!
	 *
	 * And, of coruse, checking to see if the command is valid.
	 */


	if (strlen(cmd) != 1)
	{
		retval = 1;
		fprintf(stderr, "ERROR: Unrecognized command name in the command '%s'.\n", str);
		return root;    // no change
	}


	/* note that strcmp() is unnecessary, since we have single-character
	 * commands.
	 */

	switch (cmd[0])
	{
	case 'i':
	case 'd':
	case 's':
		if (rc != 2)
		{
			retval = 1;
			fprintf(stderr, "ERROR: The command '%c' requires an integer parameter.  Error in the command '%s'.\n", cmd[0], str);
			return root;    // no change
		}
		break;

	case 'm':
	case 'M':
	case 'p':
	case 'P':
		if (rc != 1)
		{
			retval = 1;
			fprintf(stderr, "ERROR: The command '%c' MUST NOT have any parameter.  Error in the command '%s'.\n", cmd[0], str);
			return root;    // no change
		}
		break;

	default:
		retval = 1;
		fprintf(stderr, "ERROR: Unrecognized command name in the command '%s'\n", str);
		return root;    // no change
	}

	switch (cmd[0])
	{
	case 'i':
		return bst_insert(root, val);

	case 'd':
		return bst_delete(root, val);

	case 's':
		bst_search(root, val);
		break;

	case 'm':
		if (root == NULL)
		{
			retval = 1;
			fprintf(stderr, "ERROR: Cannot calculate min because the tree is empty.\n");
		}
		else
			printf("%d\n", bst_min(root));
		break;

	case 'M':
		if (root == NULL)
		{
			retval = 1;
			fprintf(stderr, "ERROR: Cannot calculate max because the tree is empty.\n");
		}
		else
			printf("%d\n", bst_max(root));
		break;

	case 'p':
		bst_preOrder(root);
		printf("\n");
		break;

	case 'P':
		bst_inOrder(root);
		printf("\n");
		break;

	// NOTE: Invalid command not possible here, because we dealt with it above
	}


	/* if we get here, then this is a non-changing operation */
	return root;    // no change
}



void bst_free(BSTNode *root)
{
	if (root == NULL)
		return;

	bst_free(root->left);
	bst_free(root->right);

	free(root);
}



BSTNode *bst_insert(BSTNode *root, int val)
{
	if (root == NULL)
	{
		root = malloc(sizeof(BSTNode));
		if (root == NULL)
		{
			perror("Could not allocate a new BSTNode");
			exit(1);
		}

		root->left = root->right = NULL;
		root->val  = val;

		return root;
	}


	if (root->val == val)
	{
		retval = 1;
		fprintf(stderr, "ERROR: Could not insert %d into the tree because it already exists.\n", val);
		return root;
	}

	if (val < root->val)
		root->left  = bst_insert(root->left,  val);
	else
		root->right = bst_insert(root->right, val);

	return root;
}



BSTNode *bst_delete(BSTNode *root, int val)
{
	if (root == NULL)
	{
		retval = 1;
		fprintf(stderr, "ERROR: Could not delete %d from the tree because it does not exist.\n", val);
		return root;
	}


	if (root->val == val)
	{
		/* WE NEED TO DELETE.  THERE ARE 3 CASES: 0,1,2 children. */

		if (root->left == NULL && root->right == NULL)
		{
			/* CASE 1 */
			free(root);
			return NULL;
		}

		if (root->left == NULL)
		{
			/* CASE 2 - right */
			BSTNode *retval = root->right;

			free(root);
			return retval;
		}

		if (root->right == NULL)
		{
			/* CASE 2 - left */
			BSTNode *retval = root->left;

			free(root);
			return retval;
		}


		/* CASE 3 is the hardest case. */
// printf("*** CASE 3 ***   val=%d: left->val=%d right->val=%d\n", val, root->left->val, root->right->val);


		/* find the successor. */
		BSTNode *succ = root->right;
		while (succ->left != NULL)
			succ = succ->left;

		/* now that we have the successor, swap the two values. */
		int tmp   = root->val;
		root->val = succ->val;
		succ->val = tmp;

		/* now that we have swapped the values, recurse to delete
		 * the successor.  But we can't simply call delete on that
		 * node, sicne we have to update a parent pointer somewhere.
		 * So we'll recurse down towards it again.
		 */
		root->right = bst_delete(root->right, val);

		return root;
	}


	if (val < root->val)
		root->left  = bst_delete(root->left,  val);
	else
		root->right = bst_delete(root->right, val);

	return root;
}



void bst_search(BSTNode *root, int val)
{
	if (root == NULL)
	{
		printf("%d NOT found\n", val);
		return;
	}

	if (root->val == val)
	{
		printf("%d found\n", val);
		return;
	}

	if (val < root->val)
		bst_search(root->left,  val);
	else
		bst_search(root->right, val);

	return;
}



int bst_min(BSTNode *root)
{
	if (root->left == NULL)
		return root->val;
	return bst_min(root->left);
}



int bst_max(BSTNode *root)
{
	if (root->right == NULL)
		return root->val;
	return bst_max(root->right);
}



void bst_preOrder(BSTNode *root)
{
	if (root == NULL)
		return;    // NOP

	printf(" %d", root->val);

	bst_preOrder(root->left);
	bst_preOrder(root->right);
}



void bst_inOrder(BSTNode *root)
{
	if (root == NULL)
		return;    // NOP

	bst_inOrder(root->left);
	  printf(" %d", root->val);
	bst_inOrder(root->right);
}


