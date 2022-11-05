#include<stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node * next;
    int value;
    char belongs;
} node;


void display(node * head) {
    node * current = head;
    while (current != NULL) {
        printf("\nnode %d from %c", current-> value, current-> belongs);
        current = current-> next;
    }
}


void tag(struct node * head, int numbers[6], char setTag) {
    node * current = head;
    for (int i = 0; i < 6; i++) {
        node * next = NULL;
        next = (node *) malloc(sizeof(node));
        next->value = numbers[i];
        next->belongs = setTag;
        current->next = next;
        current = next;
    }
    current->next = NULL;
}


node * intersect(node * A, node * B) {
    printf("\n\nrecursion %c %d %c %d", A->belongs, A->value, B->belongs, B->value);
    if (A->next == NULL) {
        printf("\nnull A");
        return B;
    };
    if (B->next == NULL) {
        printf("\nnull B");
        return A;
    };
    if (A->value == B->value) {
        printf("\nintersecting next next");
        return intersect(A->next, B->next);
    };
    if (A->value < B->value) {
        printf("\nintersection next A and B");
        intersect(A->next, B);
        return A;
    };
    printf("\nintersecting next B and A");
    intersect(A, B->next);
    return B;
}


int main() {

    node * headA = NULL;
    node * headB = NULL;

    headA = (node *) malloc(sizeof(node));
    headB = (node *) malloc(sizeof(node));

    int arr1[6] = {1, 4, 5, 8, 12, 13};
    int arr2[6] = {3, 4, 6, 8, 10, 14};

    tag(headA, arr1, 'A');
    tag(headB, arr2, 'B');
    
    printf("\nTAG : %d", headA->next->value);

    node * headINTS = intersect(headA, headB);
    display(headINTS);

    printf("\nTEST");

    return 0;
}