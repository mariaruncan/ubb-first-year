#pragma once
#include "domain.h"

class ValidateException
{

private:

	string msg;

public:
	/*
		Constructor for class ValidateException
	*/
	ValidateException(string message) :msg{ message } {
	}
	/*
		Getter for message
	*/
	string get_message() {
		return msg;
	}
};


class Validator
{

public:

	Validator() = default;

	/*
		Validates a subject.
		Throws ValidateException if the subject is not valid with message:
			- "Invalid name!\n" - for empty name,
			- "Invalid number of hours!\n" - for hours <= 0,
			- "Invalid type!\n" - for empty type,
			- "Invalid teacher!\n" -  for empty teacher.
		Pre: sub is a Subject object
	*/
	void validate_subject(const string& name, const string& hours, const string& type, const string& teacher);

	/*
		Validates a string
		Throws ValidateException with message "Invalid string!\n" if the string is empty
		Pre: str - string
	*/
	void validate_string(const string& str);

};
