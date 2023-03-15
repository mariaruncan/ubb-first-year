#pragma once
#include <string>
using std::string;

class Melodie {
private:
	int id;
	string titlu;
	string artist;
	int rank;
public:
	Melodie(int id, string titlu, string artist, int rank) :id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank }{
	}
	/*
	getter pentru id
	*/
	int get_id() const {
		return id;
	}

	/*
	getter pentru titlu
	*/
	string get_titlu() const {
		return titlu;
	}

	/*
	getter pentru artist
	*/
	string get_artist() const {
		return artist;
	}
	
	/*
	getter pentru rank
	*/
	int get_rank() const {
		return rank;
	}
};

