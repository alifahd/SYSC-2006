/* SYSC 2006 Winter 2019 Lab 7
 *
 * array_list.c 
 *
 * Prototype of a dynamically allocated, fixed-capacity list that supports a 
 * subset of the operations provided by Python's list class.
 */ 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array_list.h"

/* Construct a new, empty list, and return a pointer to it
 * Parameter capacity is the # of elements that can be stored in the list.
 * Terminate the program via assert if capacity is <= 0.
 * Terminate the program via assert if memory for the list cannot be 
 * allocated from the heap.
 */
list_t *list_construct(int capacity)
{
    list_t *list;

	list = malloc(sizeof(list_t));
	assert(list != NULL);

	list->elems = malloc(capacity*sizeof(int));
	assert(list->elems != NULL);

	assert(capacity > 0);

	list->capacity = capacity;
	list->size = 0;

    return list;
}

/* Destroy the list pointed to by parameter list, deallocating all memory 
 * that was allocated from the heap.
 * Terminate the program via assert if list is NULL.
 */
void list_destroy(list_t *list)
{
    assert(list != NULL);
    free(list->elems);  /* Return the array to the heap. */
    free(list);         /* Return the structure to the heap. */
}

/* Print the list pointed to by parameter list on the console.
 * Terminate the program via assert if list is NULL.
 */
void list_print(const list_t *list)
{    
    assert(list != NULL);
	printf("[");
    int n = list->size;

    if (n > 0) {
        /* Print all the array elements, with a leading space before
         * all but the first element. 
         */
	    printf("%d", list->elems[0]);

        for (int i = 1; i < n; i += 1) {
	        printf(" %d", list->elems[i]);
	    }
	}
	printf("]");
    printf(", capacity: %d, size: %d\n", list->capacity, list->size);
}

/* Insert element at the end of the list pointed to by parameter list
 * and return true.
 * If the list is full, double its capacity before appending
 * the element.
 * Terminate the program via assert if list is NULL.
 * Terminate the program via assert if the full list's capacity
 * couldn't be doubled.
 */

_Bool list_append(list_t *list, int element)
{
	assert (list != NULL);
	if (list->capacity == list->size){
		increase_capacity(list, list->capacity*2);
		list->elems[list->size] = element;
		list->size++;
	}else{
		list->elems[list->size] = element;
		list->size++;
	}
	return true;
}

/* Return the maximum number of integers that can be stored in the list 
 * pointed to by parameter list.
 * Terminate the program via assert if list is NULL.
 */
int list_capacity(const list_t *list)
{
		assert(list != NULL);
       	return list->capacity;
}

/* Return the number of integers in the list pointed to by parameter list.
 * Terminate the program via assert if list is NULL.
 */
int list_size(const list_t *list)
{
    	assert(list != NULL);
       	return list->size;
}

/* Return the element located at the specified index, in the list
 * pointed to by parameter list. 
 * Terminate the program via assert if list is NULL, 
 * or if index is not in the range 0 .. list_size() - 1.
 */
int list_get(const list_t *list, int index)
{
	assert(list != NULL);
	assert(index >= 0);
	assert(index < list->size);
    return list->elems[index];
}

/* Store element at the specified index, in the list pointed to by 
 * parameter list. Return the integer that was previously 
 * stored at that index.
 * Terminate the program via assert if list is NULL, 
 * or if index is not in the range 0 .. list_size() - 1.
 */
int list_set(list_t *list, int index, int element)
{
	assert(list != NULL);
	assert(index >= 0);
	assert(index < list->size);
   	int holder = list->elems[index];
	list->elems[index] = element;
    return holder;
}

/* Empty the list pointed to by parameter list.
 * Memory allocated to the list is not freed, so the emptied list can 
 * continue to be used.
 * Terminate the program via assert if list is NULL.
 */
void list_removeall(list_t *list)
{
	assert(list != NULL);
	list->size = 0;
}

/* SYSC 2006 Winter 2019 Lab 8
 *
 * additional_functions.c 
 */ 

/* Return the index (position) of the first occurrence of an integer
 * equal to target in the list pointed to by parameter list. 
 * Return -1 if target is not in the list.
 * Terminate the program via assert if list is NULL.
 */
int list_index(const list_t *list, int target)
{
	assert(list != NULL);
	for(int i=0; i < list->size; i++){
		if (list->elems[i] == target){
			return i;
		}
	}
		return -1;
}

/* Count the number of integers that are equal to target, in the list 
 * pointed to by parameter list, and return that number.
 * Terminate the program via assert if list is NULL.
 */
int list_count(const list_t *list, int target)
{
	assert(list != NULL);
	int count = 0;
	for(int i=0; i < list->size; i++){
		if (list->elems[i] == target){
			count++;
		}
	}
    return count;
}

/* Determine if an integer in the list pointed to by parameter list 
 * is equal to target.
 * Return true if target is in the list, otherwise return false.
 * Terminate the program via assert if list is NULL.
 */
_Bool list_contains(const list_t *list, int target)
{
	assert(list != NULL);
	if (list_index(list, target) != -1){
		return true;
	}
	else{
		return false;
	}
}

/* Increase the capacity of the list pointed to by parameter list to
 * the specified new capacity.
 * Terminate the program via assert if new_capacity is not greater than the
 * list's current capacity, or if the memory required to increase the
 * list's capacity cannot be allocated.
 */
void increase_capacity(list_t *list, int new_capacity)
{
	assert(list != NULL);
	assert(new_capacity > list->capacity);
	int holder[list->size];
	for (int i = 0; i < list->size;i++){
		holder[i]=list->elems[i];
	}
	int n = list->size;
	free(list);
	list = malloc(sizeof(list_t));
	assert(list != NULL);
	list->elems = malloc(new_capacity*sizeof(int));
	assert(list->elems != NULL);
	int count = 0;
	for (int i = 0; i < n;i++){
		list->elems[i] = holder[i];
		count++;
	}
	list->size = count;
	list->capacity = new_capacity;
}

/* Delete the integer at the specified position in the list pointed
 * to by parameter list.
 * Parameter index is the position of the integer that should be removed.
 * Terminate the program via assert if list is NULL, or if index
 * is not in the range 0 .. list_size() - 1.

 */
void list_delete(list_t *list, int index)
{
	assert(list != NULL);
	assert(index<list->size);
	for (int i=index; i<list->size-1; i++){
		list->elems[i] = list->elems[i+1];
	}
	list->size = list->size-1;
}

