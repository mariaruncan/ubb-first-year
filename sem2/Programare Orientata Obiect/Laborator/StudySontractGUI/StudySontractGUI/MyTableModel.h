#pragma once
#include <vector>
#include "domain.h"
#include <QAbstractTableModel>
#include <qbrush.h>
using std::vector;

class MyTableModel: public QAbstractTableModel {
private:
	vector<Subject> all;
public:
	MyTableModel(const vector<Subject>& subs) : all{ subs } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return all.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Subject s = all[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(s.get_name());
			}
			else if (index.column() == 1) {
				return QString::number(s.get_hours());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(s.get_type());
			}
			else {
				return QString::fromStdString(s.get_teacher());
			}
		}

		return QVariant{};
	}

	void setSubjects(const vector<Subject>& subs) {
		this->all = subs;
		emit layoutChanged();
	}
};

