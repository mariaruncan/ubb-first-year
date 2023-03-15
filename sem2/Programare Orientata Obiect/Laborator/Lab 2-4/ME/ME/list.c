#include "list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

List* create_list() {
	List* l = malloc(sizeof(List));
	if (l) {
		l->lg = 0;
		l->cap = 2;
		l->elems = (Telem*)malloc(l->cap * sizeof(Telem));
	}
	return l;
}

void destroy_products_list(List* l) {
	destroy_list(l, destroy_product);
}

void destroy_list(List* l, DestroyFunction destrF) {
	int i;
	for (i = 0; i < l->lg; i++) {
		destrF(l->elems[i]);
	}
	free(l->elems);
	free(l);
}

Telem get_elem(List* l, int index) {
	return l->elems[index];
}

Telem set_elem(List* l, int index, Telem elem) {
	l->elems[index] = elem;
	return l->elems[index];
}

int nr_elems(List* l) {
	return l->lg;
}

void resize(List* l) {
	int new_cap = l->cap + 2;
	Telem* new_elems = malloc(new_cap * sizeof(Telem));
	//copy elements
	if (new_elems) {
		for (int i = 0; i < l->lg; i++) {
			*(new_elems + i) = l->elems[i];
		}
		//deallocate old vector
		free(l->elems);
		l->elems = new_elems;
		l->cap = new_cap;
	}
}

void add(List* l, Telem el) {
	if (l->lg == l->cap)
		resize(l);
	l->elems[l->lg] = el;
	(l->lg)++;
}

List* copy_list(List* l) {
	List* rez = create_list();
	for (int i = 0; i < l->lg; i++) {
		Telem p = get_elem(l, i);
		add(rez, copy_product(p));
	}
	return rez;
}

void test_create_list() {
	List* l = create_list();
	assert(nr_elems(l) == 0);
	destroy_list(l, destroy_product);
}

void test_iterate_list() {
	List* l = create_list();
	add(l, create_product(1, (char*)"a", (char*)"b", (char*)"c", 1, 2)); 
	add(l, create_product(2, (char*)"d", (char*)"e", (char*)"f", 3, 4));
	assert(nr_elems(l) == 2);

	Product* p = get_elem(l, 0);
	assert(p->id == 1);
	assert(strcmp(p->type, "a") == 0);
	p = get_elem(l, 1);
	assert(p->id == 2);
	assert(p->price == 3.0);
	destroy_list(l, destroy_product);
}

void test_copy_list() {
	List* l = create_list();
	add(l, create_product(1, (char*)"a", (char*)"b", (char*)"c", 1, 2));
	add(l, create_product(2, (char*)"d", (char*)"e", (char*)"f", 3, 4));
	List* l2 = copy_list(l);
	assert(nr_elems(l2) == 2);
	Product* p = get_elem(l, 1);
	assert(strcmp(p->model, "f") == 0);
	destroy_list(l, destroy_product);
	destroy_list(l2, destroy_product);
}

void test_resize() {
	List* l = create_list();
	for (int i = 0; i < 8; i++)
		add(l, create_product(1, (char*)"a", (char*)"b", (char*)"c", 1, 2));
	assert(nr_elems(l) == 8);
	destroy_list(l, destroy_product);
}

void test_list_of_lists() {
	List* products = create_list();
	add(products, create_product(1, "a", "a", "a", 1.0f, 1));
	add(products, create_product(2, "a", "a", "a", 1.0f, 1));

	List* products2 = create_list();

	List* undo_list = create_list();
	add(undo_list, products);
	assert(nr_elems(undo_list) == 1);
	add(undo_list, products2);
	assert(nr_elems(undo_list) == 2);

	destroy_list(undo_list, destroy_products_list);
}