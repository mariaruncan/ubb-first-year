#pragma once
#include "Service.h"

#include <QtWidgets/QWidget>
#include <qtablewidget.h>
#include <qboxlayout.h>
#include "MyModel.h"
#include <qtableview.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qslider>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "MyLayout.h"

class GUI : public QWidget {
private:
	Service& srv;

	QTableWidget* tabel = new QTableWidget;
	MyModel* model = new MyModel{ srv };
	QTableView* tv = new QTableView;
	QLabel* labelId = new QLabel;
	QLineEdit* edtTitlu = new QLineEdit;
	QSlider* sliderRank = new QSlider;
	QPushButton* btnDelete = new QPushButton{ "Sterge" };
	QPushButton* btnUpdate = new QPushButton{ "Update" };

	MyLayout* my = new MyLayout{ srv };

	void reload_table(vector<Melodie>& all);
	void init_comp();
	void connect_signals();

public:
	GUI(Service& s) :srv{ s } {
		tv->setModel(model);
		init_comp();
		connect_signals();
		reload_table(srv.get_sortate());
	}

};
