#include <stdio.h>
#include <stdlib.h>
#define MAX 10  
struct Queue {
    int items[MAX];
    int front, rear;
};
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}
int isEmpty(struct Queue* q) {
    return (q->front == -1);
}
int isFull(struct Queue* q) {
    return (q->rear == MAX - 1);
}
void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}
void BFS(int graph[MAX][MAX], int startVertex, int n) {
    struct Queue q;
    initQueue(&q);
    int visited[MAX] = {0}; 
    visited[startVertex] = 1;
    enqueue(&q, startVertex);
    printf("Breadth-First Search starting from vertex %d:\n", startVertex);
    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);
        for (int i = 0; i < n; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
}
int main() {
    int graph[MAX][MAX] = {0};
    int n, e, u, v;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    printf("Enter the edges (u, v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  
    }
    int startVertex;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    BFS(graph, startVertex, n);
    return 0;
}

