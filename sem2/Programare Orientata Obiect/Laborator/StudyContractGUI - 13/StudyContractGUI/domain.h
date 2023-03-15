#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::ostream;

class Subject
{

private:

	string name;
	int hours;
	string type;
	string teacher;

public:
	/*
		Default constructor for Subject
	*/
	Subject() noexcept: hours{ 0 } {
	}

	/*
		Constructor with parameters for a Subject object
		Pre: name, type, teachers - string, hours - int
	*/
	Subject(const string& name, int hours, const string& type, const string& teacher) :name{ name }, hours{ hours }, type{ type }, teacher{ teacher }{
	}

	/*
		Copy constructor
		Pre: ot is a Subject object
		Post: a new Subject object is created, with the same attributes as ot
	*/
	Subject(const Subject& ot) :name{ ot.name }, hours{ ot.hours }, type{ ot.type }, teacher{ ot.teacher }{
		//cout << "Copy constructor Subject\n";
	}

	/*
		Getter for a subject's name
	*/
	string get_name() const;

	/*
		Getter for a subject's number of hours per week
	*/
	int get_hours() const noexcept;

	/*
		Getter for a subject's type
	*/
	string get_type() const;

	/*
		Getter for a subject's teacher
	*/
	string get_teacher() const;


};

class DTO {
private:
	string type;
	int count;

public:
	/*
		Default constructor for DTO object
	*/
	DTO() : type{ "" }, count{ 0 }{};

	/*
		Constructor with parameters for a DTO object
		Pre: t - string, c - int
	*/
	DTO(const string& t, int c) :type{ t }, count{ c }{
	}

	/*
		Copy constructor
		Copying DTO-type objects is "forbidden"
	*/
	DTO(const DTO& d) = delete;

	/*
		Getter for a DTO type
	*/
	string get_type() {
		return type;
	}

	/*
		Getter for a DTO count
	*/
	int get_count() noexcept{
		return count;
	}

	/*
		Increments a DTO's count
	*/
	void increment_count() noexcept{
		count++;
	}
};
