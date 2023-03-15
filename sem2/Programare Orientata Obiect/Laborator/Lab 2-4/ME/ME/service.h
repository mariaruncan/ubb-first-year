#ifndef SERVICE_H_
#define SERVICE_H_
#include "list.h"

typedef struct {
	List* l;
	List* undo_list;
}Inventory;

/*
Create an inventory
*/
Inventory* create_inventory();

/*
Destroy inventory
*/
void destroy_inventory(Inventory* inv);

/*
Add a product to inventory
post: return 0 if product was added
	  return 1 if product is invalid
	  return 2 if the product was already in list and the quantity has been updated
*/
int add_product(Inventory* inv, int id, char* type, char* producer, char* model, float price, int quantity);

void test_add();

/*
Update a product's price or quantity
post: return 0 if the product was updated
	  return 1 if the new price/quantity is not valid
	  return 2 if the product with the given id does not exist
*/
int update_product(Inventory* inv, int id, float new_price, int new_quantity);

void test_update();

/*
Delete the product with an given id
post: return 0 if the product was deleted
	  return 1 if there id no product with the given id
*/
int delete_product(Inventory* inv, int id);

void test_delete();

/*
Compare two product's prices
return 0 if the first price is less or equal
return 1 otherwise
*/
int cmp_price1(Product* p1, Product* p2);

/*
Compare two product's prices
return 0 if the first price is greater or equal
return 1 otherwise
*/
int cmp_price2(Product* p1, Product* p2);

/*
Compare two product's quantities
return 0 if the first quantity is less or equal
return 1 otherwise
*/
int cmp_quantity1(Product* p1, Product* p2);

/*
Compare two product's quantities
return 0 if the first quantity is greater or equal
return 1 otherwise
*/
int cmp_quantity1(Product* p1, Product* p2);

/*
Sort the products by e given criteria
post: return a new list, sorted
criteria = 1 - ascending by price
		   2 - descending by price
		   3 - ascending by quantity
		   4 - descending by quantity
*/
List* sort_products(Inventory* inv, int criteria);

void test_sort();

/*
Filter the product by producer
return a list with products that have p.producer = producer
*/
List* filter_producer(Inventory* inv, char* producer);

void test_filter_producer();

/*
Filter the product by price
return a list with products that have p.price in [min_price, max_price]
*/
List* filter_price(Inventory* inv, float min_price, float max_price);

void test_filter_price();

/*
Filter the product by quantity
return a list with products that have p.quantity >= quantity
*/
List* filter_quantity(Inventory* inv, int quantity);

void test_filter_quantity();


/* 
Undo the last add/update/delete
post: list is its previous form before the last add/update/delete
return 0 if undo was done
	   1 if undo cannot be done*/
int undo(Inventory* inv);

void test_undo();

#endif
