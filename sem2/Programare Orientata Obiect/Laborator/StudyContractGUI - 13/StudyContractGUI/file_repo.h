#pragma once
#include <fstream>
#include "repository.h"
using std::string;

class FileRepo :public SubjectRepo {
private:
	string file_name;
	void load_from_file();
	void write_to_file();
public:

	/*
		Constructor with parameters for a FileRepo object
		Pre: fname - string(name of a file)
		Post: the list is populated with the data in the file
	*/
	FileRepo(const string& fname) :SubjectRepo(), file_name{ fname }{
		load_from_file();
	}

	/*
		Adds a subject in list
		Pre: sub is a Subject object
		Post: the subject is added
		Throws RepoException with message "Subject already exists!\n" if the subject is already in the list
	*/
	void add_subject(const Subject& sub) override;

	/*
		Deletes the subject with the given name
		Pre: name - string
		Post: the subject with the given name is erased
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the given name
	*/
	void delete_subject(const string& name) override;

	/*
		Updates the subject with the same name as sub
		Pre: sub - Subject object
		Post: the subject is updated
		Throws RepoException with message "Subject does not exist!\n" if there is no subject with the same name as sub
	*/
	void update_subject(const Subject& sub) override;

	/*
		Destructor for FileRepo
	*/
	~FileRepo() {
		SubjectRepo::~SubjectRepo();
	}

};