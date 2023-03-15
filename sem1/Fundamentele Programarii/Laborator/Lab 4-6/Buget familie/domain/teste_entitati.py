from domain.entitati import *


def test_creeaza_cheltuiala():
    assert (creeaza_cheltuiala(15, 60.5, "altele") == {"zi": 15, "suma": 60.5, "tip": "altele"})


def test_cloneaza_cheltuiala():
    assert (cloneaza_cheltuiala(creeaza_cheltuiala(15, 60.5, "altele")) == {"zi": 15, "suma": 60.5, "tip": "altele"})


def test_egal_cheltuieli():
    assert (egal_cheltuieli(creeaza_cheltuiala(15, 60.5, "altele"), {"zi": 15, "suma": 60.5, "tip": "altele"}))
    assert (not(egal_cheltuieli(creeaza_cheltuiala(15, 50, "altele"), {"zi": 15, "suma": 60.5, "tip": "altele"})))


def teste_ent():
    test_creeaza_cheltuiala()
    test_cloneaza_cheltuiala()
    test_egal_cheltuieli()
