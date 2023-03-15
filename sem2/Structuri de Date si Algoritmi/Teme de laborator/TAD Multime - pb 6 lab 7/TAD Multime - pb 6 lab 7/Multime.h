#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;
class Nod;

typedef Nod* PNod;

class Nod {
	friend class Multime;

private:
	TElem e;
	PNod st, dr;

public:
	Nod(TElem e, PNod st, PNod dr);
	TElem element();
	PNod stanga();
	PNod dreapta();

};

class Multime {

	friend class IteratorMultime;

private:
	PNod rad; // radacina arborelui
	int n;

	bool cauta_iterativ(PNod rad, TElem elem) const;
	PNod sterge_semi_rec(PNod p, TElem elem);
	PNod minim(PNod p);

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();

	void intersectie(const Multime& b);

};

