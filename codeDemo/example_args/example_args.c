#include <stdio.h>

int main(int argc, char** argv)
{
	int count = 0;
	sscanf(argv[1], "%d", &count);
	int i;
	for(i= 0; i < count; i++){
		printf("%s\n", argv[2]);
	}
	return 0;
}
