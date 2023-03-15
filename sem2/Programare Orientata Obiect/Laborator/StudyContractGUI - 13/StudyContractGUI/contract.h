#pragma once
#include "repository.h"
#include "Observer.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

class ContractException
{

private:

	string msg;

public:
	/*
		Constructor with parameters for a RepoException object
		Pre: message - string
	*/
	ContractException(string message) :msg{ message } {
	}

	/*
		Getter for message
	*/
	string get_message() {
		return msg;
	}
};

class Contract: public Observable {
private:
	Repo& repo;
	vector<Subject> all;

public:

	Contract(Repo& repo) noexcept: repo{ repo } {
	}

	Contract(Contract& con) = delete;

	/*
		Clear the contract
		Post: contract is empty
	*/
	void clear_contract();

	/*
		Adds a subject in contract
		Pre: name - string, the name of the subject
		Throw RepoException if the subject does not exist
			  ContractException if the subject is already in contract
	*/
	void add_contract(const string& name);

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
		Remove a subject from contract
		Pre: name - string, the name of the subject
		Post: if the subject was in contract, it is no longer
	*/
	void delete_contract(const string& name);

	/*
		Update a subject in contract
		Pre: sub - subject
		Post: if there was a subject with the same name as sub, is updated
	*/
	void update_contract(const Subject& sub);

	/*
		Return a list with subjects from contract
	*/
	const vector<Subject>& get_subjects() noexcept;

};
