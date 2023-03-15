#include "IteratorColectie.h"
#include "Colectie.h"

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
void IteratorColectie::deplasare() {
	while (curent < col.m && col.e[curent].first == NIL) {
		curent++;
	}
	poz = 1;
}

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
	deplasare();
}

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
void IteratorColectie::prim() {
	curent = 0;
	deplasare();
}


// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
void IteratorColectie::urmator() {
	if (col.e[curent].first != NIL && col.e[curent].first != STERS && poz < col.e[curent].second) {
		poz++;
	}
	else {
		curent++;
		deplasare();
	}
}

// caz fav=  caz mediu = caz defav = theta(1)
bool IteratorColectie::valid() const {
	return curent < col.m;
}


// caz fav=  caz mediu = caz defav = theta(1)
TElem IteratorColectie::element() const {
	return col.e[curent].first;
}
