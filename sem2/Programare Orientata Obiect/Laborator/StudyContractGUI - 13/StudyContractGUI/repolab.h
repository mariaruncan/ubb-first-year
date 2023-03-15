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


class RepoLab : public Repo {
private:
	map<string, Subject> elems;
	vector<Subject> elems2;
	float prob;

public:
	RepoLab() = default;
	RepoLab(float p) :prob{ p } {}
	RepoLab(const RepoLab& ot) = delete;
	~RepoLab() = default;

	void add_subject(const Subject& sub) override{
		float const eroare = ((float)rand()) / (float)RAND_MAX;
		if (eroare < prob) {
			throw RepoEx(to_string(eroare));
		}
		for (const auto& s : elems) {
			if (s.second.get_name() == sub.get_name()) {
				throw RepoEx(to_string(prob));
			}
		}
		elems[sub.get_name()] = sub;
	}

	const vector<Subject>& get_all() noexcept override{
		elems2.clear();
		for (const auto& el : elems) {
			elems2.push_back(el.second);
		}
		return elems2;
	}

	void delete_subject(const string& name) override{
		float const eroare = ((float)rand()) / (float)RAND_MAX;
		if (eroare < prob) {
			throw RepoEx(to_string(eroare));
		}
		for (const auto& el : elems) {
			if (el.first == name) {
				elems.erase(el.first);
				return;
			}
		}
		throw RepoEx(to_string(prob));
	}

	const Subject& find_subject(const string& name) override {
		float const eroare = ((float)rand()) / (float)RAND_MAX;
		if (eroare < prob) {
			throw RepoEx(to_string(eroare));
		}
		for (const auto& el : elems) {
			if (el.first == name) {
				return el.second;
			}
		}
		throw RepoEx(to_string(prob));
	}

	void update_subject(const Subject& sub) override {
		float const eroare = ((float)rand()) / (float)RAND_MAX;
		if (eroare < prob) {
			throw RepoEx(to_string(eroare));
		}
		for (const auto& el : elems) {
			if (el.first == sub.get_name()) {
				elems[el.first] = sub;
				return;
			}
		}
		throw RepoEx(to_string(prob));
	}
};