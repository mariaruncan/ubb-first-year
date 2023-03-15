#pragma once
#include "service.h"
#include "ContractGUI.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qbuttongroup.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>
#include "MyTableModel.h"
#include <qtableview.h>

class GUI : public QWidget {
private:
    Service& srv;

    QPushButton* btnSortName = new QPushButton{ "Sort by name" };
    QPushButton* btnSortHours = new QPushButton{ "Sort by hours" };
    QPushButton* btnSortTeacherType = new QPushButton{ "Sort by teacher and type" };

    QCheckBox* checkboxA = new QCheckBox{ "Ascending" };
    QCheckBox* checkboxD = new QCheckBox{ "Descending" };

    QListWidget* listSubjects = new QListWidget;
    MyTableModel* model = new MyTableModel{ srv.get_all() };
    QTableView* tableSubjects = new QTableView;

    QLineEdit* editName = new QLineEdit;
    QSpinBox* spinHours = new QSpinBox;
    QComboBox* comboType = new QComboBox;
    QLineEdit* editTeacher = new QLineEdit;

    QPushButton* btnAdd = new QPushButton{ "Add" };
    QPushButton* btnDelete = new QPushButton{ "Delete" };
    QPushButton* btnUpdate = new QPushButton{ "Update" };
    QPushButton* btnClear = new QPushButton{ "Clear fields" };
    QPushButton* btnFilterHours = new QPushButton{ "Filter by max no of hours" };
    QPushButton* btnFilterTeacher = new QPushButton{ "Filter by teacher" };
    QPushButton* btnReload = new QPushButton{ "Reload list" };
    QPushButton* btnUndo = new QPushButton{ "Undo" };
    QPushButton* btnReport = new QPushButton{ "Report type" };

    QLabel* lb = new QLabel{ "Contract" };
    QPushButton* btnAddC = new QPushButton{ "Add subject to contract" };
    QPushButton* btnClearC = new QPushButton{ "Clear contract" };
    QPushButton* btnGenerateC = new QPushButton{ "Generate contract with random subjects" };
    QSpinBox* spinNrS = new QSpinBox;
    QPushButton* btnCrud = new QPushButton{ "Contract CRUD GUI" };


    void init_gui_components();
    void connect_signals();
    void set_initial_gui_state();
    void reload_list(const vector<Subject>& all);
    void reload_table(const vector<Subject>& all);

public:

    GUI(Service& srv) :srv{ srv } {
        tableSubjects->setModel(model);
        init_gui_components();
        connect_signals();
        set_initial_gui_state();
    }
};
