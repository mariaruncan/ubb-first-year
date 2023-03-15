#pragma once
#include "Melodie.h"
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;
#include <algorithm>

class Repo {
private:
	string filename;
	vector<Melodie> all;

	void read();
	void write();
public:
	/*
	costructor pentru un obiecte de tip Repo
	pre: filename - string - numele fisierului in care se vor siti/scrie datele
	*/
	Repo(string f) :filename{ f } {
		read();
	}

	/*
	functia returneaza o lista cu toate melodiile 
	post: se returneaza un vector de melodii
	*/
	const vector<Melodie>& get_all();

	/*
	functia sterge melodia cu id-ul dat
	pre: id - int - id-ul melodiei
	post: in lista nu mai exista melodia cu id-ul id
	*/
	void sterge(int id);

	/*
	functia cauta melodia cu id-ul dat
	pre: id - int - id-ul melodiei
	post: se returneaza melodia cu id-ul id
	*/
	const Melodie& find(int id);

	/*
	functia actualizeaza o melodie
	pre: m - Melodie - contine noile atribute ale melodiei
	post: melodia care are acelasi id cu m este acum actualizata
	*/
	void update(Melodie m);
};

