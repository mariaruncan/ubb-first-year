#pragma once
#include <vector>
#include <utility>

using namespace std;

typedef int TElem;
typedef int TPrioritate;

typedef std::pair<TElem, TPrioritate> Element;

typedef bool (*Relatie)(TPrioritate p1, TPrioritate p2);

class CP {

private:
	int cp;
	int prim, prim_liber;
	Element* e; //vectorul de elemente
	int* urm; //vectorul de legaturi (valori din [-1..cp-1])
	Relatie rel;

	// returneaza prima pozitie libera
	int aloca();

	// dealoca nodul de pe pozitia i
	void dealoca(int i);

	// initializeaza cei doi vectori
	void init_spatiu_liber();

	// redimensioneaza cei doi vectori si actualizeaza primul_liber
	void redim();

	// returneaza pozitia unui nou nod
	int creeaza_nod(Element el);

public:
	//constructorul implicit
	CP(Relatie r);

	//adauga un element in CP
	void adauga(TElem e, TPrioritate p);

	//acceseaza elementul cel mai prioritar in raport cu relatia de ordine
	//arunca exceptie daca CP e vida
	Element element()  const;

	//sterge elementul cel mai prioritar si il returneaza
	//arunca exceptie daca CP e vida
	Element sterge();

	//verifica daca CP e vida;
	bool vida() const;

	// schimba prioritatea unui element
	TPrioritate schimba_prioritate(TElem elem, TPrioritate p_noua);

	// destructorul cozii
	~CP();

};
