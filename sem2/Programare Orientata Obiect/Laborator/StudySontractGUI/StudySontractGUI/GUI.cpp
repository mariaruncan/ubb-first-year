#include "GUI.h"

void GUI::init_gui_components() {
	QHBoxLayout* ly1 = new QHBoxLayout;
	ly1->addWidget(tableSubjects);

	QHBoxLayout* lySort = new QHBoxLayout;
	lySort->addWidget(btnSortName);
	lySort->addWidget(btnSortHours);
	lySort->addWidget(btnSortTeacherType);

	QHBoxLayout* lySort2 = new QHBoxLayout;
	checkboxA->setChecked(true);
	lySort2->addWidget(checkboxA);
	lySort2->addWidget(checkboxD);

	QVBoxLayout* ly2 = new QVBoxLayout;
	ly2->addWidget(listSubjects);
	ly2->addLayout(lySort);
	ly2->addLayout(lySort2);

	QFormLayout* lyFields = new QFormLayout;
	lyFields->addRow("Name", editName);
	spinHours->setMaximum(8);
	lyFields->addRow("Hours", spinHours);
	comboType->addItem("");
	comboType->addItem("obligatorie");
	comboType->addItem("optionala");
	comboType->addItem("facultativa");
	lyFields->addRow("Type", comboType);
	lyFields->addRow("Teacher", editTeacher);

	QGridLayout* lyBtn = new QGridLayout;
	lyBtn->addWidget(btnAdd, 0, 0);
	lyBtn->addWidget(btnDelete, 1, 0);
	lyBtn->addWidget(btnUpdate, 2, 0);
	lyBtn->addWidget(btnClear, 3, 0);
	lyBtn->addWidget(btnFilterHours, 0, 1);
	lyBtn->addWidget(btnFilterTeacher, 1, 1);
	lyBtn->addWidget(btnReload, 2, 1);
	lyBtn->addWidget(btnUndo, 3, 1);

	QVBoxLayout* ly3 = new QVBoxLayout;
	ly3->addLayout(lyFields);
	ly3->addLayout(lyBtn);
	ly3->addWidget(btnReport);

	QGridLayout* ly4 = new QGridLayout;
	ly4->addWidget(lb, 0, 0);
	ly4->addWidget(btnGenerateC, 1, 0);
	ly4->addWidget(spinNrS, 1, 1);
	ly4->addWidget(btnAddC, 2, 0);
	ly4->addWidget(btnClearC, 3, 0);
	ly4->addWidget(btnCrud, 2, 1);
	
	QGridLayout* lyMain = new QGridLayout;
	setLayout(lyMain);
	lyMain->addLayout(ly2, 0, 0);
	lyMain->addLayout(ly1, 1, 0);
	lyMain->addLayout(ly3, 0, 1);
	lyMain->addLayout(ly4, 1, 1);
	
}

