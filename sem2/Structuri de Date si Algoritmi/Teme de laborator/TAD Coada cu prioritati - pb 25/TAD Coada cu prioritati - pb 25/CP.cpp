
#include "CP.h"
#include <exception>
#include <stdio.h>

using namespace std;

/*
	caz fav = caz mediu = caz defav = theta(1)
		
*/
int CP::aloca() {
	int i = prim_liber;
	prim_liber = urm[prim_liber];
	return i;
}

/*
	caz fav = caz mediu = caz defav = theta(1)
*/
void CP::dealoca(int i) {
	urm[i] = prim_liber;
	prim_liber = i;
}

/*
	caz fav = caz mediu = caz defav = theta(cp)
*/
void CP::init_spatiu_liber() {
	e = new Element[sizeof(Element) * cp];
	urm = new int[sizeof(int) * cp];
	for (int i = 0; i <= cp - 2; i++) {
		urm[i] = i + 1;
	}
	urm[cp - 1] = -1;
	prim_liber = 0;
}

/*
	caz fav = caz mediu = caz defav = theta(cp)
*/
void CP::redim() {
	int cp_noua = cp * 2;
	Element* e_nou = new Element[sizeof(Element) * cp_noua];
	int* urm_nou = new int[sizeof(int) * cp_noua];
	for (int i = 0; i < cp; i++) {
		*(e_nou + i) = e[i];
		*(urm_nou + i) = urm[i];
	}

	cp = cp_noua;
	delete[] e;
	e = e_nou;
	delete[] urm;
	urm = urm_nou;
}

/*
	caz fav = caz mediu = caz defav = theta(1) amortizata
*/
int CP::creeaza_nod(Element el) {
	if (prim_liber == -1) {
		redim();
		for (int i = cp / 2; i <= cp - 2; i++) {
			urm[i] = i + 1;
		}
		urm[cp - 1] = -1;
		prim_liber = cp / 2;
	}
	int i = aloca();
	e[i] = el;
	urm[i] = -1;
	return i;
}

/*
	caz fav = caz mediu = caz defav = theta(1)
*/
CP::CP(Relatie r) {
	cp = 2;
	rel = r;
	prim = -1;
	init_spatiu_liber();
}

/*
	caz fav: elementul trebuie adaugat inainte primului => theta(1)
	caz mediu: inserare intre 2 elemente - corpul lui while poate fi executat de 1, 2, .., n-1 ori => theta(n)
	caz defav: adaugam dupa ultimul element => theta(n)
	total: O(n)
*/
void CP::adauga(TElem el, TPrioritate p) {
	int nou = creeaza_nod(Element(el, p));
	if (prim == -1) { // daca avem o coada e vida
		prim = nou;
	}
	else if (rel(p, e[prim].second)) { // daca elementul de adaugat are prioritatea cea mai mare
		urm[nou] = prim;
		prim = nou;
	}
	else { // cautam sa inseram intre doua elemente
		int poz1 = prim;
		int poz2 = urm[poz1];
		while (poz2 != -1) {
			if (rel(e[poz1].second, p) && rel(p, e[poz2].second)) {
				urm[poz1] = nou;
				urm[nou] = poz2;
				return;
			}
			poz1 = poz2;
			poz2 = urm[poz2];
		}
		// daca am ajuns aici, inseamna ca nu am gasit doua elemente intre care sa adaugam
		// deci adaugarea se face la sfarsit, in poz1 fiind pozitia ultimului element din coada
		urm[poz1] = nou;
	}
}

/*
	caz fav = caz mediu = caz defav = theta(1)
*/
Element CP::element() const {
	if (prim == -1) {
		throw exception("exceptie");
	}
	return e[prim];
}

/*
	caz fav = caz mediu = caz defav = theta(1)
*/
Element CP::sterge() {
	if (prim == -1) {
		throw exception("exceptie");
	}
	Element rez = e[prim];
	int p = prim;
	prim = urm[prim];
	dealoca(p);
	return rez;
}

/*
	caz fav = caz mediu = caz defav = theta(1)
*/
bool CP::vida() const {
	return prim == -1;
}

/*
	caz fav = caz mediu = caz defav = theta(n)
	pre: c - coada cu prioritati, elem - TElem, p_noua - TPrioritate
	post: c' - coada cu prioritatea actualizata, p_veche este vechea prioritate a elementului elem sau -1
	Subaloritm schimba_prioritate(c, elem, p_noua)
		i <- c.prim
		p_veche <- -1
		gasit <- fals
		cat timp i <> -1 && gasit = fals executa
			daca c.e[i].first = elem atunci
				gasit <- adevarat
				p_veche <- c.e[i].second
				c.e[i].second <- p_noua
			sf daca
			i <- c.urm[i]
		sf cat timp

		daca gasit = fals atunci
			schimba_prioritate <- -1
		altfel
			creeaz_cp(aux)
			cat timp vida(c) = fals executa
				x <- sterge(c) // x de tip Element
				adauga(aux, x.el, x.p)
			sf cat timp
			cat timp vida(aux) = fals executa
				<el, p> x <- sterge(aux)
				adauga(c, x.el, x.p)
			sf cat timp
			schimba_prioritate <- p_veche
		sf daca
	sf subalgoritm
*/
TPrioritate CP::schimba_prioritate(TElem elem, TPrioritate p_noua) {
	int i = prim;
	int p_veche;
	bool gasit = false;
	while (i != -1 && gasit == false) {
		if (e[i].first == elem) {
			p_veche = e[i].second;
			e[i].second = p_noua;
			gasit = true;
		}
		i = urm[i];
	}
	if (gasit == false) {
		return -1;
	}
	else {
		CP aux(this->rel);
		while (!this->vida()) {
			Element el = this->sterge();
			aux.adauga(el.first, el.second);
		}
		while (!aux.vida()) {
			Element el = aux.sterge();
			this->adauga(el.first, el.second);
		}
		return p_veche;
	}

}

/*
	caz fav = caz mediu = caz defav = theta(1)
*/
CP::~CP() {
	delete[] e;
	delete[] urm;
};

