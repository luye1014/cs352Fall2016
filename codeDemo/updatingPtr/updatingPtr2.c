#include <stdio.h>
#include <stdlib.h>

int main(){
	int a[] = {5, 15, 34, 54, 14, 2, 52, 72};
	int *p = malloc(sizeof(int));
	int *q = malloc(sizeof(int));
	*p = a;
	 *q = &a[5];

	*(p++) = *q – 1;
	printf("p=%d,q=%d",&p,&q);
	return 0;
}

