/*
Linden Beemer
CPSC 346
Project 1 - Merge Sort
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node * next;
};

// recursively merges two lists
struct node* merge(struct node *head1, struct node *head2) {
    struct node* result;

    if(!head1) {
        return head2;
    } else if(!head2) {
        return head1;
    }

    if(head1->data <= head2->data) {
        result = head1;
        result->next = merge(head1->next, head2);
    } else {
        result = head2;
        result->next = merge(head1, head2->next);
    }

    return result;
}

// split lists recursively and merge them back together
struct node* mergesort(struct node *head, int size) {
    if(size < 2) {
        return head;
    }

    int size1 = size / 2;
    int size2 = size - size1;

    struct node* curr = head;
    for(int i = 0; i < size1 - 1; ++i) {
        curr = curr->next;
    }
    struct node *back = curr->next;
    curr->next = NULL;

    head = mergesort(head, size1);
    back = mergesort(back, size2);

    return merge(head, back);
}

// utility function for printing lists
void printList(struct node *head) {
    struct node* curr = head;
    while(curr) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
}

int main() {
    // merge test 1
    printf("merge test 1, list 1 = 10, list 2 = 5\n");
    struct node* test1 = (struct node*)malloc(sizeof(struct node));
    test1->data = 10;
    struct node* test2 = (struct node*)malloc(sizeof(struct node));
    test2->data = 5;
    struct node* result = merge(test1, test2);
    printList(result);
    printf("\n");

    // merge test 2
    printf("merge test 2, list 1 = 10, 25, list 2 = 5, 13\n");
    struct node* test3 = (struct node*)malloc(sizeof(struct node));
    test3->data = 25;
    test1->next = test3;
    struct node* test4 = (struct node*)malloc(sizeof(struct node));
    test4->data = 13;
    test2->next = test4;
    result = merge(test1, test2);
    printList(result);
    printf("\n");

    // sort test 1 (list is 10, 25, 5, 13)
    printf("sort test 1, list = 10, 25, 5, 13\n");
    struct node* test5 = (struct node*)malloc(sizeof(struct node));
    test5->data = 10;
    struct node* test6 = (struct node*)malloc(sizeof(struct node));
    test6->data = 25;
    test5->next = test6;
    struct node* test7 = (struct node*)malloc(sizeof(struct node));
    test7->data = 5;
    test6->next = test7;
    struct node* test8 = (struct node*)malloc(sizeof(struct node));
    test8->data = 13;
    test7->next = test8;
    result = mergesort(test5, 4);
    printList(result);
}