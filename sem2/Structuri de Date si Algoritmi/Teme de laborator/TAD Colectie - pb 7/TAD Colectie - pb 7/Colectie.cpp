#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
Colectie::Colectie() {

	// initializam capacitatile
	this->cap_D = 1;
	this->cap_P = 1;

	// alocam spatiu de memorie pentru cei doi vectori
	this->D = new TElem[cap_D];
	this->P = new int[cap_P];

	// initializam numarul de elemente din cei doi vectori
	this->dim_D = 0;
	this->dim_P = 0;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
void Colectie::redim() {

	// daca este cazul, alocam spatiu de memorie suplimentar pentru D
	if (dim_D == cap_D) {
		TElem* D_nou = new TElem[2 * cap_D];
		// copiem valorile din vechea locatie
		for (int i = 0; i < dim_D; i++)
			D_nou[i] = D[i];
		// dublam capacitatea
		cap_D = 2 * cap_D;
		// eliberam vechea zona
		delete[] D;
		// vectorul indica spre o noua zona
		D = D_nou;
	}
	
	// daca este cazul, alocam spatiu de memorie suplimentar pentru P
	if (dim_P == cap_P) {
		int* P_nou = new int[2 * cap_P];
		// copiem valorile din vechea locatie
		for (int i = 0; i < dim_P; i++)
			P_nou[i] = P[i];
		// dublam capacitatea
		cap_P = 2 * cap_P;
		// eliberam vechea zona
		delete[] P;
		// vectorul indica spre o noua zona
		P = P_nou;
	}
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
void Colectie::adauga(TElem elem) {
	if (dim_D == cap_D || dim_P == cap_P)
		redim();

	// in caz ca elem exista in vectorul D, ii cautam pozitia
	int poz = -1;
	for (int i = 0; i < dim_D && poz == -1; i++)
		if (D[i] == elem) {
			poz = i;
		}

	// daca elem este in vectorul D, ii adaugam pozitia la sfarsitul vectorului P
	if (poz != -1) {
		P[dim_P] = poz;
		dim_P++;
	}
	// daca elem nu este in vectorul D, il adaugam la sfarsitul acestuia si ii punem pozitia la sfarsitul lui P
	else {
		poz = dim_D;
		D[poz] = elem;
		dim_D++;

		P[dim_P] = poz;
		dim_P++;
	}

}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
bool Colectie::sterge(TElem elem) {
	int ap = nrAparitii(elem);
	if (ap == 0)
		return false;
	else {

		int j = 0;
		IteratorColectie i = IteratorColectie(*this);
		while (i.valid()) {
			if (i.element() == elem) {
				while (j < dim_P - 1) {
					P[j] = P[j + 1];
					j++;
				}
				dim_P--;
				P[dim_P] = 0;
				break;
			}
			i.urmator();
			j++;
		}
	}

	if (ap == 1) {
		int poz = -1;
		for (int i = 0; i < dim_D; i++) {
			if (D[i] == elem) {
				poz = i;
				while (i < dim_D - 1) {
					D[i] = D[i + 1];
					i++;
				}
				dim_D--;
				D[dim_D] = 0;
				break;
			}
		}
		for (int i = 0; i < dim_P; i++) 
			if (P[i] > poz)
				P[i] = P[i] - 1;

	}
	return true;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
bool Colectie::cauta(TElem elem) const {
	IteratorColectie i = IteratorColectie(*this);
	while (i.valid()) {
		if (i.element() == elem) {
			return true;
		}
		i.urmator();
	}
	return false;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
int Colectie::nrAparitii(TElem elem) const {
	IteratorColectie i = IteratorColectie(*this);
	int nr_aparitii = 0;
	while (i.valid()) {
		if (i.element() == elem) {
			nr_aparitii++;
		}
		i.urmator();
	}
	return nr_aparitii;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
int Colectie::dim() const {
	return this->dim_P;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
bool Colectie::vida() const {
	if (this->dim_P == 0 && this->dim_D == 0)
		return true;
	return false;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	// eliberam zona de memorie alocata colectiei
	delete[] this->D;
	delete[] this->P;
}


