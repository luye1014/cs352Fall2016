/* File: substrings.c
 * Author: Eric Anson
 * Purpose: Read strings a line at a time and see if the subsequent lines
 *          are a substring of the first line.
 */

#include <stdio.h>
#include <string.h>

/* needleInHaystack this routine checks whether the string needle is a
   substring of the string hay. If it is, it returns the index of the first
   occurance, if not, it returns -1
*/
int needleInHaystack(char *needle, char *hay) {
  int i;
  int upper;
  char *p1, *p2;

  
  upper = strlen(hay) - strlen(needle);  //bound on search
  for (i = 0; i <= upper; ++i) {
    p1 = hay + i;
    p2 = needle;
    while (p2) {
      if (*p1 != *p2)
        break;
      ++p1;
      ++p2;
    }
    if (!(*p2))		//matched entire string
      return i;
  }
  return -1;
}

int main() {
  char *masterStr = NULL;
  char *str = NULL;
  size_t msz, ssz;
  int res;

  //Read the strings
  res = getline(&masterStr, &msz, stdin);
  if (res <= 0 || masterStr[0] == '\n') {
    fprintf(stderr,"Master String is empty\n");
    return 1;
  }
  while ((res = getline(&str, &ssz, stdin)) > 0) {
    if (str[0] != '\n') {		//ignore empty line 
      if (str[res-1] == '\n')
        str[res-1] = '\0';		//strip off newline
      printf("%d\n", needleInHaystack(str, masterStr));
    }
  }
  return 0;
}
