#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

// caz fav: arbore vid
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	PNod curent = mult.rad;
	while (curent != nullptr) {
		q.push(curent);
		curent = curent->stanga();
	}
}

// caz fav = caz mediu = caz defav = theta(1)
TElem IteratorMultime::element() const {
	if (!valid()) {
		throw std::exception();
	}
	return q.top()->element();
}

// caz fav = caz mediu = caz defav = theta(1)
bool IteratorMultime::valid() const {
	return !(q.empty());
}

// caz fav: arbore vid
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
void IteratorMultime::urmator() {
	if (!valid()) {
		throw std::exception();
	}
	PNod curent = q.top()->dreapta();
	q.pop();
	while (curent != nullptr) {
		q.push(curent);
		curent = curent->stanga();
	}
}

// caz fav: arbore vid
// caz mediu: arbore echilibrat => theta(log2 n)
// caz defav: arbore degenerat => theta(n)
// total: O(n)
void IteratorMultime::prim() {
	while (!q.empty()) {
		q.pop();
	}
	PNod curent = mult.rad;
	while (curent != nullptr) {
		q.push(curent);
		curent = curent->stanga();
	}
}

