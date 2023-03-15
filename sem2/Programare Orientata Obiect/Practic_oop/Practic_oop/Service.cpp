#include "Service.h"

vector<Melodie> Service::get_sortate() {
    vector<Melodie> rez = repo.get_all();
    std::sort(rez.begin(), rez.end(), [](const Melodie& m1, const Melodie& m2) {
        return m1.get_rank() > m2.get_rank(); });
    return rez;
}

int Service::nr_rank(int r) {
    int k = 0;
    for (const auto& el : repo.get_all()) {
        if (el.get_rank() == r) {
            k++;
        }
    }
    return k;
}

void Service::sterge_id(int id) {
    repo.sterge(id);
}

int Service::nr_artist(string artist) {
    int k = 0;
    for (const auto& el : repo.get_all()) {
        if (el.get_artist() == artist) {
            k++;
        }
    }
    return k;
}

Melodie Service::find_id(int id)
{
    return repo.find(id);
}

void Service::update(int id, string titlu, int rank) {
    Melodie m = find_id(id);
    Melodie noua = Melodie{ id, titlu, m.get_artist(), rank };
    repo.update(noua);
}
