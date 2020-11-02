#include "list.h"

List *list_create()
{
    List *list = (List *)malloc(sizeof(List));
    list->len = 0;
    return list;
}

void list_print(List *list)
{
    for (int i = 0; i < list->len; i++)
    {
        printf("%f ", list->data[i]);
    }
    printf("\n");
}

void list_free(List *list)
{
    if (list->len != 0)
        free(list->data);
}

void list_append(List *list, float new_element)
{
    if (list->len == 0)
    {
        list->data = (float *)malloc(sizeof(float));
        list->data[0] = new_element;
    }
    else
    {
        list->data = (float *)realloc(list->data, (list->len + 1) * sizeof(float));
        list->data[list->len] = new_element;
    }
    list->len++;
}

float list_pop(List *list)
{
    float value = list->data[0];
    float *new_data = (float *)malloc(sizeof(float) * (list->len - 1));
    for (int i = 1; i < list->len; i++)
    {
        new_data[i - 1] = list->data[i];
    }
    list->data = new_data;
    list->len--;
    return value;
}

void list_load(List *list, __m128 r1)
{
    float aux[4] __attribute__((aligned(16))) = {0.0, 0.0, 0.0, 0.0};
    _mm_store_ps(aux, r1);
    for (int i = 0; i < 4; i++)
    {
        list_append(list, aux[i]);
    }
}