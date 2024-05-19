#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode; 
    return newNode;
}


void addNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* tail = (*head)->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}


void printList(Node* head) {
    if (head == NULL) return;
    Node* temp = head;
    do {
        printf("Memory Address: %p, Data: %d\n", temp, temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}


void sortList(Node** head) {
    if (*head == NULL || (*head)->next == *head) return; 

    Node *current, *index, *tempNode;
    for (current = *head; current->next != *head; current = current->next) {
        for (index = current->next; index != *head; index = index->next) {
            if (current->data > index->data) {
                
                if (current->next == index) {
                    current->next = index->next;
                    index->prev = current->prev;
                    current->prev->next = index;
                    index->next->prev = current;
                    current->prev = index;
                    index->next = current;
                } else {
                    Node* tempNext = current->next;
                    Node* tempPrev = current->prev;
                    current->next = index->next;
                    current->prev = index->prev;
                    index->next->prev = current;
                    index->prev->next = current;
                    index->next = tempNext;
                    index->prev = tempPrev;
                    tempNext->prev = index;
                    tempPrev->next = index;
                }
                
                if (*head == current) *head = index;
                else if (*head == index) *head = current;
                tempNode = current;
                current = index;
                index = tempNode;
            }
        }
    }
}

int main() {
    Node* head = NULL;
    int N, data;

    printf("Masukkan jumlah data: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        printf("Masukkan data ke-%d: ", i + 1);
        scanf("%d", &data);
        addNode(&head, data);
    }

    printf("\nList sebelum pengurutan:\n");
    printList(head);

    sortList(&head);

    printf("List setelah pengurutan:\n");
    printList(head);

    return 0;
}
