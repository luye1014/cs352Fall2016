#include "utilityFunction.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

char **extendArray(char **oldArray, int oldLen, int newLen){ 
	char **newptr = malloc(newLen * sizeof(char*));
	// if(newptr == NULL){
	// 	perror("Failed to allocate");
	// 	exit(1);
	// }
	memcpy(newptr, oldArray, oldLen * sizeof (char*));
	free(oldArray);
	return newptr;
}

void Mysort(char **array, int ArrayLength){
    int i, j;   
    char *temp;             // holding variable orig with no *
    for(i = 0; i < ArrayLength-1; i++){
        for (j = 0; j < ArrayLength-1-i; j++){
            if (strcmp(array[j], array[j+1])>0){ 
                temp = array[j];             // swap elements
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}


