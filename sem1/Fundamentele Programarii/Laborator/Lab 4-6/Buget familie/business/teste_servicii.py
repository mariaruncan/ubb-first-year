from business.servicii import *
from domain.entitati import egal_cheltuieli


def test_srv_adauga_cheltuiala_lista():
    lista = []
    l_undo = []
    srv_adauga_cheltuiala_lista(lista, 5, 60.5, "altele", l_undo)
    assert(len(lista) == 1)
    assert(egal_cheltuieli(lista[0], creeaza_cheltuiala(5, 60.5, "altele")))
    try:
        srv_adauga_cheltuiala_lista(lista, 40, 50, "casa", l_undo)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\nTip invalid!\n")


def test_srv_actualizeaza_zi():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 10, "suma": 100, "tip": "altele"}]
    l_undo = []
    srv_actualizeaza_zi(lista, 0, 15, l_undo)
    assert(egal_cheltuieli(lista[0], creeaza_cheltuiala(15, 60, "mancare")))
    try:
        srv_actualizeaza_zi(lista, 1, -6, l_undo)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")


def test_srv_actualizeaza_suma():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 10, "suma": 100, "tip": "altele"}]
    l_undo = []
    srv_actualizeaza_suma(lista, 0, 70, l_undo)
    assert (egal_cheltuieli(lista[0], creeaza_cheltuiala(1, 70, "mancare")))
    try:
        srv_actualizeaza_suma(lista, 1, -30, l_undo)
        assert False
    except Exception as ex:
        assert (str(ex) == "Suma invalida!\n")


def test_srv_actualizeaza_tip():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 10, "suma": 100, "tip": "altele"}]
    l_undo = []
    srv_actualizeaza_tip(lista, 0, "telefon", l_undo)
    assert (egal_cheltuieli(lista[0], creeaza_cheltuiala(1, 60, "telefon")))
    try:
        srv_actualizeaza_tip(lista, 1, "casa", l_undo)
        assert False
    except Exception as ex:
        assert (str(ex) == "Tip invalid!\n")


def test_srv_sterge_zi():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 10, "suma": 100, "tip": "altele"},
             {"zi": 1, "suma": 80, "tip": "telefon"}]
    l_undo = []
    srv_sterge_zi(lista, 1, l_undo)
    assert(len(lista) == 1)
    srv_sterge_zi(lista, 6, l_undo)
    assert(len(lista) == 1)
    try:
        srv_sterge_zi(lista, 45, l_undo)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")


def test_srv_sterge_interval():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "telefon"}]
    l_undo = []
    srv_sterge_interval(lista, 16, 20, l_undo)
    assert(len(lista) == 3)
    srv_sterge_interval(lista, 5, 13, l_undo)
    assert(len(lista) == 1)
    try:
        srv_sterge_interval(lista, -3, 6, l_undo)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")


def test_srv_sterge_tip():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}]
    l_undo = []
    srv_sterge_tip(lista, "telefon", l_undo)
    assert(len(lista) == 3)
    srv_sterge_tip(lista, "mancare", l_undo)
    assert(len(lista) == 1)
    try:
        srv_sterge_tip(lista, "casa", l_undo)
        assert False
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")


def test_srv_cautare_mai_mare_suma():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}]
    assert(len(srv_cautare_mai_mare_suma(lista, 70)) == 2)
    assert(len(srv_cautare_mai_mare_suma(lista, 150)) == 0)
    try:
        srv_cautare_mai_mare_suma(lista, -10)
        assert False
    except Exception as ex:
        assert(str(ex) == "Suma invalida!\n")


def test_srv_cautare_inainte_zi_mai_mic_suma():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}, {"zi": 4, "suma": 30, "tip": "mancare"}]
    assert(len(srv_cautare_inainte_zi_mai_mic_suma(lista, 7, 80)) == 2)
    assert(len(srv_cautare_inainte_zi_mai_mic_suma(lista, 15, 90)) == 3)
    try:
        srv_cautare_inainte_zi_mai_mic_suma(lista, 45, 20)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")
    try:
        srv_cautare_inainte_zi_mai_mic_suma(lista, 20, -50)
        assert False
    except Exception as ex:
        assert (str(ex) == "Suma invalida!\n")


def test_srv_cautare_tip():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}]
    assert(len(srv_cautare_tip(lista, "mancare")) == 2)
    assert (len(srv_cautare_tip(lista, "altele")) == 1)
    assert (len(srv_cautare_tip(lista, "telefon")) == 0)
    try:
        srv_cautare_tip(lista, "casa")
        assert False
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")


