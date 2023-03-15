#include "IteratorColectie.h"
#include "Colectie.h"

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	// initializeaza iteratorul pe primul element din colectie
	this->curent = 0;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
void IteratorColectie::prim() {
	// seteaza iteratorul pe primul element din colectie
	this->curent = 0;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
void IteratorColectie::urmator() {
	// iteratorul creste pentru a arata spre urmatorul element al colectie
	if (this->curent >= this->col.dim())
		throw;
	(this->curent)++;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
bool IteratorColectie::valid() const {
	// verifica daca iteratorul arata spre un element al colectie
	return this->curent < this->col.dim();
}


/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
TElem IteratorColectie::element() const {
	// returneaza elementul curent
	if (this->curent >= this->col.dim())
		throw;
	int poz = col.P[curent];
	return col.D[poz];
}
