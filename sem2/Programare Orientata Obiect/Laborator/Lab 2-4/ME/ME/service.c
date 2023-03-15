#include "service.h"
#include "sorting.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

Inventory* create_inventory() {
	Inventory* inv = malloc(sizeof(Inventory));
	if (inv) {
		inv->l = create_list();
		inv->undo_list = create_list();
	}
	return inv;
}

void destroy_inventory(Inventory* inv) {
	destroy_list(inv->l, destroy_product);
	destroy_list(inv->undo_list, destroy_products_list);
	free(inv);
}

int add_product(Inventory* inv, int id, char* type, char* producer, char* model, float price, int quantity) {
	Product* p = create_product(id, type, producer, model, price, quantity);
	int error = validate(p);
	if (error == 1) {
		destroy_product(p);
		return 1;  // the product is invalid
	}
	for (int i = 0; i < nr_elems(inv->l); i++) {
		if (strcmp(p->type, get_type(inv->l->elems[i])) == 0 && strcmp(p->producer, get_producer(inv->l->elems[i])) == 0 &&
			strcmp(p->model, get_model(inv->l->elems[i])) == 0 && p->price == get_price(inv->l->elems[i])) {
			Product* p1 = get_elem(inv->l, i);
			add(inv->undo_list, copy_list(inv->l));
			set_elem(inv->l, i, p);
			destroy_product(p1);
			return 2;  // the product was already in the list and the quantity has been updated
		}
	}
	add(inv->undo_list, copy_list(inv->l));
	add(inv->l, p);
	return 0;  // the product has been added
}

void test_add() {
	Inventory* inv = create_inventory();
	assert(add_product(inv, 1, "a", "b", "c", 1, 2) == 0);
	assert(strcmp(get_type(inv->l->elems[0]), "a") == 0);
	assert(strcmp(get_model(inv->l->elems[0]), "c") == 0);
	assert(get_quantity(inv->l->elems[0]) == 2);

	assert(add_product(inv, 2, "a", "b", "c", 1, 10) == 2);
	assert(get_quantity(inv->l->elems[0]) == 10);

	assert(add_product(inv, 3, "", "d", "e", -4, 10) == 1);
	destroy_inventory(inv);
}

int update_product(Inventory* inv, int id, float new_price, int new_quantity) {
	Product* prod;
	Product* new_prod;
	int poz = -1;
	int i = 0;
	while (i < inv->l->lg && poz == -1) {
		prod = get_elem(inv->l, i);
		if (prod->id == id) {
			poz = i;
			break;
		}
		i++;
	}
	if (poz == -1)
		return 2; // the product with the given id does not exist

	prod = get_elem(inv->l, poz);
	if (new_price == -1) {
		new_prod = create_product(prod->id, prod->type, prod->producer, prod->model, prod->price, new_quantity);
	}
	else {
		new_prod = create_product(prod->id, prod->type, prod->producer, prod->model, new_price, prod->quantity);
	}
	int error = validate(new_prod);
	if (error == 1) {
		destroy_product(new_prod);
		return 1; // the new product is not valid
	}
	add(inv->undo_list, copy_list(inv->l));
	set_elem(inv->l, poz, new_prod);
	destroy_product(prod);
	return 0; // the product has been succesfully updated
}

void test_update() {
	Inventory* inv = create_inventory();
	add_product(inv, 1, "a", "b", "c", 1, 2);
	assert(update_product(inv, 2, -1, 10) == 2);
	assert(update_product(inv, 1, -1, -10) == 1);
	
	assert(update_product(inv, 1, 10.3f, -1) == 0);
	Product* p = get_elem(inv->l, 0);
	assert(fabs(p->price - 10.3) < 0.00001);
	assert(update_product(inv, 1, -1, 15) == 0);
	p = get_elem(inv->l, 0);
	assert(p->quantity == 15);
	destroy_inventory(inv);
}