def test_srv_raport_suma_totala_tip():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}, {"zi": 15, "suma": 20, "tip": "mancare"}]
    assert(srv_raport_suma_totala_tip(lista, "mancare") == 160)
    assert (srv_raport_suma_totala_tip(lista, "altele") == 100)
    assert (srv_raport_suma_totala_tip(lista, "telefon") == 0)
    try:
        srv_raport_suma_totala_tip(lista, "casa")
        assert False
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")


def test_srv_raport_zi_cu_suma_maxima():
    lista1 = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
              {"zi": 1, "suma": 80, "tip": "mancare"}, {"zi": 15, "suma": 20, "tip": "mancare"}]
    assert(srv_raport_zi_cu_suma_maxima(lista1) == 1)
    lista2 = [{"zi": 3, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 200, "tip": "altele"},
              {"zi": 3, "suma": 80, "tip": "mancare"}]
    assert(srv_raport_zi_cu_suma_maxima(lista2) == 9)


def test_srv_raport_cu_suma_data():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 60, "tip": "telefon"}, {"zi": 15, "suma": 60, "tip": "mancare"}]
    assert(len(srv_raport_cu_suma_data(lista, 60)) == 3)
    assert (len(srv_raport_cu_suma_data(lista, 90)) == 0)
    try:
        srv_raport_cu_suma_data(lista, -30)
        assert False
    except Exception as ex:
        assert(str(ex) == "Suma invalida!\n")


def test_srv_raport_cheltuieli_sortate_tip():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 60, "tip": "telefon"}, {"zi": 15, "suma": 60, "tip": "mancare"}]
    lista_noua = srv_raport_cheltuieli_sortate_tip(lista)
    assert(lista_noua[0]["tip"] == "altele")
    assert(lista_noua[1]["tip"] == "mancare")
    assert(lista_noua[2]["tip"] == "mancare")
    assert(lista_noua[3]["tip"] == "telefon")


def test_srv_filtrare_tip():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 60, "tip": "telefon"}, {"zi": 15, "suma": 60, "tip": "mancare"}]
    assert(len(srv_filtrare_tip(lista, "mancare")) == 2)
    assert (len(srv_filtrare_tip(lista, "telefon")) == 3)
    try:
        srv_filtrare_tip(lista, "casa")
        assert False
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")


def test_srv_filtrare_mai_mici_suma():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 30, "tip": "telefon"}, {"zi": 15, "suma": 80, "tip": "mancare"}]
    assert(len(srv_filtrare_mai_mici_suma(lista, 60)) == 3)
    assert(len(srv_filtrare_mai_mici_suma(lista, 90)) == 1)
    try:
        srv_filtrare_mai_mici_suma(lista, 0)
        assert False
    except Exception as ex:
        assert(str(ex) == "Suma invalida!\n")


def test_srv_undo():
    lista = []
    l_undo = []
    srv_adauga_cheltuiala_lista(lista, 5, 60.5, "altele", l_undo)
    srv_adauga_cheltuiala_lista(lista, 16, 80.3, "telefon", l_undo)
    srv_actualizeaza_suma(lista, 1, 100, l_undo)
    assert(len(l_undo) == 3)
    srv_undo(lista, l_undo)
    assert(egal_cheltuieli(lista[1], creeaza_cheltuiala(16, 80.3, "telefon")))
    srv_undo(lista, l_undo)
    assert(len(lista) == 1)
    srv_undo(lista, l_undo)
    assert(len(lista) == 0)
    try:
        srv_undo(lista, l_undo)
        assert False
    except Exception as ex:
        assert(str(ex) == "Nu se mai poate face undo!")


def teste_srv():
    test_srv_adauga_cheltuiala_lista()
    test_srv_actualizeaza_zi()
    test_srv_actualizeaza_suma()
    test_srv_actualizeaza_tip()
    test_srv_sterge_zi()
    test_srv_sterge_interval()
    test_srv_sterge_tip()
    test_srv_cautare_mai_mare_suma()
    test_srv_cautare_inainte_zi_mai_mic_suma()
    test_srv_cautare_tip()
    test_srv_raport_suma_totala_tip()
    test_srv_raport_zi_cu_suma_maxima()
    test_srv_raport_cu_suma_data()
    test_srv_raport_cheltuieli_sortate_tip()
    test_srv_filtrare_tip()
    test_srv_filtrare_mai_mici_suma()
    test_srv_undo()
