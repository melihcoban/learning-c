#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>


typedef struct QueueNode {
    void *value;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
    int size;
} Queue;

int enqueue(Queue *q, void *value)
{
    QueueNode *node = malloc(sizeof(struct QueueNode));

    node->value = value;
    node->next = NULL;

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


struct Queue* initialize_queue()
{
    struct Queue *q = malloc(sizeof(struct Queue));

    q->head = NULL;

    q->size = 0;

    q->tail = NULL;

    return q;
};

struct Edge {
    int vertex;
    struct Edge *next;
} Edge;

struct Graph {
    int vertices;
    struct Edge** edges;
} Graph;


struct Graph* create_graph(int v) {
    struct Graph *g = malloc(sizeof(struct Graph)); 

    g->vertices = v;

    g->edges = malloc(v * sizeof(struct Edge*));

    for (int i = 0; i < v; i++) {
        g->edges[i] = NULL;
    };

    return g;
}

struct Edge* create_edge(int v)
{
    struct Edge *e = malloc(sizeof(struct Edge));

    e->vertex = v;

    e->next = NULL;

    return e;
}

void add_edge_to_graph(struct Graph *g, int u, int v)
{
    struct Edge *e = create_edge(v);

    e->next = g->edges[u];

    g->edges[u] = e; 
}

void print_graph(struct Graph *g)
{
    printf("Vertex: Adjacency List\n");

    for (int i = 0; i < g->vertices; i++) {

        struct Edge* temp = g->edges[i];

        printf("%d ---> ", i);

        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf ("NULL \n");
    };
};

int value_in_array(int value, int *array, int array_size)
{
    for (int i = 0; i < array_size; i++) {
        if (array[i] == value)
            return 1;
    };

    return 0;
}


int bfs(struct Graph *g, int start)
{
    Queue *queue = initialize_queue();

    int visited[g->vertices] = {};

    struct Edge* startingEdge = g->edges[start];

    visited[start] = start;

    enqueue(queue, startingEdge);

    while (queue->size != 0)
    {
        struct Edge* current = dequeue(queue);

        printf("Visiting: %d\n", current->vertex);

        visited[current->vertex] = current->vertex;

        struct Edge* node = g->edges[current->vertex];

        while(node)
        {
            if (!value_in_array(node->vertex, visited, g->vertices))
                enqueue(queue, node);

            node = node->next;
        };
    };

    return 0;
};

int main()
{
    struct Graph *g = create_graph(6);

    add_edge_to_graph(g, 0, 1);
    add_edge_to_graph(g, 1, 2);
    add_edge_to_graph(g, 2, 1);
    add_edge_to_graph(g, 2, 3);
    add_edge_to_graph(g, 3, 2);
    add_edge_to_graph(g, 3, 4);
    add_edge_to_graph(g, 2, 5);
    add_edge_to_graph(g, 4, 5);

    print_graph(g);

    printf("Reachable from 0: \n");
    bfs(g, 0);

    printf("Reachable from 4: \n");
    bfs(g, 4);

    return 0;
}