int delete_product(Inventory* inv, int id) {
	int poz = -1;
	int i = 0;
	while (i < inv->l->lg && poz == -1) {
		Product* p = get_elem(inv->l, i);
		if (p->id == id) {
			poz = i;
			break;
		}
		i++;
	}
	if (poz == -1)
		return 1; // the product with the given id does not exist
	add(inv->undo_list, copy_list(inv->l));
	Product* p2 = get_elem(inv->l, poz);
	for (i = poz; i < inv->l->lg - 1; i++) {
		Product* p = get_elem(inv->l, i + 1);
		set_elem(inv->l, i, p);
	}
	destroy_product(p2);
	inv->l->lg--;
	return 0; // the product was succesfully deleted
}

void test_delete() {
	Inventory* inv = create_inventory();
	Product* p;
	p = create_product(1, "a", "b", "c", 1.1f, 2);
	add(inv->l, p);
	p = create_product(2, "d", "e", "f", 2.2f, 4);
	add(inv->l, p);
	assert(nr_elems(inv->l) == 2);
	assert(delete_product(inv, -3) == 1);
	assert(delete_product(inv, 3) == 1);
	assert(delete_product(inv, 1) == 0);
	assert(nr_elems(inv->l) == 1);
	p = get_elem(inv->l, 0);
	assert(p->id == 2);
	assert(strcmp(p->type, "d") == 0);
	assert(strcmp(p->model, "f") == 0);
	assert(p->quantity == 4);
	destroy_inventory(inv);
}

int cmp_price1(Product* p1, Product* p2) {
	if (p1->price <= p2->price)
		return 0;
	else
		return 1;
}

int cmp_price2(Product* p1, Product* p2) {
	if (p1->price >= p2->price)
		return 0;
	else
		return 1;
}

int cmp_quantity1(Product* p1, Product* p2) {
	if (p1->quantity <= p2->quantity)
		return 0;
	else
		return 1;
}

int cmp_quantity2(Product* p1, Product* p2) {
	if (p1->quantity >= p2->quantity)
		return 0;
	else
		return 1;
}

List* sort_products(Inventory* inv, int criteria) {
	List* rez = copy_list(inv->l);
	if (criteria == 1)
		sort(rez, cmp_price1);
	else if (criteria == 2)
		sort(rez, cmp_price2);
	else if (criteria == 3)
		sort(rez, cmp_quantity1);
	else
		sort(rez, cmp_quantity2);
	return rez;
}

void test_sort() {
	Inventory* inv = create_inventory();
	Product* p1 = create_product(1, "a", "b", "c", 10.3f, 2);
	add(inv->l, p1);
	Product* p2 = create_product(2, "d", "e", "f", 8.6f, 5);
	add(inv->l, p2);
	
	List* rez = sort_products(inv, 1);
	assert(get_id(rez->elems[0]) == 2);
	destroy_list(rez, destroy_product);
	
	rez = sort_products(inv, 2);
	assert(get_id(rez->elems[0]) == 1);
	destroy_list(rez, destroy_product);

	rez = sort_products(inv, 3);
	assert(get_id(rez->elems[0]) == 1);
	destroy_list(rez, destroy_product);

	rez = sort_products(inv, 4);
	assert(get_id(rez->elems[0]) == 2);
	destroy_list(rez, destroy_product);
	
	destroy_inventory(inv);


	inv = create_inventory();
	p1 = create_product(1, "d", "e", "f", 8.6f, 5);
	add(inv->l, p1);
	p2 = create_product(2, "a", "b", "c", 10.3f, 2);
	add(inv->l, p2);

	rez = sort_products(inv, 1);
	assert(get_id(rez->elems[0]) == 1);
	destroy_list(rez, destroy_product);

	rez = sort_products(inv, 2);
	assert(get_id(rez->elems[0]) == 2);
	destroy_list(rez, destroy_product);

	rez = sort_products(inv, 3);
	assert(get_id(rez->elems[0]) == 2);
	destroy_list(rez, destroy_product);

	rez = sort_products(inv, 4);
	assert(get_id(rez->elems[0]) == 1);

	destroy_list(rez, destroy_product);

	destroy_inventory(inv);
}

