from domain.entitati import creeaza_cheltuiala
from validation.validare import *


def test_valideaza_cheltuiala():
    ch1 = creeaza_cheltuiala(45, 60, "telefon")
    try:
        valideaza_cheltuiala(ch1)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")
    ch2 = creeaza_cheltuiala(56, -30, "casa")
    try:
        valideaza_cheltuiala(ch2)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\nSuma invalida!\nTip invalid!\n")
    ch3 = creeaza_cheltuiala(6, 80, "mancare")
    valideaza_cheltuiala(ch3)


def test_valideaza_zi():
    valideaza_zi(15)
    try:
        valideaza_zi(0)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")
    try:
        valideaza_zi(-60)
        assert False
    except Exception as ex:
        assert(str(ex) == "Zi invalida!\n")


def test_valideaza_suma():
    valideaza_suma(50.3)
    try:
        valideaza_suma(-89.6)
        assert False
    except Exception as ex:
        assert(str(ex) == "Suma invalida!\n")


def test_valideaza_tip():
    valideaza_tip("telefon")
    try:
        valideaza_tip("casa")
        assert False
    except Exception as ex:
        assert(str(ex) == "Tip invalid!\n")


def teste_val():
    test_valideaza_cheltuiala()
    test_valideaza_zi()
    test_valideaza_suma()
    test_valideaza_tip()
