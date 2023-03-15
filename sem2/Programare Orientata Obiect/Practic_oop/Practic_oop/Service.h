#pragma once
#include "Repo.h"
#include <algorithm>

class Service {
private:
	Repo& repo;
public:
	/*
	constructor pentru un obiect de tipul Servie
	pre: r - Repo
	*/
	Service(Repo& r) :repo{ r } {
	}

	/*
	"interzicem" copierea obiectelor de tip Service
	prin marcarea constructorului de copiere cu delete
	*/
	Service(const Service& srv) = delete;

	/*
	functia returneaza o lista de melodii sortate dupa rank
	post: lista este sortata descrescator dupa rank
	*/
	vector<Melodie> get_sortate();

	/*
	functia returneaza numarul de melodii care au un rank dat
	pre: r - int - un rank
	post: se returneaza numarul de melodii cu rankul r
	*/
	int nr_rank(int r);

	/*
	functia sterge din lista melodia cu id-ul dat
	pre: id - int - id-ul melodiei de sters
	post: in lista nu mai exista melodia cu id-ul id
	*/
	void sterge_id(int id);

	/*
	functia returneaza numarul de melodii care au un artist dat
	pre: artist - string - artistul
	post: se returneaza numarul de melodii cu artistul artist
	*/
	int nr_artist(string artist);

	/*
	functia returneaza melodia cu un id dat
	pre: id - int - id-ul de cautat
	post: se returneaza melodia cu id-ul id
	*/
	Melodie find_id(int id);

	/*
	fucntia actualizeaza titlul si rankul unei melodii cu id-ul de
	pre: id - int, titlu - stirng, rank - string
	post: melodia cu id ul id are titlul titlu si rank-ul rank
	*/
	void update(int id, string titlu, int rank);

};

