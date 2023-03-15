#include "GUI.h"
#include <QtWidgets/QApplication>
#include "teste.h"

int run(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repo repo{ "melodii.txt" };
    Service srv{ repo };
    GUI* w = new GUI{ srv };
    w->show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    test_all();
    run(argc, argv);
    return 0;
}
