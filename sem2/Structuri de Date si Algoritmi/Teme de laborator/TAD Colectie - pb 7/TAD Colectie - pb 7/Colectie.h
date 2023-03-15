#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	// capacitatea vectorului de elemente distincte
	int cap_D;

	// capacitatea vectorului de pozitii
	int cap_P;

	// dimensiunea vectorului de elemente ditincte
	int dim_D;

	// dimensiunea vectorului de pozitii
	int dim_P;

	// vector de elemente distincte
	TElem* D;

	// vector de pozitii
	int* P;

	// functie pentru alocarea unui spatiu mai mare
	void redim();

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

	// destructorul colectiei
	~Colectie();

};

