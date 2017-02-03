/*
 * File:    arrFlex.c
 * Authors: Lu Ye
 *
 * Purpose: This is a library for many function to implemente arrFlex.
 */

 #include "arrFlex.h"
 #include <stdlib.h>
 #include <string.h>


/* ArrFlex is a struct which represents a resizable array of characters (not
 * necessarily a string).
 *
 * Originally, it was based off of ArrayList from Java - but we decided to
 * rename it because we're not requiring that students implement a linked
 * list.  We're expecting most implementations to simply be a single large
 * array, which is reallcoated as necessary.
 */
// typedef struct ArrFlex
//  {
// 	char *data;
// 	int size;
// 	int memSize;

// } ArrFlex;

/* arrFlex_new()
 *
 * Creates a new ArrFlex object.  This should malloc() the struct, malloc()
 * the array inside it, and initialize all fields.  It returns a pointer to
 * the new object.
 *
 * ERROR HANDLING: Return NULL if there is any error allocating memory.
 *
 * RETURN VALUE: New object or NULL
 */
ArrFlex *arrFlex_new(){
	ArrFlex *obj = malloc(sizeof(ArrFlex));
	if(obj==NULL){
		return NULL;
	}
	obj->memSize = 64;//intinalize it to 64 for malloc 64 char space
	obj->size = 0;
	obj->data = malloc(sizeof(char) * obj->memSize);
	if(obj->data == NULL){
		return NULL;
	}
	return obj;
}

/* arrFlex_free()
 *
 * Frees an ArrFlex object, inclding freeing the array inside it.
 *
 * ERROR HANDLING: None
 *
 * RETURN VALUE: void
 */
void arrFlex_free(ArrFlex *obj){
	free(obj->data);
	free(obj);
}

/* arrFlex_clone()
 *
 * Creates a new ArrFlex object, which is a duplicate of a preivous one.  Make
 * sure that they do not share the same array!
 *
 * ERROR HANDLING: Return NULL if there is any error allocating memory.
 *
 * RETURN VALUE: New object or NULL
 */
ArrFlex *arrFlex_clone(ArrFlex *obj){
	ArrFlex *arrFlex_another = arrFlex_new();
	if(arrFlex_another==NULL){ //check perror
		return NULL;
	}
	int i;
	for(i = 0; i<obj->size;i++){
		arrFlex_another->data[i] = obj->data[i];//clone
	}
	arrFlex_another->size = obj->size;
	return arrFlex_another;
}

/* arrFlex_size()
 *
 * Return the number of elements in the ArrFlex object.  NOTE: This is the
 * number of active elements - we encourage you to have a 'capacity' which is
 * larger, in order to reduce the number of times you have to resize your
 * array.
 *
 * ERROR HANDLING: None
 *
 * RETURN VALUE: current size
 */
int arrFlex_size(ArrFlex *obj){
	return obj->size; //return size
}

/* arrFlex_set()
 *
 * Set the value of a single element in the array.  The index given must be
 * non-negative, and less than the current size.
 *
 * ERROR HANDLING: Return -1 if the index is invalid.
 *
 * RETURN VALUE: -1 on error, 0 otherwise
 */
int arrFlex_set(ArrFlex *obj, int index, char val){
	if(index >= 0 && index < obj->size){ // must non-negative and less then size
		obj->data[index] = val;
		return 0;
	}
	return -1;
}

/* arrFlex_get()
 *
 * Get the value of a single element in the array.  The index given must be
 * non-negative, and less than the current size.
 *
 * ERROR HANDLING: Return -1 if the index is invalid.
 *
 * RETURN VALUE: -1 on error, the character at that index otherwise
 */
int arrFlex_get(ArrFlex *obj, int index){
	if(index >= 0 && index < obj->size){
		return obj->data[index];
	}
	return -1; //invalid
}

/* arrFlex_add()
 *
 * Add a single value to the array, extending its capacity if necessary.
 *
 * ERROR HANDLING: Return -1 if there is any error allocating memory.
 *
 * RETURN VALUE: -1 on error, 0 otherwise
 */
int arrFlex_add(ArrFlex *obj, char newVal){
	int i;
	if(obj->size >= obj->memSize){
		char *temp = malloc(sizeof(char) * ((obj->memSize)*2)); //extend the capacity
		if(temp == NULL){
			return -1;
		}
		for(i=0; i<obj->size; i++){
			temp[i] = obj->data[i]; //give obj data to value in temp at i
		}
		free(obj->data);
		obj->data = temp;
		temp[i] = newVal;
		obj->size++;
	}else{
		obj->data[obj->size] = newVal;
		obj->size++;
	}
	return 0;
}

/* arrFlex_append()
 *
 * Extend the current array, adding to it *ALL* of the values in the other
 * array.
 *
 * ERROR HANDLING: Return -1 if there is any error allocating memory.
 *
 * RETURN VALUE: -1 on error, 0 otherwise
 */
