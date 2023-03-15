#include "MyLayout.h"
#include <qpainter.h>


void MyLayout::set_melodii() {
	repaint();
}

void MyLayout::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	int x = 10;
	for (int i = 0; i <= 10; i++) {
		int inaltime = srv.nr_rank(i);
		p.drawRect(x, height() - 20 * inaltime, 10, 20 * inaltime);
		x += 30;
	}
}
