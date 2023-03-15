#include "Colectie.h"
#include "IteratorColectie.h"


using namespace std;

// caz fav = caz mediu = caz defav = theta(1)
int hashCode(TElem e) {
	// avem elemente intregi ai avem nevoie de chei naturale
	return abs(e);
}

// caz fav = caz mediu = caz defav = theta(1)
int Colectie::d(TElem e, int i) const{
	return (int)(hashCode(e) % m + 0.5 * i + 0.5 * i * i) % m;
}

// caz fav = caz mediu = caz defav = theta(m)
Colectie::Colectie() {
	m = MAX;
	e = new Pereche[m];
	for (int i = 0; i < m; i++) {
		e[i] = make_pair(NIL, 0);
	}
}

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
void Colectie::adauga(TElem elem) {
	int i = 0;
	bool gasit = false;
	do {
		int j = d(elem, i);
		if (e[j].first == NIL || e[j].first == STERS) {
			e[j] = make_pair(elem, 1);
			gasit = true;
		}
		else if (e[j].first == elem) {
			e[j].second++;
			gasit = true;
		}
		else {
			i++;
		}
	} while (i < m && !gasit);
	if (i == m)
		throw exception();
}

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
bool Colectie::sterge(TElem elem) {
	for (int i = 0; i < m; i++) {
		int j = d(elem, i);
		if (e[j].first == elem) {
			if (e[j].second == 1) {
				e[j].first = STERS;
			}
			else {
				e[j].second--;
			}
			return true;
		}
	}
	return false;
}

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
bool Colectie::cauta(TElem elem) const {
	for(int i = 0; i < m; i++) {
		int j = d(elem, i);
		if (e[j].first == elem) {
			return true;
		}
		else if (e[j].first == NIL) {
			return false;
		}
	}
	return false;
}

// caz fav = caz mediu = theta(1)
// caz defav = theta(m)
// total = O(m)
int Colectie::nrAparitii(TElem elem) const {
	for (int i = 0; i < m; i++) {
		int j = d(elem, i);
		if (e[j].first == elem) {
			return e[j].second;
		}
	}
	return 0;
}

// caz fav = caz mediu = caz defav = theta(m)
int Colectie::dim() const {
	int s = 0;
	for (int i = 0; i < m; i++) {
		if (e[i].first != NIL && e[i].first != STERS) {
			s = s + e[i].second;
		}
	}
	return s;
}


bool Colectie::vida() const {
	for (int i = 0; i < m; i++) {
		if (e[i].first != NIL && e[i].first != STERS) {
			return false;
		}
	}
	return true;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

/*
	caz fav = caz mediu = theta(m)
	caz defav = theta(m^2)
	total = O(m^2)
	pre: a, b - Colectie
	 post: a' =  a\b

	subalgoritm intersectie(Colectie a, Colectie b)
		pentru i <- 0, m-1 executa
			elem <- a.e[i].val
			diff <- b.nrAparitii(el) - a.e[i].fr
			daca diff < 0 atunci
				pentru j <- 0, diff + 1, -1 executa
					a.sterge(el)
				sf pentru
			sf daca
		sf pentru
	sf subalgoritm

*/
void Colectie::intersectie(const Colectie& b) {
	for (int i = 0; i < m; i++) {
		TElem el = e[i].first; // e[i] - elementul curent de cautat
		int diff = b.nrAparitii(el) - e[i].second;
		if (diff >= 0) { // daca avem mai multe sau la fel de multe elemente x in multimea b, nu facem nimic
			continue;
		}
		else { // in acest caz inseamna ca b are mai putine elem decat multimea this, mai exact cu -diff mai putine, deci stergem din this
			for (int j = 0; j > diff; j--) {
				sterge(el);
			}
		}
	}
}


Colectie::~Colectie() {
	delete[] e;
}


