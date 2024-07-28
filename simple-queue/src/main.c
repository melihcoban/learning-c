#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/item.h"
#include <malloc.h>

typedef struct QueueNode {
    void *value;
    struct QueueNode *next;
} QueueNode;


typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    int size;
    int (*enqueue)(struct Queue *q, void* value);
    void* (*peek)(struct Queue *q);
    void* (*dequeue)(struct Queue *q);
} Queue;

int enqueue(Queue *q, void *value)
{
    QueueNode *node = malloc(sizeof(struct QueueNode));

    node->value = value;
    node->next = NULL;

    struct User *u = (struct User*)node->value;

    if (q->size == 0)
    {
        q->head = node;
        q->tail = node;
    }
    else
    {
        q->tail->next = node;
        q->tail = node;
    }

    q-> size += 1; 

    return 0;
}

void* dequeue(Queue *q)
{
    if (q->size == 0)
        return NULL;

    void* retVal = q->head->value;

    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    q->size -= 1;

    return retVal;
}

void* peek(Queue *q)
{
    if (q->tail == NULL)
        return NULL;

    return q->tail->value;
}


struct Queue initialize_queue()
{
    Queue q = {NULL, NULL, 0, enqueue, peek, dequeue };

    return q;
};



int read_from_file_and_add_to_queue(Queue* q)
{
    FILE* filePtr;
    int buffLength = 255;
    char buffer[buffLength];
    int id = 0;

    filePtr = fopen("../include/users.txt", "r");

    while (fgets(buffer, buffLength, filePtr))
    {
        id += 1; 

        struct User *u = malloc(sizeof(struct User));

        u->name = strdup(buffer);
        u->id = id;
        
        q->enqueue(q, u);
    }

    fclose(filePtr);


    return 0;
}

int dequeue_and_get_user(Queue *q)
{
    void* value = q->dequeue(q);

    if (value == NULL) {
        printf("No items left in the queue");
        return -1;
    }

    struct User *u = (struct User*)value;

    printf("Next user in queue.\nID: %d\nUsername: %s\n", u->id, u->name);

    return 0;
}

int main()
{
    Queue q = initialize_queue();

    read_from_file_and_add_to_queue(&q);

    printf("Initial queue size: %d\n", q.size);

    int result = 0;

    while(result == 0)
    {
        void* value = q.dequeue(&q);

        if (value == NULL) {
            printf("No items left in the queue");
            result = -1;
        }

        struct User *u = (struct User*)value;

        printf("Next user in queue.\nID: %d\nUsername: %s\n", u->id, u->name);
    }

    return 0;
}
