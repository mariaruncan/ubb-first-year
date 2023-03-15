#include "contract.h"
using namespace std;

void Contract::clear_contract() {
	all.clear();
	notify();
}

void Contract::add_contract(const string& name) {
	if (name.empty()) {
		throw ContractException("Name can not be empty!\n");
	}
	const vector<Subject>& elems = repo.get_all();
	auto it = std::find_if(elems.begin(), elems.end(), [name](const Subject& s) {return s.get_name() == name; });
	if (it == elems.end())
		throw RepoException("Subject does not exist!\n");
	else {
		if (all.end() != find_if(all.begin(), all.end(), [name](const Subject& s) {return s.get_name() == name; }))
			throw ContractException("Subject is already in contract!\n");
		all.push_back(*it);
		notify();
	}
}

void Contract::generate_contract(int nr) {
	clear_contract();
	vector<Subject> aux = repo.get_all();
	if (nr > (int)aux.size()) {
		nr = aux.size();
	}
	for (int i = 0; i < nr; i++) {
		mt19937 mt{ std::random_device{}() };
		uniform_int_distribution <> const dist(0, (int)aux.size() - 1);
		int const rndNr = dist (mt);;// numar aleator intre [0,size-1]
		const auto seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
		shuffle(aux.begin(), aux.end(), default_random_engine(seed));
		all.push_back(aux[rndNr]);
		aux.erase(aux.begin() + rndNr);
	}
	notify();
}

void Contract::export_contract(const string& file_name) {
	if (file_name.empty()) {
		throw ContractException("File name can not be empty!\n");
	}
	string file = file_name + ".csv";
	ofstream fout(file);
	fout << "Name,Hours,Type,Teacher\n";
	for (const Subject& s : all) {
		fout << s.get_name() << "," << s.get_hours() << "," << s.get_type() << "," << s.get_teacher() << "\n";
	}
	fout.close();
}

void Contract::delete_contract(const string& name) {
	auto it = all.begin();
	for (const Subject& s : all) {
		if (s.get_name() == name) {
			all.erase(it);
			notify();
			return;
		}
		it++;
	}
}

void Contract::update_contract(const Subject& sub) {
	for (Subject& s : all) {
		if (s.get_name() == sub.get_name()) {
			s = sub;
			return;
		}
	}
	notify();
}

const vector<Subject>& Contract::get_subjects() noexcept{
	return all;
}
