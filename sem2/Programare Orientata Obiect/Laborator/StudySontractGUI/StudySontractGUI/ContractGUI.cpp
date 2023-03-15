#include "ContractGUI.h"

void ContractCRUDGUI::init_comp() {
	QFormLayout* lyFields = new QFormLayout;
	lyFields->addRow("Subject name", lineName);
	sliderNr->setMaximum(10);
	sliderNr->setOrientation(Qt::Horizontal);
	sliderNr->setTickPosition(QSlider::TicksBelow);
	lyFields->addRow("Nr of subjects", sliderNr);
	lyFields->addRow("File name", lineFile);

	QGridLayout* lyBtn = new QGridLayout;
	lyBtn->addWidget(btnAdd, 0, 0);
	lyBtn->addWidget(btnGenerate, 1, 0);
	lyBtn->addWidget(btnClear, 0, 1);
	lyBtn->addWidget(btnExport, 1, 1);

	QVBoxLayout* ly2 = new QVBoxLayout;
	ly2->addLayout(lyFields);
	ly2->addLayout(lyBtn);

	QHBoxLayout* lyMain = new QHBoxLayout;
	setLayout(lyMain);
	lyMain->addWidget(table);
	lyMain->addLayout(ly2);
}

void ContractCRUDGUI::connect_signals() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, [this]() {
		try {
			con.add_contract(lineName->text().toStdString());
			reload_table(con.get_subjects());
		}
		catch (ContractException& ex) {
			QMessageBox::information(this, "ContractException", QString::fromStdString(ex.get_message()));
		}
		catch (RepoException& ex) {
			QMessageBox::information(this, "RepoException", QString::fromStdString(ex.get_message()));
		}
		});

	QObject::connect(btnGenerate, &QPushButton::clicked, this, [this]() {
		con.generate_contract(sliderNr->value());
		reload_table(con.get_subjects());
		});

	QObject::connect(btnClear, &QPushButton::clicked, this, [this]() {
		con.clear_contract();
		reload_table(con.get_subjects());
		});

	QObject::connect(btnExport, &QPushButton::clicked, this, [this]() {
		try {
			string file = lineFile->text().toStdString();
			con.export_contract(file);
			string text = "Contract exported (file " + file + ".csv).";
			QMessageBox::information(this, "Info status", QString::fromStdString(text));
		}
		catch (ContractException& ex) {
			QMessageBox::information(this, "ContractException", QString::fromStdString(ex.get_message()));
		}
		});
}

void ContractCRUDGUI::set_initial_state() {
	reload_table(con.get_subjects());
}

void ContractCRUDGUI::reload_table(const vector<Subject>& all) {
	table->clear();
	table->setRowCount((int)all.size() + 1);
	table->setColumnCount(4);
	table->setItem(0, 0, new QTableWidgetItem(QString("Name")));
	table->setItem(0, 1, new QTableWidgetItem(QString("Hours")));
	table->setItem(0, 2, new QTableWidgetItem(QString("Type")));
	table->setItem(0, 3, new QTableWidgetItem(QString("Teacher")));
	for (int i = 0; i < all.size(); i++) {
		QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(all[i].get_name()));
		table->setItem(i + 1, 0, name);
		QTableWidgetItem* hours = new QTableWidgetItem(QString::number(all[i].get_hours()));
		table->setItem(i + 1, 1, hours);
		QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(all[i].get_type()));
		table->setItem(i + 1, 2, type);
		QTableWidgetItem* teacher = new QTableWidgetItem(QString::fromStdString(all[i].get_teacher()));
		table->setItem(i + 1, 3, teacher);
	}
}

