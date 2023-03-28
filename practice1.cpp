#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void* dataPtr;
    struct node* next;
}NODE;

typedef struct stack{
    NODE* head;
    NODE* tail;
    int cnt;
    int size;
}STACK;

STACK* makeStack(){
    STACK* s = (STACK*)malloc(sizeof(STACK));

    s->head = NULL;
    s->tail = NULL;
    s->cnt = 0;
    s->size = 100;
    
    return s;
}

int isEmpty(STACK* s){
    return s->cnt <= 0;
}

int pushStack(STACK* s, int data){
    NODE* n = NULL;
    int* d = NULL;

    if (s->cnt >= s->size) {
        return 0;
    }

    n = (NODE*)malloc(sizeof(NODE));
    d = (int*)malloc(sizeof(int));
    *d = data;
    n->next = NULL;
    n->dataPtr = d;
    
    if (s->head == NULL) {
        s->head = n;
        s->tail = n;

    }
    else {
        n->next = s->tail;
        s->tail = n;
    }

    (s->cnt)++;

    return 1;

}

int popStack(STACK* s){

    int data;
    NODE* temp = NULL;

    if (isEmpty(s)) {
        return 0;
    }
    data = *(int*)(s->tail->dataPtr);
    temp = s->tail;
    s->tail = s->tail->next;
    (s->cnt)--;

    free(temp->dataPtr);
    free(temp);

    return data;
}

void traverse(STACK* s){
    NODE* loc = NULL;

    for (loc = s->tail; loc !=NULL; loc = loc->next) {
        printf("[%d]\n",*(int*)loc->dataPtr);
    }
    printf("\n");
}

STACK* concat(STACK* s1, STACK* s2){
    STACK* s3 = makeStack();
    STACK* loc = NULL;

    for (loc = s1; !((isEmpty(s1))&&(isEmpty(s2))); loc = s1) {
        if (isEmpty(s1)) {
            loc = s2;
        }
        else if (!(isEmpty(s2))) {
            if (*(int*)(loc->tail->dataPtr) < *(int*)(s2->tail->dataPtr)) {
                loc = s2;
            }
        }
        pushStack(s3,popStack(loc));
    }

    free(s1);
    free(s2);

    return s3;
}

int main()
{
    STACK* s1 = makeStack();
    STACK* s2 = makeStack();
    
    pushStack(s1, 9);
    pushStack(s1, 4);
    pushStack(s1, 2);
    pushStack(s1, 6);
    pushStack(s1, 5);
    
    pushStack(s2, 3);
    pushStack(s2, 1);
    pushStack(s2, 7);
    

    // HW 1-1
    while(s1->cnt > 0){
        traverse(s1);
        popStack(s1);
    }
    printf("--------------------------\n");
    
    // HW 1-2
    while(s2->cnt > 0){
        traverse(s2);
        popStack(s2);
    }
    printf("--------------------------\n");
    
    pushStack(s1, 9);
    pushStack(s1, 4);
    pushStack(s1, 2);
    pushStack(s1, 6);
    pushStack(s1, 5);
    
    pushStack(s2, 3);
    pushStack(s2, 1);
    pushStack(s2, 7);
    
    // HW2
    STACK* s3 = concat(s1, s2);
    traverse(s3);

    while(s3->cnt > 0){
        traverse(s3);
        popStack(s3);
    }
    
    free(s3);
    
    return 0;
}
