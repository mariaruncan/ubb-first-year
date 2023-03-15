#ifndef SORTING_H_
#define SORTING_H_
#include "list.h"

/*
Compare function
Return 0 if they are equal and 1 otherwise
*/
typedef int(*CmpFunction)(Product* p1, Product* p2);

/*
Sort in place
cmpF - function after which the sorting is done
*/
void sort(List* l, CmpFunction cmpF);

#endif