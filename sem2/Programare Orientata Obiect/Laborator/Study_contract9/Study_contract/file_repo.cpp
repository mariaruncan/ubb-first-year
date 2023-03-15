#include "file_repo.h"
using std::ifstream;
using std::ofstream;
using std::endl;

void FileRepo::load_from_file() {
	ifstream fin(file_name);
	if (!fin.is_open()) {
		throw RepoException("Error open:" + file_name);
	}
	while (!fin.eof()) {
		string name;
		fin >> name;
		if (fin.eof()) break; //pentru linii goale
		int hours;
		fin >> hours;
		string type;
		fin >> type;
		string teacher;
		fin >> teacher;
		Subject s{ name, hours, type, teacher };
		SubjectRepo::add_subject(s);
	}
	fin.close();
}

void FileRepo::write_to_file() {
	ofstream fout(file_name);
	if (!fout.is_open()) {
		throw RepoException("Error open:" + file_name);
	}
	for (const Subject& s : get_all()) {
		fout << s.get_name() << endl;
		fout << s.get_hours() << endl;
		fout << s.get_type() << endl;
		fout << s.get_teacher() << endl;
	}
	fout.close();
}

void FileRepo::add_subject(const Subject& sub) {
	SubjectRepo::add_subject(sub);
	write_to_file();
}

void FileRepo::delete_subject(const string& name) {
	SubjectRepo::delete_subject(name);
	write_to_file();
}

void FileRepo::update_subject(const Subject& sub) {
	SubjectRepo::update_subject(sub);
	write_to_file();
}
