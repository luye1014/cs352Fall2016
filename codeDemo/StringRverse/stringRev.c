/**
 * This program implements a function to reverse a string.
 */

#include <stdio.h>
#include <string.h>

char *reverse(char *str){
	int i, j, len;
	char *result;

	if(str == NULL) return NULL;
	result = strdup(str);
	len = strlen(str);
	for(i=0, j = len-1; j>=0; i++, j--){
		result[i] = str[j];
	}
	result[len] = '\0';
	return result;

}

int main(){
	char str[32];

	while(scanf("%31s", str) != EOF){
		printf("the reverse of %s is %s.\n", str, reverse(str));
	}
	return 0;
}
