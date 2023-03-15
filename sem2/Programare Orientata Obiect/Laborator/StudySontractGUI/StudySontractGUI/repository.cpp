#include "repository.h"
#include <assert.h>

void SubjectRepo::add_subject(const Subject& sub) {
	if (std::find_if(elems.begin(), elems.end(), [sub](const Subject& s) {return s.get_name() == sub.get_name(); }) != elems.end()) {
		throw RepoException("Subject already exists!\n");
	}
	else {
		elems.push_back(sub);
	}
}

const vector<Subject>& SubjectRepo::get_all() noexcept {
	return elems;
}

void SubjectRepo::delete_subject(const string& name) {
	vector<Subject>::iterator it = elems.begin();
	for (const Subject& s : elems) {
		if (s.get_name() == name) {
			elems.erase(it);
			return;
		}
		it++;
	}
	throw RepoException("Subject does not exist!\n");
}

const Subject& SubjectRepo::find_subject(const string& name) {
	vector<Subject>::iterator it = std::find_if(elems.begin(), elems.end(), [name](const Subject& s) {return s.get_name() == name; });
	if (it != elems.end()) {
		return *(it);
	}
	throw RepoException("Subject does not exist!\n");
}

void SubjectRepo::update_subject(const Subject& sub) {
	for (Subject& s : elems) {
		if (s.get_name() == sub.get_name()) {
			s = sub;
			return;
		}
	}
	throw RepoException("Subject does not exist!\n");
}
