#pragma once
#include <vector>
#include "domain.h"
#include "repolab.h"
using std::vector;

class RepoException
{

private:

	string msg;

public:
	/*
		Constructor with parameters for a RepoException object
		Pre: message - string
	*/
	RepoException(string message) :msg{ message } {
	}

	/*
		Getter for message
	*/
	string get_message() {
		return msg;
	}
};

class SubjectRepo : public Repo {

private:
	vector<Subject> elems;

public:
	/*
		Default constructor for a SubjectRepo object
	*/
	SubjectRepo() = default;

	/*
		Copy constructor
		Copying SubjectRepo-type objects is "forbidden"
	*/
	SubjectRepo(const SubjectRepo& ot) = delete;

	/*
		Default destructor for SubjectRepo
	*/
	~SubjectRepo() = default;

	/*
		Adds a subject in list
		Pre: sub is a Subject object
		Post: the subject is added
		Throws RepoException with message "Subject already exists!\n" if the subject is already in the list
	*/
	void add_subject(const Subject& sub) override;

	/*
		Returns a reference to the subjects list
	*/
	const vector<Subject>& get_all() noexcept override;

	/*
		Deletes the subject with the given name
		Pre: name - string
		Post: the subject with the given name is erased
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the given name
	*/
	void delete_subject(const string& name) override;

	/*
		Searches for a subject with the given name and returns it
		Pre: name - string
		Post: returns a Subject object with the given name
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the given name
	*/
	const Subject& find_subject(const string& name) override;

	/*
		Updates the subject with the same name as sub
		Pre: sub - Subject object
		Post: the subject is updated
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the same name as sub
	*/
	void update_subject(const Subject& sub) override;

};
