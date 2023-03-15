#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


Nod::Nod(TElem e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
TElem Nod::element() {
	return this->e;
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
PNod Nod::urmator() {
	return this->urm;
}



MD::MD() {
	this->prim = nullptr;
	this->ultim = nullptr;
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
void MD::adauga(TCheie c, TValoare v) {

	pair <TCheie, TValoare> elem(c, v);

	PNod nou = new Nod(elem, nullptr);
	
	// daca lista este nevida, se adauga dupa ultimul element
	if (this->ultim != nullptr)
		this->ultim->urm = nou;

	// daca lista este vida, elementul de adaugat va fi primul din lista
	else
		this->prim = nou;

	// se actualizeaza ultim
	this->ultim = nou;
}

/*
	caz favorabil: elementul de sters se afla la inceput => theta(1)
	caz defavorabil: elementul de sters este ultimul sau nu se afla in lista => theta(n)
	caz mediu: elementul de sters se afla pe poz 1, 2,..,n => theta(n) ((1+2+...+n)/n)
	total: O(n)
*/
bool MD::sterge(TCheie c, TValoare v) {

	pair <TCheie, TValoare> elem(c, v);

	// daca lista este vida, nu avem ce sterge
	if (prim == nullptr)
		return false;

	// daca elementul de sters este chiar primul, prim se actualizeaza, iar spatiul ocupat de elem de sters se dealoca
	if (prim->e == elem) {
		PNod p = prim;
		prim = p->urm;
		delete p;
		// daca inainte de stergere exista un sigur element in lista, lista este acum vida si trebuie actualizat ultim
		if (prim == nullptr) {
			ultim = nullptr;
		}
		return true;
	}

	else {
		// iteram toata lista pentru a gasi elementul de sters
		IteratorMD i = IteratorMD(*this);

		PNod p = prim; // in p vom retine adresa elementului dinaintea celui de sters

		while (i.valid()) {
			if (i.element() == elem) {
				break;
			}
			p = i.curent;
			i.urmator();
		}

		// i.curent este nullptr sau adresa elementului de sters

		// daca am iterat toata lista si nu am gasit elementul, returnam fals
		if (i.valid() == false) {
			return false;
		}
		// daca am ajuns pana aici, inseamna ca p precede elementul de sters
		
		// daca elementul de sters este ultimul, ultim este actualizat
		if (i.curent == ultim) {
			ultim = p;
			p->urm = nullptr;
		}
		// daca elementul de sters nu este ultimul, se sterge pur si simplu
		else {
			p->urm = i.curent->urm;
		}
		// dealocam spatiul
		delete i.curent;

		return true;
	}
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
vector<TValoare> MD::cauta(TCheie c) const {

	vector <TValoare> rez;
	IteratorMD i = IteratorMD(*this);
	
	// iteram peste lista si in caz ca gasim elemente cu cheia c, le adaugam valorile in vectorul rez
	while (i.valid()) {
		TElem el = i.element();
		if (el.first == c) {
			rez.push_back(el.second);
		}
		i.urmator();
	}

	return rez;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
int MD::dim() const {
	
	int dim = 0;
	IteratorMD i = IteratorMD(*this);

	while (i.valid()) {
		dim++;
		i.urmator();
	}

	return dim;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
bool MD::vid() const {
	return prim == nullptr && ultim == nullptr;
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(1)
*/
IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

/*
	caz favorabile = caz defavorabil = caz mediu = theta(n)
*/
MD::~MD() {
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}
