#include "product.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

Product* create_product(int id, char* type, char* producer, char* model, float price, int quantity) {
	Product* p = (Product*)malloc(sizeof(Product));
	if (p) {
		p->id = id;
		size_t lg = strlen(type) + 1;
		p->type = malloc(lg * sizeof(char));
		if (p->type) {
			strcpy_s(p->type, lg, type);
		}

		lg = strlen(producer) + 1;
		p->producer = malloc(lg * sizeof(char));
		if (p->producer) {
			strcpy_s(p->producer, lg, producer);
		}

		lg = strlen(model) + 1;
		p->model = malloc(lg * sizeof(char));
		if (p->model) {
			strcpy_s(p->model, lg, model);
		}

		p->price = price;
		p->quantity = quantity;
	}
	return p;
}

void destroy_product(Product* p) {
	free(p->type);
	free(p->producer);
	free(p->model);
	free(p);
}

Product* copy_product(Product* p) {
	return create_product(p->id, p->type, p->producer, p->model, p->price, p->quantity);
}

int validate(Product* p) {
	if (strlen(p->type) == 0)
		return 1;
	if (strlen(p->producer) == 0)
		return 1;
	if (strlen(p->model) == 0)
		return 1;
	if (p->price <= 0)
		return 1;
	if (p->quantity < 0)
		return 1;
	return 0;
}

void test_create_destroy() {
	Product* p = create_product(1, "laptop", "asus", "vivobook", 10.1f, 12);
	assert(p->id == 1);
	assert(strcmp(p->type, "laptop") == 0);
	assert(strcmp(p->producer, "asus") == 0);
	assert(strcmp(p->model, "vivobook") == 0);
	assert(fabs(p->price - 10.1) < 0.00001);
	assert(p->quantity == 12);

	destroy_product(p);
}

void test_validate() {
	Product* p;
	p = create_product(1, "a", "b", "c", 1.0f, 2);
	assert(validate(p) == 0);
	destroy_product(p);

	p = create_product(1, "", "b", "c", 1.0f, 2);
	assert(validate(p) == 1);
	destroy_product(p);

	p = create_product(1, "a", "", "c", 1.0f, 2);
	assert(validate(p) == 1);
	destroy_product(p);

	p = create_product(1, "a", "b", "", 1.0f, 2);
	assert(validate(p) == 1);
	destroy_product(p);

	p = create_product(1, "a", "b", "c", -3.9f, 2);
	assert(validate(p) == 1);
	destroy_product(p);

	p = create_product(1, "a", "b", "c", 1.0f, -7);
	assert(validate(p) == 1);
	destroy_product(p);
}

int get_id(Product* p) {
	return p->id;
}

char* get_type(Product* p){
	return p->type;
}

char* get_producer(Product* p){
	return p->producer;
}

char* get_model(Product* p)
{
	return p->model;
}

float get_price(Product* p)
{
	return p->price;
}

int get_quantity(Product* p)
{
	return p->quantity;
}
