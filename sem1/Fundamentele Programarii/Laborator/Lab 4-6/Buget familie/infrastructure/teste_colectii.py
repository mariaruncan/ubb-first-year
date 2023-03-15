from domain.entitati import creeaza_cheltuiala
from infrastructure.colectii import *


def test_adauga_cheltuiala_lista():
    lista = []
    adauga_cheltuiala_lista(lista, creeaza_cheltuiala(2, 60, "mancare"))
    assert(len(lista) == 1)
    adauga_cheltuiala_lista(lista, creeaza_cheltuiala(6, 80, "imbracaminte"))
    assert(len(lista) == 2)


def test_gaseste_cheltuiala():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 60, "tip": "telefon"}, {"zi": 15, "suma": 60, "tip": "mancare"}]
    assert(gaseste_cheltuiala(lista, creeaza_cheltuiala(5, 60, "telefon")) == 2)
    try:
        gaseste_cheltuiala(lista, creeaza_cheltuiala(20, 60, "intretinere"))
        assert False
    except Exception as ex:
        assert(str(ex) == "Cheltuiala inexistenta!\n")


def test_sortare_sume_pe_zile():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 60, "tip": "telefon"}, {"zi": 1, "suma": 60, "tip": "mancare"}]
    lista_sume = sortare_sume_pe_zile(lista)
    assert(lista_sume[1] == 120)
    assert(lista_sume[9] == 100)
    assert(lista_sume[15] == 0)


def teste_col():
    test_adauga_cheltuiala_lista()
    test_gaseste_cheltuiala()
    test_sortare_sume_pe_zile()
