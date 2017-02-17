#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "defs.h"


// inspired by the linux kernel
STRUCT(LinkedList)
{
    LinkedList* next;
    LinkedList* prev;
};


static inline void init_list(LinkedList* list)
{
    list->next = list;
    list->prev = list;
}


static inline void __list_add(LinkedList* new_elem,
                              LinkedList* prev,
                              LinkedList* next)
{
    next->prev = new_elem;
    new_elem->next = next;
    new_elem->prev = prev;
    prev->next = new_elem;
}


#define listEntry(ptr, type, member) ((type*)((char*)(ptr) - (size_t)(&((type*)0)->member)))


#define listForEach(_list) \
for (linked_list* iter = (_list)->next; iter != (_list); iter = (iter)->next)


#define listPushFront(head, elem, member) \
{ \
    __list_add(&(elem)->member, &(head)->member, (head)->member.next); \
}


#define listPushBack(head, elem, member) \
{ \
    __list_add(&(elem)->member, (head)->member.prev, &(head)->member); \
}



#endif
