#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef char *data_t;

const int ELEM_POISON = 0xBE;

struct elem_t {
        data_t data = nullptr;
        int next = 0;
        int prev = 0;
};

struct list_t {
        elem_t *elem = nullptr;
        int cap = 0;
        int free = 0;
        int tail = 0;
        bool ordered = true;
};

// Resizes list.
void
list_resize(list_t *list, int new_cap);
// Construct list.
void
list_ctor(list_t *list, int cap);
// Inserts element to the list after position pos.
void
list_insert(list_t *list, data_t data, int pos);
// Inserts element to the list to the beginning of the list.
void
list_insert_front(list_t *list, data_t data);
// Inserts element to the list to the enf of the list.
void
list_insert_back(list_t *list, data_t data);
// Removes element out of list.
void
list_remove(list_t *list, int num);
// Sorts elements of the list in logical order.
void
list_sort(list_t *list);
// Finds element in the list by logical position
// excluding the zero element.
int
list_find(const list_t *list, int pos);
// Destroy list.
void
list_dtor(list_t *list);
// Checks condition of list.
bool
list_verify(list_t *list);

#endif // LIST_H

