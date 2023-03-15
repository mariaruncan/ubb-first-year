#pragma once
#include <qabstracttablemodel>
#include "Melodie.h"
#include <qwidget.h>
#include <vector>
#include "Service.h"
using std::vector;

class MyModel:public QAbstractTableModel {
private:
	Service& srv;
public:
	MyModel(Service& s) :srv{ s } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void set_melodii();
};

