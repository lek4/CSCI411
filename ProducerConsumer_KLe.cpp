/* 
 * Name: Katherine Le
 * CSCI 411
 * Lab: Semaphore
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>         // for sleep function
#include <semaphore.h>

#define BUFF_SIZE   5		/* total number of slots */
#define NP          3		/* total number of producers */
#define NC          3		/* total number of consumers */
#define NITERS      4		/* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;         	  /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;        	  /* buf[out%BUFF_SIZE] is the first full slot */
    sem_t full;     	  /* keep track of the number of full spots */
    sem_t empty;    	  /* keep track of the number of empty spots */
    //  sem_t mutex;       /* enforce mutual exclusion to shared data - but need to use pthread for Linux */
} sbuf_t;

sbuf_t shared;

// for keeping track of circular array:
int numBufferItems = 0;     // buffer is initially 0
int rear = -1;
int front = 0;

pthread_mutex_t theMutex;   // pthread mutex

void *Producer(void *arg)
{
    int i, item, index;
 
   /* Fill in the code here */
    item = rand() % 20;
    index = 0;
    for (i=0; i < NITERS; i++) {

        /* Fill in the code here */
        if(numBufferItems < NITERS)
        {
            // Add to buffer
            sem_wait(&shared.empty);
            pthread_mutex_lock(&theMutex);
            shared.buf[index] = item;
            index++;
            pthread_mutex_unlock(&theMutex);
            sem_post(&shared.full);
            printf("Producer produced %d\n",item);
        }        
        else
        {
            sleep(2);
            printf("Error with producer");
        }

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    /* Fill in the code here */
    int item;
    // Remove from buffer when buffer is full
    sem_wait(&shared.full);
    pthread_mutex_lock(&theMutex);
    item = shared.buf[numBufferItems -1];
    numBufferItems--;
    pthread_mutex_unlock(&theMutex);
    sem_post(&shared.empty);
    
    printf("Consumer consumed %d\n",item);
    sleep(2);
}

// insert item into buffer
int insert_item(int item) 
{
    // Add item to circular queue
    rear =(rear+1)%BUFF_SIZE;
    shared.buf[rear] = item;
    numBufferItems++;
}

// delete item from buffer
int remove_item(int item)
{
    // Delete item from circular queue
    front=(front+1)%BUFF_SIZE;
    numBufferItems--;
}


/******************************************************
* Main Begins Here *
******************************************************/
int main()
{
    pthread_t idP, idC;
    int index;

    /* Insert code here to initialize semaphores */
    sem_init(&shared.full, 0, 5);
    sem_init(&shared.empty, 0, 0);
    // initialize mutex
    pthread_mutex_init(&theMutex, NULL);

    for (index = 0; index < NP; index++)
    {  
       /* Create a new producer */
       pthread_create(&idP, NULL, Producer, &index);
    }

    /* Insert code here to create NC consumers */
    pthread_create(&idP, NULL, Producer, &index);
    for (index = 0; index < NC; index++)
    {  
       pthread_create(&idC, NULL, Consumer, &index);
    }
    
    pthread_exit(NULL);
    sem_destroy(&shared.full);
    sem_destroy(&shared.empty);
    pthread_mutex_destroy(&theMutex);
    return 0;
}