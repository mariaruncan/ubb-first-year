#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>
#include <queue>

using namespace std;

// caz fav = caz mediu = caz defav = theta(1)
Nod::Nod(TElem e, PNod st, PNod dr) {
	this->e = e;
	this->st = st;
	this->dr = dr;
}

// caz fav = caz mediu = caz defav = theta(1)
TElem Nod::element() {
	return e;
}

// caz fav = caz mediu = caz defav = theta(1)
PNod Nod::stanga() {
	return st;
}

// caz fav = caz mediu = caz defav = theta(1)
PNod Nod::dreapta() {
	return dr;
}


//o posibila relatie
// caz fav = caz mediu = caz defav = theta(1)
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

// caz fav: subarborele in care vrem sa cautam este vid => theta(1)
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
bool Multime::cauta_iterativ(PNod rad, TElem elem) const {
	while (rad != nullptr) {
		if (elem == rad->e) {
			return true;
		}
		else if (rel(elem, rad->e)) {
			rad = rad->st;
		}
		else {
			rad = rad->dr;
		}
	}
	return false;
}

// caz fav: subarborele in care vrem sa stergem este vid => theta(1)
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
PNod Multime::sterge_semi_rec(PNod p, TElem elem) {
	if(p == nullptr) {
		return p;
	}
	
	PNod curent = p;
	PNod precedent = nullptr;

	while (curent != nullptr && curent->e != elem) {
		precedent = curent;
		if (rel(elem, curent->e)) {
			curent = curent->st;
		}
		else {
			curent = curent->dr;
		}
	}

	if (curent == nullptr) { // nodul ce trebuie sters nu exista
		return p;
	}

	if (curent->st != nullptr && curent->dr != nullptr) { // nodul de sters are 2 fii
		PNod aux = minim(curent->dr);
		curent->e = aux->e;
		curent->dr = sterge_semi_rec(curent->dr, curent->e);
	}
	else { // nodul de sters are cel mult un fiu
		PNod fiu;
		if (curent->st == nullptr) {
			fiu = curent->dr;
		}
		else{
			fiu = curent->st;
		}

		if (precedent == nullptr) { // nodul de sters este chiar rad
			return fiu;
		}

		if (precedent->st == curent) {
			precedent->st = fiu;
		}
		else {
			precedent->dr = fiu;
		}
		delete curent;
		curent = nullptr;
	}
	
	return p;
}

// caz fav: subarborele in care vrem sa gasim  inimul este vid => theta(1)
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
PNod Multime::minim(PNod p) {
	while (p->st != nullptr) {
		p = p->st;
	}
	return p;
}

// caz fav = caz mediu = caz defav = theta(1)
Multime::Multime() {
	this->n = 0;
	this->rad = nullptr;
}

// caz fav: subarborele in care vrem sa adaugam este vid => theta(1)
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
bool Multime::adauga(TElem elem) {
	PNod nou = new Nod(elem, nullptr, nullptr);
	if (rad == nullptr) {
		rad = nou;
		n++;
		return true;
	}
	else {
		PNod curent = rad;
		PNod parinte = nullptr;

		while (1) {
			parinte = curent;

			if (elem == parinte->e) {
				delete nou;
				return false;
			}

			if (rel(elem, parinte->e)) { // incercam adaugarea in stanga
				curent = curent->st;

				if (curent == nullptr) {
					parinte->st = nou;
					n++;
					return true;
				}
			}
			else { // incercam adaugarea in dreapta
				curent = curent->dr;

				if (curent == nullptr) {
					parinte->dr = nou;
					n++;
					return true;
				}
			}
		}
	}

}

// caz fav: subarborele in care vrem sa stergem este vid => theta(1)
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
bool Multime::sterge(TElem elem) {
	if (cauta(elem)) {
		rad = sterge_semi_rec(rad, elem);
		n--;
		return true;
	}
	return false;
}

// caz fav: subarborele in care vrem sa stergem este vid => theta(1)
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
bool Multime::cauta(TElem elem) const {
	return cauta_iterativ(rad, elem);
}

// caz fav = caz mediu = caz defav = theta(1)
int Multime::dim() const {
	return n;
}

// caz fav = caz mediu = caz defav = theta(1)
bool Multime::vida() const {
	return rad == nullptr;
}

// caz fav: arbore vid
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

// caz fav = caz mediu = caz defav = theta(n)
Multime::~Multime() {
	// parcurgem pe nivele
	queue<PNod> q;
	if (rad) {
		q.push(rad);
	}
	while (!q.empty()) {
		PNod p = q.front();
		q.pop();
		if (p->st != nullptr) {
			q.push(p->st);
		}
		if (p->dr != nullptr) {
			q.push(p->dr);
		}
		delete p;
	}
}

/*
	caz fav: a si b sunt arbori echilibrati => theta(n * (log2 n +log2 m)), unde n = dim(a), m = dim(b)
	caz mediu: a este ech, b degenerat, sau invers => theta(n * (log2 n + m)) sau theta(n * (n + log2 m)) , unde n = dim(a), m = dim(b)
	caz defav: a si b sunt arbori degenerati => theta(n * (n + m)), unde n = dim(a), m = dim(b)
	pre: a, b - Multime
	post: a' - Multime, a' reprezinta intersectia dintre a si b

	Subalgoritm intersectie(Multime a, Multime b)
		@ aloca elem
		creeaza(a, it)
		pentru i<-0,dim(a) executa
			elem[i] = element(it)
			urmator(it)
		sf pentru

		pentru i<-0, dim(a) executa
			daca cauta(b, elem[i]) = fals atunci
				sterge(a, elem[i])
			sf daca
		sf pentru
		@ dealoca elem
	sf subalgortim
*/
void Multime::intersectie(const Multime& b) {
	TElem* elem = new TElem[dim()];
	IteratorMultime it = iterator();
	for (int i = 0; i < dim(); i++) {
		elem[i] = it.element();
		it.urmator();
	}
	for (int i = 0; i < dim(); i++) {
		if (b.cauta(elem[i]) == false) {
			sterge(elem[i]);
		}
	}

	delete[] elem;
}


