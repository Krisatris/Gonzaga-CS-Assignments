/**
 * Author: Linden Beemer
 * CPSC 346 Project 4
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE				10
#define NUMBER_OF_THREADS	3

void *sorter(void *params);	/* thread that performs basic sorting algorithm */
void *merger(void *params);	/* thread that performs merging of results */

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};

int result[SIZE];

typedef struct
{
	int from_index;
	int to_index;
} parameters;

int main (int argc, const char * argv[]) 
{
	int i;
    
	pthread_t workers[NUMBER_OF_THREADS];

	/**
	printf("array at start is: ");
    for(int i = 0; i < SIZE; ++i) {
        printf("%d ", list[i]);
    }
	printf("\n");
	**/

	/* establish the first sorting thread */
	//1. call malloc to allocate a “parameters”
	//2. use “parameters” to specify the first half of the array
      //3. create the first thread
    parameters *p1 = malloc(sizeof(parameters));
	p1->from_index = 0;
    p1->to_index = (SIZE / 2) - 1;
    pthread_create(&workers[0], 0, sorter, p1);

	/* establish the second sorting thread */
	//1. call malloc to allocate a “parameters”
	//2. use “parameters” to specify the first half of the array
      //3. create the second thread
    parameters *p2 = malloc(sizeof(parameters));
    p2->from_index = SIZE / 2;
    p2->to_index = SIZE;
    pthread_create(&workers[1], 0, sorter, p2);
	
	/* now wait for the 2 sorting threads to finish */
	// use ptheread_join; wait for 2 sorting threads to finish 
	pthread_join(workers[0], NULL);
    pthread_join(workers[1], NULL);

	/* establish the merge thread */
	//reuse “parameters” to hold the beginning index in each half
	//create the third thread: merge 
    parameters *p3 = malloc(sizeof(parameters));
    p3->from_index = 0;
    p3->to_index = SIZE / 2;
	pthread_create(&workers[2], 0, merger, p3);

	/* wait for the merge thread to finish */
	pthread_join(workers[2], NULL); 

	/* output the sorted array */
	printf("Sorted array is: ");
    for(int i = 0; i < SIZE; ++i) {
        printf("%d ", result[i]);
    }
	printf("\n");
	
    return 0;
}

/**
 * Sorting thread.
 *
 * This thread can essentially use any algorithm for sorting
 */

void *sorter(void *params)
{
	parameters* p = (parameters *)params;
	
	// Sorting algorithm here. It can be any sorting algorithm.
	int min_elem, temp;
	for(int i = p->from_index; i < p->to_index - 1; ++i) {
		min_elem = i;
		for(int j = i + 1; j < p->to_index; ++j) {
			if(list[j] < list[min_elem])
				min_elem = j;
		}
		// swap the found elem 
		temp = list[min_elem];
		list[min_elem] = list[i];
		list[i] = temp;
	}

	/**
	printf("array before merge is: ");
    for(int i = p->from_index; i < p->to_index; ++i) {
        printf("%d ", list[i]);
    }
	printf("\n");
	**/

	pthread_exit(0);
}

/**
 * Merge thread
 *
 * Uses simple merge sort for merging two sublists
 */

void *merger(void *params)
{
	parameters* p = (parameters *)params;
	
	//reuse “parameters” to hold the first index in each half
	//merge two sorted sublist to the arry result
    int i = 0;
	int j = p->from_index;
    int k = p->to_index;
    while(j < p->to_index && k < SIZE) {
		if(list[j] < list[k]) {
			result[i] = list[j];
			++j;
		} else {
			result[i] = list[k];
			++k;
		}
		++i;
	}
	// fill in rest of array if needed
	while(j < p->to_index) {
		result[i] = list[j];
		++j;
		++i;
	}
	while(k < SIZE) {
		result[i] = list[k];
		++k;
		++i;
	}
	
	pthread_exit(0);
}