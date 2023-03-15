#include "IteratorMD.h"
#include "MD.h"

using namespace std;

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	this->curent = md.prim;
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
TElem IteratorMD::element() const {
	if (curent == nullptr)
		throw;
	return curent->element();
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
bool IteratorMD::valid() const {
	return curent != nullptr;
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
void IteratorMD::urmator() {
	if (curent == nullptr)
		throw;
	curent = curent->urmator();
}

/*
	caz favorabil = caz defavorabil = caz mediu = theta(1)
*/
void IteratorMD::prim() {
	curent = md.prim;
}


/*
	caz favorabil: k <= 1 - theta(1)
	caz defavorabil: k >= n - theta(n)
	caz mediu: while se poate executa de 1, 2, ..., n ori => theta(n) ((1+2+...+n)/n)
	total: O(n)
	
	pre: k este un numar intreg, md este multidictionar
	post: iteratorul arata spre a k-a pereche din dictionar

	Subalgoritm avanseazaKPasi(k)
		Daca k <= 0 atunci
			@arunca exceptie
		SfDaca
		curent <- [md].prim
		
		Cat timp k > 1 si curent != [0] atunci
			k <- k - 1
			curent <- curent.urmator()
		SfCatTimp

		Daca curent == [0] atunci
			@arunca exceptie
		SfDaca
	SfSubalgoritm
*/
void IteratorMD::avanseazaKPasi(int k) {
	if (k <= 0) {
		throw 0;
	}
	curent = md.prim;
	while (k > 1 && curent != nullptr) {
		curent = curent->urmator();
		k--;
	}
	if (curent == nullptr) {
		throw 0;
	}
}

