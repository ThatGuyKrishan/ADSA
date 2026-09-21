#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* rear = NULL;

void enqueue(int val) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = val;
    if (rear == NULL) {
        rear = temp;
        rear->next = rear; // Points to itself
    } else {
        temp->next = rear->next;
        rear->next = temp;
        rear = temp;
    }
    printf("Inserted: %d\n", val);
}

void dequeue() {
    if (rear == NULL) {
        printf("Queue Underflow\n");
        return;
    }
    struct Node* front = rear->next;
    printf("Dequeued: %d\n", front->data);
    
    if (rear == front) { // Only one element left
        rear = NULL;
    } else {
        rear->next = front->next;
    }
    free(front);
}

void display() {
    if (rear == NULL) {
        printf("Queue is Empty\n");
        return;
    }
    struct Node* temp = rear->next;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != rear->next);
    printf("\n");
}

int main() {
    int choice, val;
    while (1) {
        printf("\n--- Circular Queue (Linked List) ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                enqueue(val);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
