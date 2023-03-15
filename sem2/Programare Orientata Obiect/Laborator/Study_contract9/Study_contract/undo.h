#pragma once
#include "domain.h"
#include "repository.h"
#include <vector>
using std::vector;

class UndoException
{

private:

	string msg;

public:
	/*
		Constructor with parameters for a RepoException object
		Pre: message - string
	*/
	UndoException(string message) :msg{ message } {
	}

	/*
		Getter for message
	*/
	string get_message() {
		return msg;
	}
};

class Actiune_undo {
public:

	/*
		Undo function
	*/
	virtual void do_undo() = 0;

	/*
		Default destructor for ActiuneUndo
	*/
	virtual ~Actiune_undo() = default;
};

class Undo_add :public Actiune_undo {
private:
	Subject sub;
	Repo& repo;

public:
	Undo_add(Repo& repo, const Subject& s): repo{repo}, sub{s}{}
	void do_undo() override {
		repo.delete_subject(sub.get_name());
	}
	
};

class Undo_delete :public Actiune_undo {
private:
	Subject sub;
	Repo& repo;

public:
	Undo_delete(Repo& repo, const Subject& s) : repo{ repo }, sub{ s }{}
	void do_undo() override {
		repo.add_subject(sub);
	}
};

class Undo_update :public Actiune_undo {
private:
	Subject sub;
	Repo& repo;
public:
	Undo_update(Repo& repo, const Subject& s) : repo{ repo }, sub{ s }{}
	void do_undo() override {
		repo.update_subject(sub);
	}
	
};