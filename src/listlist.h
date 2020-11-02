#ifndef LISTLIST_HEADER
#define LISTLIST_HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct ListList
{
    int len;
    List *data;
} ListList;

ListList *ll_create();
void ll_print(ListList *listlist);
void ll_append(ListList *listlist, List new_element);
void ll_delete(ListList *listlist, int index);
float ll_pop_min(ListList *listlist);
int ll_is_empty(ListList *listlist);
void ll_merge(ListList *listlist, List *list);

#endif