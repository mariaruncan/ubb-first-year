#include "MyModel.h"

int MyModel::rowCount(const QModelIndex& parent) const {
    return srv.get_sortate().size();
}

int MyModel::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant MyModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        int rand = index.row();
        vector<Melodie>& all = srv.get_sortate();
        if (index.column() == 0) {
            return QString::number(all[rand].get_id());
        }
        else if (index.column() == 1) {
            return QString::fromStdString(all[rand].get_titlu());
        }
        else if (index.column() == 2) {
            return QString::fromStdString(all[rand].get_artist());
        }
        else if (index.column() == 3) {
            return QString::number(all[rand].get_rank());
        }
        else {
            return QString::number(srv.nr_rank(all[rand].get_rank()));
        }
    }
    return QVariant();
}

void MyModel::set_melodii() {
    emit layoutChanged();
}