List* filter_producer(Inventory* inv, char* producer) {
	List* rez = create_list();
	for (int i = 0; i < inv->l->lg; i++) {
		Product* p = get_elem(inv->l, i);
		if (strcmp(p->producer, producer) == 0) {
			add(rez, copy_product(p));
		}
	}
	return rez;
}

void test_filter_producer() {
	Inventory* inv = create_inventory();
	add_product(inv, 1, "a", "b", "c", 10.3f, 12);
	add_product(inv, 2, "d", "e", "f", 10.2f, 1);
	add_product(inv, 3, "g", "b", "h", 2.3f, 3);
	List* rez = filter_producer(inv, "b");
	assert(rez->lg == 2);
	assert(get_id(rez->elems[0]) == 1);
	assert(get_id(rez->elems[1]) == 3);
	destroy_list(rez, destroy_product);

	rez = filter_producer(inv, "abc");
	assert(rez->lg == 0);
	destroy_list(rez, destroy_product);

	destroy_inventory(inv);
}

List* filter_price(Inventory* inv, float min_price, float max_price) {
	List* rez = create_list();
	for (int i = 0; i < inv->l->lg; i++) {
		Product* p = get_elem(inv->l, i);
		if (p->price >= min_price && p->price <= max_price) {
			add(rez, copy_product(p));
		}
	}
	return rez;
}

void test_filter_price() {
	Inventory* inv = create_inventory();
	add_product(inv, 1, "a", "b", "c", 10.3f, 12);
	add_product(inv, 2, "d", "e", "f", 7.2f, 1);
	add_product(inv, 3, "g", "b", "h", 2.3f, 3);
	List* rez = filter_price(inv, 6.5f, 11.9f);
	assert(rez->lg == 2);
	assert(get_id(rez->elems[0]) == 1);
	assert(get_id(rez->elems[1]) == 2);

	destroy_list(rez, destroy_product);

	rez = filter_price(inv, 3.5f, 5.6f);
	assert(rez->lg == 0);
	destroy_list(rez, destroy_product);

	destroy_inventory(inv);
}

List* filter_quantity(Inventory* inv, int quantity) {
	List* rez = create_list();
	for (int i = 0; i < inv->l->lg; i++) {
		Product* p = get_elem(inv->l, i);
		if (p->quantity >= quantity) {
			add(rez, copy_product(p));
		}
	}
	return rez;
}

void test_filter_quantity() {
	Inventory* inv = create_inventory();
	add_product(inv, 1, "a", "b", "c", 10.3f, 12);
	add_product(inv, 2, "d", "e", "f", 10.2f, 1);
	add_product(inv, 3, "g", "b", "h", 2.3f, 3);
	List* rez = filter_quantity(inv, 3);
	assert(rez->lg == 2);
	assert(get_id(rez->elems[0]) == 1);
	assert(get_id(rez->elems[1]) == 3);
	destroy_list(rez, destroy_product);

	rez = filter_quantity(inv, 20);
	assert(rez->lg == 0);
	destroy_list(rez, destroy_product);

	destroy_inventory(inv);
}

int undo(Inventory* inv) {
	if (nr_elems(inv->undo_list) == 0) {
		return 1;
	}
	destroy_list(inv->l, destroy_product);
	int index = nr_elems(inv->undo_list) - 1;
	List* new_list = get_elem(inv->undo_list, index);
	inv->l = new_list;
	inv->undo_list->lg--;
	return 0;
}

void test_undo() {
	Inventory* inv = create_inventory();
	assert(undo(inv) == 1);
	add_product(inv, 1, "a", "b", "c", 10.0f, 2);
	assert(nr_elems(inv->undo_list) == 1);
	add_product(inv, 1, "a", "b", "c", 10.0f, 7);
	assert(nr_elems(inv->undo_list) == 2);
	assert(undo(inv) == 0);
	assert(nr_elems(inv->undo_list) == 1);
	destroy_inventory(inv);
}