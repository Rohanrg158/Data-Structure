#include <stdio.h>
#define MAX 100
int queue[MAX];
int qfront = -1, qrear = -1;
int qIsEmpty() { return qfront == -1; }
int qIsFull() { return qrear == MAX - 1; }
void enqueue(int val) {
    if (qIsFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (qIsEmpty()) qfront = 0;
    queue[++qrear] = val;
    printf("Enqueued %d to Queue\n", val);
}
int dequeue() {
    if (qIsEmpty()) {
        printf("Queue Underflow\n");
        return -1;
    }
    int val = queue[qfront];
    if (qfront == qrear) qfront = qrear = -1;
    else qfront++;
    printf("Dequeued %d from Queue\n", val);
    return val;
}
void displayQueue() {
    if (qIsEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = qfront; i <= qrear; i++) printf("%d ", queue[i]);
    printf("\n");
}
int deque[MAX];
int dfront = -1, drear = -1;
int dIsEmpty() { return dfront == -1; }
int dIsFull() { return (dfront == 0 && drear == MAX-1) || (dfront == drear + 1); }
void insertFront(int val) {
    if (dIsFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if (dIsEmpty()) dfront = drear = 0;
    else if (dfront == 0) dfront = MAX - 1;
    else dfront--;
    deque[dfront] = val;
    printf("Inserted %d at front of Deque\n", val);
}
void insertRear(int val) {
    if (dIsFull()) {
        printf("Deque Overflow\n");
        return;
    }
    if (dIsEmpty()) dfront = drear = 0;
    else if (drear == MAX - 1) drear = 0;
    else drear++;
    deque[drear] = val;
    printf("Inserted %d at rear of Deque\n", val);
}
int deleteFront() {
    if (dIsEmpty()) {
        printf("Deque Underflow\n");
        return -1;
    }
    int val = deque[dfront];
    if (dfront == drear) dfront = drear = -1;
    else dfront = (dfront == MAX - 1) ? 0 : dfront + 1;
    printf("Deleted %d from front of Deque\n", val);
    return val;
}
int deleteRear() {
    if (dIsEmpty()) {
        printf("Deque Underflow\n");
        return -1;
    }
    int val = deque[drear];
    if (dfront == drear) dfront = drear = -1;
    else drear = (drear == 0) ? MAX - 1 : drear - 1;
    printf("Deleted %d from rear of Deque\n", val);
    return val;
}
void displayDeque() {
    if (dIsEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque: ");
    int i = dfront;
    while (1) {
        printf("%d ", deque[i]);
        if (i == drear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}
int main() {
    int choice, val;
    while (1) {
        printf("\nChoose:\n");
        printf("1. Enqueue (Queue)\n2. Dequeue (Queue)\n3. Display Queue\n");
        printf("4. Insert Front (Deque)\n5. Insert Rear (Deque)\n6. Delete Front (Deque)\n7. Delete Rear (Deque)\n8. Display Deque\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &val);
                enqueue(val);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Enter value to insert at front of deque: ");
                scanf("%d", &val);
                insertFront(val);
                break;
            case 5:
                printf("Enter value to insert at rear of deque: ");
                scanf("%d", &val);
                insertRear(val);
                break;
            case 6:
                deleteFront();
                break;
            case 7:
                deleteRear();
                break;
            case 8:
                displayDeque();
                break;
            case 9:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}

