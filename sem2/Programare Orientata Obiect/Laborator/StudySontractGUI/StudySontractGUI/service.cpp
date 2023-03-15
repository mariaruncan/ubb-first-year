#include "service.h"

void Service::add_subject(const string& name, const string& hours, const string& type, const string& teacher) {
	valid.validate_subject(name, hours, type, teacher);
	int const int_hours{ stoi(hours) };
	Subject s(name, int_hours, type, teacher);
	repo.add_subject(s);
	undo_actions.push_back(new Undo_add{ repo, s });
}

void Service::delete_subject(const string& name) {
	valid.validate_string(name);
	Subject s = repo.find_subject(name);
	repo.delete_subject(name);
	undo_actions.push_back(new Undo_delete{ repo,s });
	con.delete_contract(name);
}

void Service::update_subject(const string& name, const string& n_hours, const string& n_type, const string& n_teacher) {
	valid.validate_subject(name, n_hours, n_type, n_teacher);
	int const int_n_hours = stoi(n_hours);
	Subject s(name, int_n_hours, n_type, n_teacher);
	Subject s2 = repo.find_subject(name);
	repo.update_subject(s);
	undo_actions.push_back(new Undo_update{ repo, s2 });
	con.update_contract(s);
}

const Subject& Service::find_subject(const string& name) {
	valid.validate_string(name);
	return repo.find_subject(name);
}

const vector<Subject>& Service::get_all() noexcept {
	return repo.get_all();
}

const vector<Subject> Service::filter_hours(int h) {
	const vector<Subject>& all = repo.get_all();
	vector<Subject> rez;
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [h](const Subject& s) noexcept {return s.get_hours() <= h; });
	return rez;
}

const vector<Subject> Service::filter_teacher(const string& name) {
	const vector<Subject>& all = repo.get_all();
	vector<Subject> rez;
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [=](const Subject& s) {return s.get_teacher() == name; });
	return rez;
}

const vector<Subject> Service::sort_list(int cmd, int rev) {
	vector<Subject> rez = repo.get_all();
	switch (cmd) {
	case 1:
		std::sort(rez.begin(), rez.end(), [](const Subject& s1, const Subject& s2) {
			return s1.get_name() < s2.get_name();
			});
		break;
	case 2:
		std::sort(rez.begin(), rez.end(), [](const Subject& s1, const Subject& s2) {
			return s1.get_hours() < s2.get_hours();
			});
		break;
	default:
		std::sort(rez.begin(), rez.end(), [](const Subject& s1, const Subject& s2) {
			if (s1.get_teacher() != s2.get_teacher())
				return s1.get_teacher() < s2.get_teacher();
			else
				return s1.get_type() < s2.get_type();
			});
		break;
	}

	if (rev == 2) {
		std::reverse(rez.begin(), rez.end());
	}
	return rez;
}
/*
const vector<Subject>& Service::get_contract() noexcept{
	return con.get_subjects();
}
*/
Contract& Service::get_contract() {
	return con;
}

void Service::add_contract(const string& name) {
	con.add_contract(name);
}

void Service::clear_contract() noexcept{
	con.clear_contract();
}

void Service::generate_contract(int nr) {
	con.clear_contract();
	con.generate_contract(nr);
}

void Service::export_contract(const string& file_name) {
	con.export_contract(file_name);
}

map<string, DTO> Service::report_type() {
	const vector<Subject>& all = repo.get_all();
	map<string, DTO> mymap;
	for (const Subject& s : all) {
		auto it = mymap.find(s.get_type());
		if (it == mymap.end()) {
			DTO obj{ s.get_type(), 1 };
			mymap[s.get_type()] = obj;
		}
		else {
			mymap[s.get_type()].increment_count();
		}
	}
	return mymap;

}

void Service::undo() {
	if (undo_actions.empty())
		throw UndoException("Undo impossible!\n");
	else {
		Actiune_undo* act = undo_actions.back();
		act->do_undo();
		undo_actions.pop_back();
		delete act;
	}
}
