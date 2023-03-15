#pragma once
#include <exception>
#include <iostream>
#include <math.h>
#include <utility>

#define NIL -99999999
#define STERS 99999999
#define MAX 65536 // 2 la a 16-a

using namespace std;

typedef int TElem;

typedef pair<TElem, int> Pereche;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	int m;
	Pereche* e;
	int d(TElem e, int i) const;

public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	void intersectie(const Colectie& b);

	// destructorul colectiei
	~Colectie();

};

