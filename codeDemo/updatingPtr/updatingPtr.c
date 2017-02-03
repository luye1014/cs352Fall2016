#include <stdio.h>

int main(){
	int x[3];
	int m, n, *p;
	
	x[0]=2;
	x[1]=4;
	x[2]=6;

	p=x;
	m=*(p+1);
	n=(*p)+1;
	printf("m=%d, n=%d\n", m, n);
	return 0;

}
