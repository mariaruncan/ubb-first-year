#ifndef PRODUCT_H_
#define PRODUCT_H_

typedef struct {
	int id;
	char* type;
	char* producer;
	char* model;
	float price;
	int quantity;
}Product;

/*
Create a new product
*/
Product* create_product(int id, char* type, char* producer, char* model, float price, int quantity);

/*
Dealocate memory occupied by product
*/
void destroy_product(Product* p);

/*
Create a copy for the product
Deep copy - copy all the sub-parts
*/
Product* copy_product(Product* p);

/*
Validate product
Returns 1 if product is invalid, otherwise returns 0
*/
int validate(Product* p);

void test_create_destroy();

void test_validate();

/*
Getter for id of a product
*/
int get_id(Product* p);

/*
Getter for type of a product
*/
char* get_type(Product* p);

/*
Getter for producer of a product
*/
char* get_producer(Product* p);

/*
Getter for model of a product
*/
char* get_model(Product* p);

/*
Getter for price of a product
*/
float get_price(Product* p);

/*
Getter for quantity of a product
*/
int get_quantity(Product* p);

#endif