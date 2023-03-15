#include "GUI.h"

void GUI::reload_table(vector<Melodie>& all) {
	tabel->clear();
	tabel->setRowCount(all.size());
	tabel->setColumnCount(4);
	int i = 0;
	for (const auto& el : all) {
		QTableWidgetItem* id = new QTableWidgetItem(QString::number(el.get_id()));
		QTableWidgetItem* titlu = new QTableWidgetItem(QString::fromStdString(el.get_titlu()));
		QTableWidgetItem* artist = new QTableWidgetItem(QString::fromStdString(el.get_artist()));
		QTableWidgetItem* rank = new QTableWidgetItem(QString::number(el.get_rank()));
		tabel->setItem(i, 0, id);
		tabel->setItem(i, 1, titlu);
		tabel->setItem(i, 2, artist);
		tabel->setItem(i, 3, rank);
		i++;
	}
}

void GUI::init_comp() {
	QVBoxLayout* lyMain = new QVBoxLayout;
	setLayout(lyMain);

	QFormLayout* lyDr = new QFormLayout;
	lyDr->addRow("Id", labelId);
	lyDr->addRow("Titlu", edtTitlu);
	sliderRank->setOrientation(Qt::Horizontal);
	sliderRank->setMaximum(10);
	sliderRank->setTickPosition(QSlider::TicksBelow);
	lyDr->addRow("Rank", sliderRank);
	lyDr->addRow(btnDelete);
	lyDr->addRow(btnUpdate);

	QHBoxLayout* lySus = new QHBoxLayout;
	lySus->addWidget(tabel);
	lySus->addWidget(tv);
	lySus->addLayout(lyDr);

	lyMain->addLayout(lySus);
	lyMain->addSpacing(100);
	
	
	my->show();
}

void GUI::connect_signals() {
	QObject::connect(tabel, &QTableWidget::itemSelectionChanged, this, [this]() {
		if (tabel->selectedItems().empty()){ 
			labelId->setText("");
			edtTitlu->setText("");
			sliderRank->setValue(0);
			return;
		}
		else {
			int rand = tabel->selectionModel()->selectedIndexes().at(0).row();
			QString id = tabel->item(rand, 0)->data(Qt::DisplayRole).toString();
			labelId->setText(id);
			QString titlu = tabel->item(rand, 1)->data(Qt::DisplayRole).toString();
			edtTitlu->setText(titlu);
			int rank = tabel->item(rand, 3)->data(Qt::DisplayRole).toInt();
			sliderRank->setValue(rank);
		}
		});

	QObject::connect(btnDelete, &QPushButton::clicked, this, [this]() {
		if (labelId->text().isEmpty()) {
			return;
		}
		int id = labelId->text().toInt();
		Melodie& m = srv.find_id(id);
		int nr = srv.nr_artist(m.get_artist());
		if (nr == 1) {
			QMessageBox::information(this, "Informare", "Aceasta este ultima melodie a artistului!");
		}
		else {
			srv.sterge_id(id);
			reload_table(srv.get_sortate());
			model->set_melodii();
			my->repaint();
		}
		});

	QObject::connect(btnUpdate, &QPushButton::clicked, this, [this]() {
		if (labelId->text().isEmpty()) {
			return;
		}
		int id = labelId->text().toInt();
		string titlu = edtTitlu->text().toStdString();
		int rank = sliderRank->value();
		srv.update(id, titlu, rank);
		reload_table(srv.get_sortate());
		model->set_melodii();
		my->repaint();
		});
}
