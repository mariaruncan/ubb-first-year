#include "tests.h"
#include <assert.h>

void test_validator() {
	Validator valid = Validator();
	valid.validate_subject("a", "4", "b", "c");
	try {
		valid.validate_subject("", "-6dw", "", "c");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid name!\nInvalid number of hours!\nInvalid type!\n");
	}
	try {
		valid.validate_subject("a", "26k", "", "");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid number of hours!\nInvalid type!\nInvalid teacher!\n");
	}

	valid.validate_string("asd");
	try {
		valid.validate_string("");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid name!\n");
	}

}

void test_domain() {
	Subject s = Subject("a", 2, "b", "c");
	assert(s.get_name() == "a");
	assert(s.get_hours() == 2);
	assert(s.get_type() == "b");
	assert(s.get_teacher() == "c");
}

void test_repository() {
	// add + get_all
	SubjectRepo repo;
	assert(repo.get_all().size() == 0);
	repo.add_subject(Subject("oop", 2, "obl", "maria"));
	assert(repo.get_all().size() == 1);
	try {
		repo.add_subject(Subject("oop", 2, "sdffs", "sfd"));
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject already exists!\n");
	}
	repo.add_subject(Subject("sda", 4, "obl", "ana"));
	const vector<Subject>& list = repo.get_all();
	assert(list[0].get_name() == "oop");
	assert(list[1].get_name() == "sda");

	// find
	const Subject& s = repo.find_subject("sda");
	assert(s.get_hours() == 4);
	assert(s.get_type() == "obl");
	assert(s.get_teacher() == "ana");
	try {
		repo.find_subject("fp");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}

	// update
	repo.update_subject(Subject("oop", 7, "opt", "ion"));
	const Subject& s1 = repo.find_subject("oop");
	assert(s1.get_hours() == 7);
	assert(s1.get_type() == "opt");
	assert(s1.get_teacher() == "ion");
	try {
		repo.update_subject(Subject("fp", 9, "obl", "vasile"));
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}

	// delete
	assert(repo.get_all().size() == 2);
	repo.delete_subject("sda");
	assert(repo.get_all().size() == 1);
	try {
		repo.delete_subject("fp");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}
}

void test_service() {
	SubjectRepo repo;
	Validator valid;
	Contract con{ repo };
	Service srv{ repo, valid, con };

	// add_subject + get_all
	const vector<Subject>& v = srv.get_all();
	assert(v.size() == 0);
	srv.add_subject("a", "2", "b", "c");
	assert(v.size() == 1);
	try {
		srv.add_subject("a", "5", "d", "s");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject already exists!\n");
	}
	try {
		srv.add_subject("s", "-4", "", "d");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid number of hours!\nInvalid type!\n");
	}
	srv.add_subject("d", "6", "e", "f");
	assert(v.size() == 2);
	srv.add_subject("b", "6", "e", "f");
	assert(v.size() == 3);
	srv.undo();
	assert(v.size() == 2);

	//update_subject
	srv.update_subject("a", "8", "x", "y");
	const Subject& s = srv.find_subject("a");
	assert(s.get_hours() == 8);
	assert(s.get_type() == "x");
	assert(s.get_teacher() == "y");
	srv.update_subject("a", "100", "k", "q");
	srv.undo();
	assert(s.get_hours() == 8);
	assert(s.get_type() == "x");
	assert(s.get_teacher() == "y");
	try {
		srv.update_subject("q", "7", "", "");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid type!\nInvalid teacher!\n");
	}
	try {
		srv.update_subject("q", "7", "d", "q");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}

	// find_subject
	const Subject& s1 = srv.find_subject("d");
	assert(s1.get_hours() == 6);
	assert(s1.get_type() == "e");
	assert(s1.get_teacher() == "f");
	try {
		srv.find_subject("");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid name!\n");
	}
	try {
		srv.find_subject("q");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}

	// delete_subject
	assert(v.size() == 2);
	srv.delete_subject("a");
	assert(v.size() == 1);
	try {
		srv.delete_subject("");
		assert(false);
	}
	catch (ValidateException& ex) {
		assert(ex.get_message() == "Invalid name!\n");
	}
	try {
		srv.delete_subject("q");
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}
	srv.undo();
	assert(v.size() == 2);
	// contract
	srv.generate_contract(2);
	assert(srv.get_contract().get_subjects().size() == 2);
	try {
		srv.add_contract("a");
		assert(false);
	}
	catch (ContractException& ex) {
		assert(ex.get_message() == "Subject is already in contract!\n");
	}
	srv.export_contract("test.csv");
	srv.clear_contract();
	assert(srv.get_contract().get_subjects().size() == 0);
	while (true) {
		try {
			srv.undo();
		}
		catch (UndoException& ex) {
			assert(ex.get_message() == "Undo impossible!\n");
			break;
		}
	}
}

