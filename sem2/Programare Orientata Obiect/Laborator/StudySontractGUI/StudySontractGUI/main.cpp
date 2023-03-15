#include "GUI.h"
#include "validator.h"
#include "file_repo.h"
#include "service.h"
#include "tests.h"
#include <QtWidgets/QApplication>

void run(int argc, char* argv[]) {
    QApplication a(argc, argv);

    Validator valid;
    FileRepo repo{ "subjects.txt" };
    Contract contr{ repo };
    Service srv{ repo, valid, contr };

    GUI* g = new GUI{ srv };
    g->show();

    a.exec();
}

int main(int argc, char* argv[]) {
    //test_all();
    run(argc, argv);
    return 0;

}
