#pragma once
#include <string>
#include "domain.h"
#include "file_repo.h"
#include "validator.h"
#include "contract.h"
#include "undo.h"
#include <algorithm>
#include <functional>
#include <map>
using std::map;
using std::string;
using std::function;

class Service
{

private:

	Repo& repo;
	Validator& valid;
	Contract& con;
	vector<Actiune_undo*> undo_actions;

public:
	/*
		Default constructor for a Service object
	*/
	Service() = default;

	/*
		Constructor with parameters for a Service object
		Pre: repo - SubjectRepo, valid - Validator
	*/
	Service(Repo& repo, Validator& valid, Contract& contr) noexcept :repo{ repo }, valid{ valid }, con{ contr }{
	}

	/*
		Copy constructor
		Copying Service-type objects is "forbidden"
	*/
	Service(const Service& ot) = delete;

	/*
		Destructor for Service
	*/
	~Service() {
		con.~Contract();
		repo.~Repo();
		valid.~Validator();
		for (const Actiune_undo* el : undo_actions) {
			delete el;
		}
	}

	/*
		Adds a subject to the list
		Pre: name, type, teacher - string, hours - int
		Post: a subject with the given attributes is added to the list
		Throws ValidateException if the subject is not valid with message:
			- "Invalid name!\n" - for empty name,
			- "Invalid number of hours!\n" - for hours <= 0,
			- "Invalid type!\n" - for empty type,
			- "Invalid teacher!\n" -  for empty teacher.
		Throws RepoException with message "Subject already exists!\n" if the subject is already in the list
	*/
	void add_subject(const string& name, const string& hours, const string& type, const string& teacher);

	/*
		Deletes a subject with the given name
		Pre: name - string
		Post: the subject with the given name is deleted
		Throws ValidateException with message "Invalid string!\n" if the string is empty
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the given name
		*/
	void delete_subject(const string& name);

	/*
		Updates the subject with the name name
		Pre: name, n_type, n_teacher - string, n_hours - int
		Post: the subject with name name has the attributes name, n_hours, n_type and n_teacher
		Throws ValidateException if the subject is not valid with message:
			- "Invalid name!\n" - for empty name,
			- "Invalid number of hours!\n" - for n_hours <= 0,
			- "Invalid type!\n" - for empty n_type,
			- "Invalid teacher!\n" -  for empty n_teacher.
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the given name
		*/
	void update_subject(const string& name, const string& n_hours, const string& n_type, const string& n_teacher);

	/*
		Searches for a subject with given name
		Pre: name - string
		Post: returns a subject with the given name
		Throws ValidateException with message "Invalid string!\n" if the string is empty
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the given name
	*/
	const Subject& find_subject(const string& name);

	/*
		Returns a list with all subjects
		Post: reutrns a vector of Subject objects
	*/
	const vector<Subject>& get_all() noexcept;

	/*
		Filter subjects by number of hours per week
		Pre: h - int (the maximum number of hours per week)
		Post: return a list of subjects that have hours <= h
	*/
	const vector<Subject> filter_hours(int h);

	/*
		Filter subjects by teacher
		Pre: n - string (name of the teacher)
		Post: return a list of subjects that have the teacher with the name name
	*/
	const vector<Subject> filter_teacher(const string& name);

	/*
		General function for sort
		Pre: cmd - int (1 by name, 2 by nr of hours, 3 by teacher and type), rev - int (1 ascending, 2 descending)
		Post: return a sorted vector by the given criteria
	*/
	const vector<Subject> sort_list(int cmd, int rev);

	/*
		Return a list with subjects from contract
	*/
	//const vector<Subject>& get_contract() noexcept;
	Contract& get_contract();

	/*
		Adds a subject in contract
		Pre: name - string, the name of the subject
		Throw RepoException if the subject does not exist
			  ContractException if the subject is already in contract
	*/
	void add_contract(const string& name);

	/*
		Clear the contract
		Post: the contract is empty
	*/
	void clear_contract() noexcept;

	/*
		Generates a contract with nr subjects
		Pre: nr - int, the number of subjects
		Post: the contract contains nr subjects
	*/
	void generate_contract(int nr);

	/*
		Export contract
		Pre: file_name - string, the file name
		Post: a file with name file_name is created and contains the contract
	*/
	void export_contract(const string& file_name);

	/*
		Returns a map, key si a string representing a type of Subject and value is a DTO witch has type 
		and number of Subjects of that type
	*/
	map<string, DTO> report_type();

	/*
		Undo the last add/delete/update operation
		Post: the list of Subjects is like before the last add/delete/update
	*/
	void undo();
};