int arrFlex_append(ArrFlex *obj, ArrFlex *arrayToAdd){
	int i, objsize = obj->size, allSize = (obj->size) + (arrayToAdd->size);
	char *temp = malloc(sizeof(char) * allSize);
	if(temp==NULL){
		return -1;
	}
	for(i = 0; i < allSize; i++){
		if(i<objsize){//if i smaller than obj size
			temp[i] = obj->data[i]; //give obj data at i location to temp [i]
		}else{
			temp[i] = arrayToAdd->data[i-objsize]; // otherwise, give it to arrayToAdd data
		}
	}
	free(obj->data);
	obj->data = temp;
	obj->memSize = allSize;
	obj->size = allSize;
	return 0;
}

/* arrFlex_insert()
 *
 * Insert a single element, at a given index, shifting values over to make
 * space.  If the index is 0, insert at the head; if the index == size, then
 * this function is identical to add().
 *
 * ERROR HANDLING: Return -1 if the index is invalid, or if there is any
 *                 error allocating memory.
 *
 * RETURN VALUE: -1 on error, 0 otherwise
 */
int arrFlex_insert(ArrFlex *obj, int index, char value){
	char *temp = NULL;
	if(index<0||index > obj->size){
		return -1;
	}else{ //if index is valid
		if(obj->size>= obj->memSize){ //if obj size bigger than obj memory size
			temp = malloc(sizeof(char)* (obj->memSize*2));
			if(temp == NULL) {
				return -1;
			}
			obj->memSize = obj->memSize*2; // extend memory size
		}else{//otherwise, insert directly
			temp = malloc(sizeof(char)* (obj->memSize));
			if(temp == NULL) {
				return -1;
			}
		}
		int i = 0, j = 0;
		while(i < (obj->size)+1){
			if(i!=index){ //if the i is not equal to index you want to find
				temp[i] = obj->data[j]; 
				i++;
				j++; //keep traking
			}else{ //otherwise, insert value
				temp[i] = value;
				i++;
			}
		}
		free(obj->data);
		obj->data = temp;
		obj->size++;
		return 0;
	}
}


/* arrFlex_delete()
 *
 * Delete a single element, at a given index, shifting values over.  If the
 * index is 0, this deletes the first; if the index == size-1, then this
 * deletes the last.
 *
 * ERROR HANDLING: Return -1 if the index is invalid (including the case
 *                 where the array was already empty).
 *
 * RETURN VALUE: -1 on error, 0 otherwise
 */
int arrFlex_delete(ArrFlex *obj, int index){
	if(index < 0 || index > obj->size) {
		return -1;
	}
	char *temp = malloc(sizeof(char)*obj->memSize); 
	if(temp == NULL) {//check the error and return -1
		return -1;
	}
	int i = 0, j = 0; 
	while(i < obj->size){ //if valid
		if(i != index) {
			temp[i] = obj->data[j]; 
		}
		else{
			temp[i] = obj->data[j+1];
			j++;
		}
		j++;
		i++;
	}
	free(obj->data); // free memory
	obj->data = temp;
	obj->size--;
	return 0;	

}

/* arrFlex_subArray()
 *
 * Duplicate a subset of the array, into a new ArrFlex.  The range is from
 * start (inclusive) to end (exclusive).  If end==start, then the length
 * of the sliced array is zero.
 *
 * The indices must fulfill the following requirements:
 *    start >= 0
 *    end   >= start
 *    end   <= size
 *
 * ERROR HANDLING: Return NULL if the start or end indices are invalid.
 *                 Also return NULL if there is any error allocating memory.
 *
 * RETURN VALUE: Pointer to the newly-allocated object, or NULL.
 */
ArrFlex *arrFlex_subArray(ArrFlex *obj, int start, int end){
	if(start < 0 || end < start || end > obj->size) { //if the size is not valid
		return NULL;
	}
	ArrFlex * temp = arrFlex_new();
	if(end==start){ 
		return temp; // a newly object if the end is equal to start
	}else{
		int i;
		for(i=start; i<end; i++) {
			arrFlex_add(temp,obj->data[i]); //call add function
		}
		return temp;
	}
}


/* arrFlex_toString()
 *
 * Allocates a new array on the heap, large enough to store the current
 * contents of the array; copies the elements into that array, and returns
 * it.
 *
 * The array that is returned must have one more character than the contents
 * of the ArrFlex object; this last character is set to '\0'.
 *
 * Since the returned array is a duplicate, the caller may modify the array -
 * that will not affect the contents of this object.  Also, the caller is
 * responsible for freeing the array.
 *
 * If the object currently has 0 elements, this will still return a non-NULL
 * pointer; however, the buffer may have as few as 1 bytes in it.
 *
 * ERROR HANDLING: Return NULL if there is any error allocating memory.
 *
 * RETURN VALUE: The new buffer, or NULL.
 */
char *arrFlex_toString(ArrFlex *obj){
	int i;
	char *temp = malloc(sizeof(char)* (obj->size + 1));//malloc one more space
	if(temp == NULL){
		return NULL;
	}else{
		for(i = 0; i<obj->size;i++){
			temp[i] = obj->data[i];
		}
	}
	temp[i] = '\0'; //last position is null terminator
	return temp;

}

//end