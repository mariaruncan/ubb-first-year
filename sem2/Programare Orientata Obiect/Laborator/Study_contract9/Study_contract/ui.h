#pragma once
#include "service.h"

class UI
{

private:

	Service& srv;

	int read_command();
	void print_subject(const Subject&);
	void print_list(const vector<Subject>&);
	void ui_add();
	void ui_delete();
	void ui_update();
	void ui_find();
	void ui_print_subjects();
	void ui_filter();
	void ui_sort();
	void sample_subjects();
	void ui_add_contract();
	void ui_generate_contract();
	void ui_clear_contract();
	void ui_print_contract();
	void ui_export_contract();
	void ui_report();
	void ui_undo();

public:

	UI(Service& srv) noexcept :srv{ srv } {
	}

	UI(const UI& ui) = delete;

	void run();

};