void GUI::connect_signals() {
	QObject::connect(checkboxA, &QCheckBox::stateChanged, this, [this]() {
		if (checkboxA->isChecked()) {
			checkboxD->setChecked(false);
		}
		else {
			checkboxD->setChecked(true);
		}
		});

	QObject::connect(checkboxD, &QCheckBox::stateChanged, this, [this]() {
		if (checkboxD->isChecked()) {
			checkboxA->setChecked(false);
		}
		else {
			checkboxA->setChecked(true);
		}
		});

	QObject::connect(btnSortName, &QPushButton::clicked, this, [this]() {
		if (checkboxA->isChecked()) {
			reload_list(srv.sort_list(1, 1));
			reload_table(srv.sort_list(1, 1));
		}
		else {
			reload_list(srv.sort_list(1, 2));
			reload_table(srv.sort_list(1, 2));
		}
		});

	QObject::connect(btnSortHours, &QPushButton::clicked, this, [this]() {
		if (checkboxA->isChecked()) {
			reload_list(srv.sort_list(2, 1));
			reload_table(srv.sort_list(2, 1));
		}
		else {
			reload_list(srv.sort_list(2, 2));
			reload_table(srv.sort_list(2, 2));
		}
		});
	QObject::connect(btnSortTeacherType, &QPushButton::clicked, this, [this]() {
		if (checkboxA->isChecked()) {
			reload_list(srv.sort_list(3, 1));
			reload_table(srv.sort_list(3, 1));
		}
		else {
			reload_list(srv.sort_list(3, 2));
			reload_table(srv.sort_list(3, 2));
		}
		});

	QObject::connect(listSubjects, &QListWidget::itemSelectionChanged, this, [this]() {
		auto selected = listSubjects->selectedItems();
		if (selected.isEmpty()) {
			editName->setText("");
			spinHours->setValue(0);
			comboType->setCurrentIndex(0),
				editTeacher->setText("");
		}
		else {
			string name = selected.at(0)->data(Qt::UserRole).toString().toStdString();
			const Subject& s = srv.find_subject(name);

			editName->setText(QString::fromStdString(s.get_name()));
			spinHours->setValue(s.get_hours());
			for (int i = 1; i < comboType->count(); i++) {
				if (comboType->itemText(i).toStdString() == s.get_type()) {
					comboType->setCurrentIndex(i);
					break;
				}
			}
			editTeacher->setText(QString::fromStdString(s.get_teacher()));
		}
		});

	QObject::connect(btnClear, &QPushButton::clicked, this, [this]() {
		editName->setText("");
		spinHours->setValue(0);
		comboType->setCurrentIndex(0);
		editTeacher->setText("");
		});

	QObject::connect(btnAdd, &QPushButton::clicked, this, [this]() {
		string name = editName->text().toStdString();
		string hours = to_string(spinHours->value());
		string type = comboType->currentText().toStdString();
		string teacher = editTeacher->text().toStdString();
		try {
			srv.add_subject(name, hours, type, teacher);
			reload_list(srv.get_all());
			reload_table(srv.get_all());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(ex.get_message()));
		}
		catch (ValidateException& ex) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(ex.get_message()));
		}
		});

	QObject::connect(btnDelete, &QPushButton::clicked, this, [this]() {
		string name = editName->text().toStdString();
		try {
			srv.delete_subject(name);
			reload_list(srv.get_all());
			reload_table(srv.get_all());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(ex.get_message()));
		}
		});

	QObject::connect(btnUpdate, &QPushButton::clicked, this, [this]() {
		string name = editName->text().toStdString();
		string nhours = to_string(spinHours->value());
		string ntype = comboType->currentText().toStdString();
		string nteacher = editTeacher->text().toStdString();
		try {
			srv.update_subject(name, nhours, ntype, nteacher);
			reload_list(srv.get_all());
			reload_table(srv.get_all());
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(ex.get_message()));
		}
		catch (ValidateException& ex) {
			QMessageBox::information(this, "ValidateException", QString::fromStdString(ex.get_message()));
		}
		});

	QObject::connect(btnUndo, &QPushButton::clicked, this, [this]() {
		try {
			srv.undo();
			reload_list(srv.get_all());
			reload_table(srv.get_all());
		}
		catch (UndoException& ex) {
			QMessageBox::information(this, "UndoException", QString::fromStdString(ex.get_message()));
		}
		});

	QObject::connect(btnFilterHours, &QPushButton::clicked, this, [this]() {
		vector<Subject> rez = srv.filter_hours(spinHours->value());
		reload_list(rez);
		reload_table(rez);
		});

	QObject::connect(btnFilterTeacher, &QPushButton::clicked, this, [this]() {
		vector<Subject> rez = srv.filter_teacher(editTeacher->text().toStdString());
		reload_list(rez);
		reload_table(rez);
		});

	QObject::connect(btnReload, &QPushButton::clicked, this, [this]() {
		reload_list(srv.get_all());
		reload_table(srv.get_all());
		});

	QObject::connect(btnReport, &QPushButton::clicked, this, [this]() {
		map<string, DTO> rez = srv.report_type();
		string msg;
		for (auto& el : rez) {
			msg = msg + el.first + ": " + to_string(el.second.get_count()) + "\n";
		}
		QMessageBox::information(this, "Report type", QString::fromStdString(msg));
		});

	QObject::connect(btnGenerateC, &QPushButton::clicked, this, [this]() {
		const int nr = spinNrS->value();
		srv.generate_contract(nr);
		});

	QObject::connect(btnAddC, &QPushButton::clicked, this, [this]() {
		string name = editName->text().toStdString();
		try {
			srv.add_contract(name);
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(ex.get_message()));
		}
		catch (ContractException& ex) {
			QMessageBox::information(this, "ContractException", QString::fromStdString(ex.get_message()));
		}
		});

	QObject::connect(btnClearC, &QPushButton::clicked, this, [this]() {
		srv.clear_contract();
		});

	QObject::connect(btnCrud, &QPushButton::clicked, this, [this]() {
		auto cWnd = new ContractCRUDGUI{ srv.get_contract() };
		cWnd->show();
		});

}

void GUI::set_initial_gui_state() {
	reload_list(srv.get_all());
	reload_table(srv.get_all());
}

void GUI::reload_list(const vector<Subject>& all) {
	listSubjects->clear();
	for (const auto& el : all) {
		string name = el.get_name();
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(name) };
		item->setData(Qt::UserRole, QString::fromStdString(el.get_name()));
		listSubjects->addItem(item);
	}
}

void GUI::reload_table(const vector<Subject>& all) {
	model->setSubjects(all);
}

