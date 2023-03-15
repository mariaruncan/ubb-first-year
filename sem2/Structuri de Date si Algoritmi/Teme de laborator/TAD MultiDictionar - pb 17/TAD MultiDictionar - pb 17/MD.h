#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class Nod;

//se defineste tipul PNod ca fiind adresa unui Nod
typedef Nod *PNod;

class Nod
{

private:

	TElem e;

	PNod urm;

public:

	friend class MD;

	// constructor pentru un nod
	Nod(TElem e, PNod urm);

	// returneaza informatia utila a nodului curent
	TElem element();

	// returneaza un pointer spre nodul urmator
	PNod urmator();
};

class MD
{
	friend class IteratorMD;

private:
	
	// prim este adresa primulul Nod din lista
	PNod prim;

	// ultim este adresa ultimului Nod din lista
	PNod ultim;

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();



};

