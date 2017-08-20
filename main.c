#include "kernel.h"
#include "tools.h"

#include <stdio.h>

#include "kernel_data.h"

void isr_off() {}
void isr_on()  {}

#include "messages.h"
#include "tasks.h"
#include "timing.h"

#include "kernel_init.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void TimerInt(void) { tickCounter++; }

STRUCT(Node) {
    int     data;
    Node*   pNext;
    Node*   pPrevious;
};

STRUCT(List) {
    Node* pHead;
    Node* pTail;
};

static void insert(Node* new, Node* prev, Node* next) {
    next->pPrevious  = new;
    new->pNext       = next;
    new->pPrevious   = prev;
    prev->pNext      = new;
}

//#define addFirst(L, N)          insert((N), dummyNode(L), firstNode(L))
//#define addLast(L, N)           insert((N), lastNode(L),  dummyNode(L))

int main(void) {

    List list = { alloc(sizeof (Node)), list.pHead };

    initList(&list);

    Node n1 = { 1, NULL, NULL }, n2 =  { 2, NULL, NULL }, n3 = { 3, NULL, NULL };

    addFirst(&list, &n1);
    addFirst(&list, &n2);
    addFirst(&list, &n3);

    //addFirst(&list, &n2);
    //addTask(&list, &n3);

    forEach(Node, &list) { printf("%d!\n", iter->data); }

    printf("\n");

    forReve(Node, &list) { printf("%d!\n", iter->data); }


    //char strBuffer[] = "Hello, world!";

    /*
    mailbox* mBox = create_mailbox(10, 20);
    
    create_msg_first(mBox, "1!\n");
    create_msg_first(mBox, "2!\n");
    create_msg_first(mBox, "3!\n");
    create_msg_last(mBox, "4!\n");
    create_msg_first(mBox, "5!\n");
    create_msg_first(mBox, "4!\n");

    msg* iter = getFirstMsg(mBox);

    while (iter != mBox->pTail) {
        printf(iter->pData);
        iter = iter->pNext;
    }
    */

    printf("DONE");

    /*
    init_kernel();
    run();
    
    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }*/
}

