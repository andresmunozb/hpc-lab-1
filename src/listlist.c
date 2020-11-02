#include "list.h"
#include "listlist.h"

ListList *ll_create()
{
    ListList *ll = (ListList *)malloc(sizeof(ListList));
    ll->len = 0;
    return ll;
}

void ll_print(ListList *listlist)
{
    for (int i = 0; i < listlist->len; i++)
    {
        list_print(&listlist->data[i]);
    }
    printf("\n");
}

void ll_free(ListList *listlist){
    if(listlist->len == 0){
        free(listlist);
    }
    else{
        for (int i=0;i<listlist->len;i++){
            list_free(&listlist->data[i]);
        }
        free(listlist->data);
        free(listlist);
    }
}

void ll_append(ListList *listlist, List new_element)
{
    if (listlist->len == 0)
    {
        listlist->data = (List *)malloc(sizeof(List));
        listlist->data[0] = new_element;
    }
    else
    {
        listlist->data = (List *)realloc(listlist->data, (listlist->len + 1) * sizeof(List));
        listlist->data[listlist->len] = new_element;
    }
    listlist->len++;
}
void ll_delete(ListList *listlist, int index)
{
    if (index < 0 || index > listlist->len)
    {
        printf("Invalid position! Please enter position between 1 to %d", listlist->len);
    }
    else
    {
        list_free(&listlist->data[index]);
        /* Copy next element value to current element */
        for (int i = index; i < listlist->len - 1; i++)
        {
            listlist->data[i] = listlist->data[i + 1];
        }

        /* Decrement array size by 1 */
        listlist->data = (List *)realloc(listlist->data, (listlist->len - 1) * sizeof(List));
        listlist->len--;
    }
}
float ll_pop_min(ListList *listlist)
{
    float min = listlist->data[0].data[0];
    int index = 0;
    for (int i = 1; i < listlist->len; i++)
    {
        if (min > listlist->data[i].data[0])
        {
            min = listlist->data[i].data[0];
            index = i;
        }
    }
    min = list_pop(&listlist->data[index]);
    if(listlist->data[index].len == 0){
        ll_delete(listlist,index);
    }
    return min;
}


int ll_is_empty(ListList *listlist)
{
    if (listlist->len == 0)
    {
        return 1;
    }
    for (int i = 0; i < listlist->len; i++)
    {
        if (listlist->data[i].len != 0)
        {
            return 0;
        }
    }
    return 1;
}

void ll_merge(ListList *listlist, List *list)
{
    while(!ll_is_empty(listlist)){
        list_append(list,ll_pop_min(listlist));
    }
}

int main()
{
    ListList *ll = ll_create();
    List *l1 = list_create();
    list_append(l1, 1.2);
    list_append(l1, 1.3);
    list_append(l1, 1.8);
    list_append(l1, 2.4);
    list_append(l1, 3.3);
    List *l2 = list_create();
    list_append(l2,1.1);
    list_append(l2,1.4);
    list_append(l2,1.5);
    list_append(l2,2.1);
    list_append(l2,3.0);
    ll_append(ll,*l1);
    ll_append(ll,*l2);
    List *l3 = list_create();
    ll_merge(ll,l3);
    list_print(l3);
    ll_free(ll);
    return 0;
}