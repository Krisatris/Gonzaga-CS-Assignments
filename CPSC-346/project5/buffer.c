/**
 * Linden Beemer
 * CPSC 346 Section 2
 */

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1

buffer_item buffer[BUFFER_SIZE];

/*define semaphores and mutex*/
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
    /* Acquire Empty Semaphore */
	sem_wait(&empty);
	
	/* Acquire mutex lock to protect buffer */
	pthread_mutex_lock(&mutex);

	buffer[insertPointer] = item;
	insertPointer = (++insertPointer) % BUFFER_SIZE;

	/* Release mutex lock and full semaphore */
	pthread_mutex_unlock(&mutex);
	sem_post(&full);

	return 0;
}

int remove_item(buffer_item *item)
{
	/* Acquire Full Semaphore */
	sem_wait(&full);

	/* Acquire mutex lock to protect buffer */
	pthread_mutex_lock(&mutex);

	*item = buffer[removePointer];
	buffer[removePointer] = -1;
	removePointer = (++removePointer) % BUFFER_SIZE;

	/* Release mutex lock and empty semaphore */
	pthread_mutex_unlock(&mutex);
	sem_post(&empty); 

	return 0;
}


int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if(argc != 4)
	{
		fprintf(stderr, "Usage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	/*call atoi to get arguments */
	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);

	/* initialize semaphores and mutex */
	printf("initalizing mutex: %d\n", pthread_mutex_init(&mutex, NULL));
	printf("initializing empty semaphore: %d\n", sem_init(&empty, 0, BUFFER_SIZE));
	printf("initializing full semaphore: %d\n", sem_init(&full, 0, 0));

	/* Create the producer and consumer threads */
	int producerIds[producerThreads];
	int consumerIds[consumerThreads];

	for(i = 0; i < producerThreads; ++i) {
		producerIds[i] = i + 1;
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, producer, &producerIds[i]);
	}

	for(j = 0; j < consumerThreads; j++) {
		consumerIds[j] = j + 1;
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, consumer, &consumerIds[j]);
	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	return 0;
}

void *producer(void *param)
{
	buffer_item item;	 

	while(TRUE)
	{
		sleep(rand() % 10);
		item = rand();
		if(insert_item(item)) {
			fprintf(stderr, "report error condition, Producer");
		}
		else {
			printf("producer produced %d\n", item);
		}
	}

}

void *consumer(void *param)
{
	buffer_item item;

	while(TRUE)
	{
		sleep(rand() % 10);
		if(remove_item(&item)) {
			fprintf(stderr, "report error condition, Consumer");
		}
		else {
			printf("consumer consumed %d\n", item);
		}
	}
}