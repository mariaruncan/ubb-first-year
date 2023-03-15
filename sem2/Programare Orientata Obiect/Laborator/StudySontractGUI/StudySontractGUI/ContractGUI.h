#pragma once
#include <qwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include "contract.h"
#include <qpainter.h>
#include <qslider.h>

class ContractCRUDGUI :public QWidget, public Observer {
private:
	Contract& con;

	QTableWidget* table = new QTableWidget;
	QLineEdit* lineName = new QLineEdit;
	QSlider* sliderNr = new QSlider;
	QLineEdit* lineFile = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{ "Add subject to contract" };
	QPushButton* btnClear = new QPushButton{ "Clear contract" };
	QPushButton* btnGenerate = new QPushButton{ "Generate with random subjects" };
	QPushButton* btnExport = new QPushButton{ "Export to file" };

	void init_comp();
	void connect_signals();
	void set_initial_state();
	void reload_table(const vector<Subject>& all);

public:
	ContractCRUDGUI(Contract& c) :con{ c } {
		con.addObserver(this);
		init_comp();
		connect_signals();
		set_initial_state();
	}

	void update() override{
		reload_table(con.get_subjects());
	}
};

