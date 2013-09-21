#include "queue1.h"

void reset(queue* q) {

	q->first = 0;
    q->last = MAX_SIZE-1;
    q->count = 0;
}

int isEmpty(const queue* q) {
	
	return (q->count <= 0);
}

int isFull(const queue* q) {

	return (q->count >= MAX_SIZE);
}

void enqueue(void* n, queue* q) {

	if (!isFull(q)) {

		q->last = (q->last+1) % MAX_SIZE;
        q->q[ q->last ] = n;    
        q->count++;
    }
}


void* dequeue(queue* q) {

	void* ret = NULL;

	if (isEmpty(q)) {
		return NULL;
	} else {

		ret = q->q[ q->first ];
		q->first = (q->first+1) % MAX_SIZE;
		q->count--;

		return ret;
    }
}

void* front(queue* q) {

	void* ret = NULL;

	if (isEmpty(q)) {
		return NULL;
	} else {

		ret = q->q[ q->first ];

		return ret;
    }
}



