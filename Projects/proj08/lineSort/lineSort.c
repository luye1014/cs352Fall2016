#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilityFunction.h"

int main(int argc, char**argv){
	FILE *filename;
	size_t len = 0;
	char *line = NULL;
	int index, counter = 0;
	char *current_line;
	char **array = malloc(16 * sizeof(char*));

	for(index = 1; index < argc; index++){ //loop for all files name you input in the command line
		filename = fopen(argv[index], "r");
		if(filename == NULL){
			printf("The file '%s' did not exist.\n", argv[index]);
		}else{
			while(getline(&line, &len, filename)!=EOF){
				current_line = strdup(line);
				if(counter<16){
					array[counter] = current_line;
				}else{
					array = extendArray(array, counter, counter+1);
					array[counter] = current_line;
				}
				counter++;
			}
			printf("The file '%s' had %d lines.\n", argv[index], counter);
			Mysort(array,counter);
			printf("here start\n");
			
			int j;
			for(j = 0; j < counter; j++){
				printf("%s\n", array[j]);
			
			}
			
		}
	}
}