void test_sort() {
	SubjectRepo repo;
	Validator valid;
	Contract con{ repo };
	Service srv{ repo, valid, con };
	srv.add_subject("b", "7", "f", "k");
	srv.add_subject("a", "2", "a", "k");
	srv.add_subject("c", "5", "a", "b");

	vector<Subject> rez = srv.sort_list(1, 1);
	rez = rez;
	assert(rez[0].get_name() == "a");
	assert(rez[1].get_name() == "b");
	assert(rez[2].get_name() == "c");

	rez = srv.sort_list(2, 2);
	assert(rez[0].get_hours() == 7);
	assert(rez[1].get_hours() == 5);
	assert(rez[2].get_hours() == 2);

	rez = srv.sort_list(3, 1);
	assert(rez[0].get_teacher() == "b" && rez[0].get_type() == "a");
	assert(rez[1].get_teacher() == "k" && rez[1].get_type() == "a");
	assert(rez[2].get_teacher() == "k" && rez[2].get_type() == "f");
}

void test_filter() {
	SubjectRepo repo;
	Validator valid;
	Contract con{ repo };
	Service srv{ repo, valid, con};
	srv.add_subject("b", "7", "f", "k");
	srv.add_subject("a", "2", "a", "k");
	srv.add_subject("c", "5", "a", "b");

	vector<Subject> rez = srv.filter_hours(5);
	assert(rez.size() == 2);
	assert(rez[0].get_hours() <= 5);
	assert(rez[1].get_hours() <= 5);

	rez = srv.filter_hours(1);
	assert(rez.size() == 0);

	rez = srv.filter_teacher("k");
	assert(rez.size() == 2);
	assert(rez[0].get_teacher() == "k");
	assert(rez[1].get_teacher() == "k");

	rez = srv.filter_teacher("x");
	assert(rez.size() == 0);
}

void test_contract() {
	SubjectRepo repo;
	Contract con{ repo };
	// add
	repo.add_subject(Subject{ "a", 2, "b", "c" });
	con.add_contract("a");
	try {
		con.add_contract("x");
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Subject does not exist!\n");
	}
	try {
		con.add_contract("a");
	}
	catch (ContractException& ex) {
		assert(ex.get_message() == "Subject is already in contract!\n");
	}
	// generate
	repo.add_subject(Subject{ "x", 2, "y", "z" });
	con.generate_contract(2);
	// get
	const vector<Subject>& aux = con.get_subjects();
	assert(aux.size() == 2);
	// update
	Subject s{ "a", 10, "d", "f" };
	con.update_contract(s);
	assert(aux[0].get_hours() == 10 || aux[1].get_hours() == 10);
	con.update_contract(Subject{ "x",4,"f","f" });
	// delete
	repo.add_subject(Subject{ "q", 4, "w", "e" });
	con.add_contract("q");
	assert(con.get_subjects().size() == 3);
	con.delete_contract("q");
	assert(con.get_subjects().size() == 2);
	// export
	con.export_contract("test");
	// clear
	con.clear_contract();
	assert(aux.size() == 0);
}

void test_report() {
	SubjectRepo repo;
	Validator valid;
	Contract con{ repo };
	Service srv{ repo, valid, con };
	srv.add_subject("oop", "5", "obl", "ana");
	srv.add_subject("so", "4", "obl", "ion");
	srv.add_subject("alg", "2", "fac", "ana");
	srv.add_subject("mate", "5", "opt", "maria");
	srv.add_subject("sda", "7", "fac", "ana");
	srv.add_subject("sd", "1", "opt", "alex");
	srv.add_subject("ag", "6", "fac", "ion");
	map<string, DTO> mymap = srv.report_type();
	assert(mymap["obl"].get_count() == 2); 
	assert(mymap["obl"].get_type() == "obl");
	assert(mymap["opt"].get_count() == 2);
	assert(mymap["fac"].get_count() == 3);
}

void test_file_repo() {
	try {
		FileRepo r{ "numefictiv.txt" };
		assert(false);
	}
	catch (RepoException& ex) {
		assert(ex.get_message() == "Error open:numefictiv.txt");
	}
	FileRepo repo{ "test.txt" };
	const vector<Subject>& all = repo.get_all();
	assert(all.size() == 3);
	assert(all[0].get_name() == "a");
	assert(all[1].get_name() == "d");
	assert(all[2].get_name() == "g");
	repo.add_subject(Subject{ "m", 10, "n", "o" });
	assert(all[3].get_hours() == 10);
	assert(all.size() == 4);
	repo.update_subject(Subject{ "m", 1, "x", "y" });
	assert(all[3].get_hours() == 1);
	repo.delete_subject("m");
	assert(all.size() == 3);
}


void test_all() {
	test_validator();
	test_domain();
	test_repository();
	test_service();
	test_sort();
	test_filter();
	test_contract();
	test_report();
	test_file_repo();
}
