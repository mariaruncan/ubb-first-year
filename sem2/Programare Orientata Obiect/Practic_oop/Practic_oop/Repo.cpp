#include "Repo.h"

void Repo::read() {
	ifstream fin(filename);
	while (true) {
		int id, rank;
		string titlu, artist;
		fin >> id;
		if (fin.eof()) {
			break;
		}
		fin >> titlu >> artist >> rank;
		all.push_back(Melodie{ id,titlu,artist,rank });
	}
	fin.close();
}

void Repo::write() {
	ofstream fout(filename);
	for (const auto& el : all) {
		fout << el.get_id() << endl;
		fout << el.get_titlu() << endl;
		fout << el.get_artist() << endl;
		fout << el.get_rank() << endl;
	}
	fout.close();
}

const vector<Melodie>& Repo::get_all() {
	return all;
}

void Repo::sterge(int id) {
	all.erase(std::find_if(all.begin(), all.end(), [id](const Melodie& m) {return m.get_id() == id; }));
	write();
}


const Melodie& Repo::find(int id) {
	for (const auto& el : all) {
		if (el.get_id() == id) {
			return el;
		}
	}
}

void Repo::update(Melodie m) {
	for (int i = 0; i < all.size(); i++) {
		if (all[i].get_id() == m.get_id()) {
			all[i] = m;
			write();
			return;
		}
	}
}
