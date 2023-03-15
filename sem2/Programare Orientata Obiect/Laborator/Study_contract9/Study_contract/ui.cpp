#include "ui.h"
#include <iostream>
#include <vector>
using std::cin;
using std::cout;


void UI::print_subject(const Subject& s) {
	cout << s.get_name() << "\t\t" << s.get_hours() << "\t\t" << s.get_type() << "\t\t" << s.get_teacher() << "\n";
}

void UI::print_list(const vector<Subject>& list) {
	if (list.size() == 0)
		cout << "There are no subjects in the list!\n\n";
	else {
		cout << "Name\t\tHours\t\tType\t\tTeacher\n";
		for (const Subject& s : list) {
			print_subject(s);
		}
		cout << "\n";
	}
}

int UI::read_command() {
	cout << "----------------------------\n";
	cout << "Subject commands:\n";
	cout << "1. Add subject\n";
	cout << "2. Delete subject\n";
	cout << "3. Update subject\n";
	cout << "4. Search for subject\n";
	cout << "5. Print all subjects\n";
	cout << "6. Filter\n";
	cout << "7. Sort\n";
	cout << "8. Report type - lab 8\n";
	cout << "9. Undo\n";
	cout << "Contract commands:\n";
	cout << "10. Add subject to contract\n";
	cout << "11. Generate contract\n";
	cout << "12. Clear contract\n";
	cout << "13. Print contract\n";
	cout << "14. Export contract\n";
	cout << "0. EXIT\n";
	cout << "----------------------------\n";
	cout << ">>>";
	int cmd;
	cin >> cmd;
	cout << "\n";
	return cmd;
}

void UI::sample_subjects() {
	srv.add_subject("oop", "5", "obl", "ana");
	srv.add_subject("so", "4", "obl", "ion");
	srv.add_subject("alg", "2", "fac", "ana");
	srv.add_subject("mate", "5", "opt", "maria");
	srv.add_subject("sda", "7", "fac", "ana");
	srv.add_subject("sd", "1", "opt", "alex");
	srv.add_subject("ag", "6", "fac", "ion");
}

void UI::ui_add() {
	string name;
	string hours;
	string type;
	string teacher;
	cout << "Name: ";
	cin >> name;
	cout << "Number of hour per week: ";
	cin >> hours;
	cout << "Type: ";
	cin >> type;
	cout << "Teacher's name: ";
	cin >> teacher;
	cout << "\n";
	srv.add_subject(name, hours, type, teacher);
	cout << "Subject added!\n\n";
}

void UI::ui_delete() {
	string name;
	cout << "Name: ";
	cin >> name;
	cout << "\n";
	srv.delete_subject(name);
	cout << "Subject deleted!\n\n";
}

void UI::ui_update() {
	string name;
	string hours;
	string type;
	string teacher;
	cout << "Name: ";
	cin >> name;
	cout << "New number of hours per week: ";
	cin >> hours;
	cout << "New type: ";
	cin >> type;
	cout << "New teacher: ";
	cin >> teacher;
	cout << "\n";
	srv.update_subject(name, hours, type, teacher);
	cout << "Subject updated!\n\n";
}

void UI::ui_find() {
	string name;
	cout << "Name of the subject to search for: ";
	cin >> name;
	cout << "\n";
	cout << "Name\t\tHours\t\tType\t\tTeacher\n";
	const Subject& s = srv.find_subject(name);
	print_subject(s);
	cout << "\n";
}

void UI::ui_print_subjects() {
	const vector<Subject>& list = srv.get_all();
	print_list(list);
}

void UI::ui_filter() {
	cout << "1. By number of hours per week\n";
	cout << "2. By teacher\n";
	cout << ">>>";
	int cmd;
	cin >> cmd;
	cout << "\n";
	if (cmd == 1) {
		cout << "Maximum number of hours per week: ";
		int h;
		cin >> h;
		cout << "\n";
		const vector<Subject>& rez = srv.filter_hours(h);
		print_list(rez);
	}
	else if (cmd == 2) {
		cout << "Name of the teacher: ";
		string n;
		cin >> n;
		cout << "\n";
		const vector<Subject>& rez = srv.filter_teacher(n);
		print_list(rez);
	}
	else {
		cout << "Invalid command!\n\n";
	}
}

void UI::ui_sort() {
	cout << "1. By name\n";
	cout << "2. By number of hours per week\n";
	cout << "3. By teacher and type\n";
	cout << ">>>";
	int cmd;
	cin >> cmd;
	cout << "\n";
	if (cmd == 1 || cmd == 2 || cmd == 3) {
		cout << "1. Ascending\n2. Descending\n>>>";
		int rev;
		cin >> rev;
		cout << "\n";
		if (rev == 1 || rev == 2) {
			const vector<Subject>& rez = srv.sort_list(cmd, rev);
			print_list(rez);
		}
		else {
			cout << "Invalid command!\n\n";
			return;
		}
	}
	else {
		cout << "Invalid command!\n\n";
	}
}

void UI::ui_add_contract() {
	cout << "Enter subject's name:";
	string name;
	cin >> name;
	srv.add_contract(name);
	cout << "\nSubject added to contract!\n\n";
}

void UI::ui_generate_contract() {
	cout << "Enter how many subject will be in contract: ";
	int nr;
	cin >> nr;
	cout << "\n";
	srv.generate_contract(nr);
	ui_print_contract();
}

void UI::ui_clear_contract() {
	srv.clear_contract();
	cout << "Contract cleared!\n\n";
}

void UI::ui_print_contract() {
	const vector<Subject>& con = srv.get_contract();
	cout << "Study contract\n\n";
	print_list(con);
}

void UI::ui_export_contract() {
	cout << "Enter the name of the file: ";
	string fname;
	cin >> fname;
	srv.export_contract(fname);
	cout << "\nContract exported (file " << fname << ")\n\n";
}

void UI::ui_report() {
	map<string, DTO> rez = srv.report_type();
	for (auto& el : rez) {
		cout << el.first << "  DTO " << el.second.get_type() << " " << el.second.get_count() << "\n";
	}
	cout << "\n\n";
}

void UI::ui_undo() {
	srv.undo();
	cout << "Undo realizat cu succes!\n\n";
}


void UI::run() {
	cout << "\nStudy contract - pb 5\n\n";
	int cmd{ -1 };
	while (cmd) {
		try {
			cmd = read_command();
			switch (cmd) {
			case 0:
				cout << "Byeeee :)\n";
				break;
			case 1:
				ui_add();
				break;
			case 2:
				ui_delete();
				break;
			case 3:
				ui_update();
				break;
			case 4:
				ui_find();
				break;
			case 5:
				ui_print_subjects();
				break;
			case 6:
				ui_filter();
				break;
			case 7:
				ui_sort();
				break;
			case 8:
				ui_report();
				break;
			case 9:
				ui_undo();
				break;
			case 10:
				ui_add_contract();
				break;
			case 11:
				ui_generate_contract();
				break;
			case 12:
				ui_clear_contract();
				break;
			case 13:
				ui_print_contract();
				break;
			case 14:
				ui_export_contract();
				break;
			default:
				cout << "Invalid command!\n\n";
			}
		}
		catch (RepoException& ex) {
			cout << ex.get_message() << "\n";
		}
		catch (ValidateException& ex) {
			cout << ex.get_message() << "\n";
		}
		catch (ContractException& ex) {
			cout << ex.get_message() << "\n";
		}
		catch (UndoException& ex) {
			cout << ex.get_message() << "\n";
		}
		catch (RepoEx& ex) {
			cout << ex.get_message() << "\n";
		}

	}
}
