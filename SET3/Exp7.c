#include <stdio.h>
#define MAX 100

// Basic Queue Structure using Array
typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front > q->rear;
}

void enqueue(Queue* q, int x) {
    if (q->rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    q->arr[++(q->rear)] = x;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    return q->arr[(q->front)++];
}

// ==========================================
// METHOD 1: Costly Push (Push O(N), Pop O(1))
// ==========================================
Queue q1, q2;

void push1(int x) {
    enqueue(&q2, x);
    while (!isEmpty(&q1)) {
        enqueue(&q2, dequeue(&q1));
    }
    // Swap q1 and q2
    Queue temp = q1;
    q1 = q2;
    q2 = temp;
}

int pop1() {
    if (isEmpty(&q1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(&q1);
}

// ==========================================
// METHOD 2: Costly Pop (Push O(1), Pop O(N))
// ==========================================
Queue q_1, q_2;

void push2(int x) {
    enqueue(&q_1, x);
}

int pop2() {
    if (isEmpty(&q_1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    // Move all elements except the last one to q_2
    while (q_1.front < q_1.rear) {
        enqueue(&q_2, dequeue(&q_1));
    }
    // The last element is the popped item
    int popped = dequeue(&q_1);
    
    // Swap q_1 and q_2
    Queue temp = q_1;
    q_1 = q_2;
    q_2 = temp;
    
    // Reset q_2 pointers for future operations
    q_2.front = 0;
    q_2.rear = -1;
    
    return popped;
}

// ==========================================
// Main Driver Program
// ==========================================
int main() {
    int method, choice, val;

    initQueue(&q1); initQueue(&q2);
    initQueue(&q_1); initQueue(&q_2);

    printf("Select Implementation Method:\n");
    printf("1. Method 1 (Costly Push)\n");
    printf("2. Method 2 (Costly Pop)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &method);

    if (method == 1) {
        printf("\n--- Stack Using Two Queues (Costly Push) ---\n");
        while (1) {
            printf("\n1. Push\n2. Pop\n3. Exit\nEnter choice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter value to push: ");
                scanf("%d", &val);
                push1(val);
            } else if (choice == 2) {
                val = pop1();
                if (val != -1) printf("Popped: %d\n", val);
            } else {
                break;
            }
        }
    } else if (method == 2) {
        printf("\n--- Stack Using Two Queues (Costly Pop) ---\n");
        while (1) {
            printf("\n1. Push\n2. Pop\n3. Exit\nEnter choice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter value to push: ");
                scanf("%d", &val);
                push2(val);
            } else if (choice == 2) {
                val = pop2();
                if (val != -1) printf("Popped: %d\n", val);
            } else {
                break;
            }
        }
    } else {
        printf("Invalid selection.\n");
    }

    return 0;
}
