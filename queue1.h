#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10000
#define EMPTY -1
#define FULL (MAX_SIZE-1)


typedef struct queue {

	void* q[MAX_SIZE];              /* the queue array */
	int first;                      /* position of first element */
    int last;                       /* position of last element */
    int count;                      /* number of queue elements */

} queue;


void reset(queue* q);

int isEmpty(const queue* q);
int isFull(const queue* q);

void enqueue(void* n, queue* q);
void* dequeue(queue* q);
void* front(queue* q);


