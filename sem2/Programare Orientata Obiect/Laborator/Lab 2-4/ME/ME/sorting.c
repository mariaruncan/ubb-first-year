#include "sorting.h"
#include <stdio.h>

void sort(List* l, CmpFunction cmpF) {
	int i, j;
	for (i = 0; i < nr_elems(l); i++) {
		for (j = i + 1; j < nr_elems(l); j++) {
			Product* p1 = get_elem(l, i);
			Product* p2 = get_elem(l, j);
			if (cmpF(p1, p2) != 0) {
				set_elem(l, i, p2);
				set_elem(l, j, p1);
			}
		}
	}
}
