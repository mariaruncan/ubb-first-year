from domain.entitati import creeaza_cheltuiala
from utils.utilitare import *


def test_cloneaza_lista():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}]
    assert(cloneaza_lista(lista) == lista)


def test_sterge_index():
    lista = [{"zi": 1, "suma": 60, "tip": "mancare"}, {"zi": 9, "suma": 100, "tip": "altele"},
             {"zi": 5, "suma": 80, "tip": "mancare"}]
    sterge_index(lista, 1)
    assert(len(lista) == 2)
    assert(lista[0] == creeaza_cheltuiala(1, 60, "mancare"))
    assert(lista[1] == creeaza_cheltuiala(5, 80, "mancare"))


def test_indexul_maximului_lista():
    lista = [2, 63, -80, 65, 70, 16, 13]
    assert(indexul_maximului_lista(lista) == 4)
    lista = [5, 1, 2, 1, 5]
    assert(indexul_maximului_lista(lista) == 0)


def teste_valid():
    test_cloneaza_lista()
    test_sterge_index()
    test_indexul_maximului_lista()
