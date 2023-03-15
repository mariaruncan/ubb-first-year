#ifndef LIST_H_
#define LIST_H_
#include "product.h"

typedef void* Telem;
typedef void (*DestroyFunction)(Telem);
/*
ADT for a dynamic array
elems - a pointer to the actual list
lg - how many elements are in list
cap - how many elements can be stored
*/
typedef struct {
	Telem* elems;
	int lg;
	int cap;
}List;

/*
Create a empty list
*/
List* create_list();

void destroy_products_list(List* l);

/*
Destroy list
*/
void destroy_list(List* l, DestroyFunction destrFct);

/*
Get an element from the list
index - position of the element, needs to be valid
return element of the given position
*/
Telem get_elem(List* l, int index);

/*
Modify the element on the given position
return the new element
*/
Telem set_elem(List* l, int index, Telem elem);

/*
return number of elements in the list
*/
int nr_elems(List* l);

/*
Allocate more memory
*/
void resize(List* l);

/*
Add element into the list
post: element is added to the end of the list
*/
void add(List* l, Telem el);

/*
Make a shallow copy of the list
return a new list containing the same elements as l
*/
List* copy_list(List* l);

void test_create_list();
void test_iterate_list();
void test_copy_list();
void test_resize();
void test_list_of_lists();

#endif