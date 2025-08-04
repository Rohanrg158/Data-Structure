#include <stdio.h>
#define MAX 5
int queue[MAX];
int front = -1, rear = -1;
int isEmpty() {
    return front == -1;
}
int isFull() {
    return (rear + 1) % MAX == front;
}
void enqueue(int val) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }
    queue[rear] = val;
    printf("Enqueued %d\n", val);
}
int dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return -1;
    }
    int val = queue[front];
    if (front == rear) {  // Queue has only one element
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
    printf("Dequeued %d\n", val);
    return val;
}
void displayQueue() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}
int main() {
    int choice, value;

    while(1) {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    }
    return 0;
}
