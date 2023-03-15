#pragma once
#include <vector>
using std::vector;
#include "Melodie.h"
#include <qwidget.h>
#include "Service.h"

class MyLayout: public QWidget {
private:
	Service& srv;;
public:
	MyLayout(Service& s) :srv{ s } {
		repaint();
	}

	void set_melodii();

	void paintEvent(QPaintEvent* ev) override;
};

