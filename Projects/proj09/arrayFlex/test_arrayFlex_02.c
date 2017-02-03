//test file made by lu ye
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "arrFlex.h"

int main(int argc, char **argv)
{
	ArrFlex *arr1 = arrFlex_new();
	int i;
	for(i=0;i<128;i++){
        arrFlex_add(arr1,'a');
	}
	char *str1 = arrFlex_toString(arr1);
	printf("arr1: %s\n", str1);

	//add few value
	ArrFlex *arr2 = arrFlex_new();
	int rc5 = arrFlex_append(arr1, arr2);
	printf("return: %d\n", rc5);
	int rc1 = arrFlex_add(arr2, 'a');
	int rc2 = arrFlex_add(arr2, 'b');
	int rc3 = arrFlex_add(arr2, 'c');
	char *str2 = arrFlex_toString(arr2);//test to string
	printf("arr2 is: %s\n", str2);
	printf("Return: %d %d %d\n", rc1, rc2, rc3);
	//test size
	int rc4 = arrFlex_size(arr2);
	printf("%d\n", rc4);
	arrFlex_free(arr2);

	//test get
	rc1 = arrFlex_get(arr1, -1);
	rc2 = arrFlex_get(arr1, 1);
	printf("%d %c\n", rc1, rc2);

	ArrFlex *arr3 = arrFlex_clone(arr1); //clone
	arr3 = arrFlex_subArray(arr1, 0, 19);

	rc1 = arrFlex_insert(arr3, 0, 'b');
	rc2 = arrFlex_insert(arr3, 1, '2');
	rc3 = arrFlex_insert(arr3, -1, '3');
	printf("%d%d%d\n", rc1, rc2, rc3);

	rc1 = arrFlex_delete(arr3, 0);
	rc2 = arrFlex_delete(arr3, 21);
	rc3 = arrFlex_set(arr3, 5, 'a');
	rc4 = arrFlex_set(arr3, 20, '4');
	printf("%d %d\n",rc3, rc4);
	printf("%d %d\n", rc1, rc2);
	arrFlex_free(arr3);

	return 0;
}
