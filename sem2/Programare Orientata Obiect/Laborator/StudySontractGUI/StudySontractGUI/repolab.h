#pragma once
#include "domain.h"
#include <vector>
#include <map>
#include <string>
using std::to_string;
using std::map;
using std::vector;

class RepoEx {
private:
	string msg;
public:
	RepoEx(string msg) :msg{ msg } {}
	string get_message() {
		return msg;
	}
};

class Repo {
public:
	virtual void add_subject(const Subject& sub) = 0;
	virtual const vector<Subject>& get_all() noexcept = 0;
	virtual void delete_subject(const string& name) = 0;
	virtual const Subject& find_subject(const string& name) = 0;
	virtual void update_subject(const Subject& sub) = 0;
};


 