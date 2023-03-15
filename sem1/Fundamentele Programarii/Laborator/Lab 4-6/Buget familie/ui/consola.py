from business.servicii import *
from domain.entitati import creeaza_cheltuiala
from infrastructure.colectii import gaseste_cheltuiala
from business.teste_servicii import teste_srv
from domain.teste_entitati import teste_ent
from infrastructure.teste_colectii import teste_col
from validation.teste_validare import teste_val


def comanda_adauga_actualizeaza(lista_cheltuieli, lista_undo):
    comenzi_adauga_actualizeaza = {
        "1": ui_adauga_cheltuiala,
        "2": ui_actualizeaza_cheltuiala
    }
    while True:
        print("""1. Adauga o noua cheltuiala
2. Actualizeaza o cheltuiala
3. Inapoi la meniul principal""")
        cmd = input("Introduceti o comanda: ")
        if cmd == "3":
            return
        if cmd in comenzi_adauga_actualizeaza:
            comenzi_adauga_actualizeaza[cmd](lista_cheltuieli, lista_undo)
        else:
            print("Comanda invalida!\n")


def ui_adauga_cheltuiala(lista_cheltuieli, lista_undo):
    z = int(input("Introduceti ziua:"))
    s = float(input("Introduceti suma:"))
    t = input("Introduceti tipul:")
    srv_adauga_cheltuiala_lista(lista_cheltuieli, z, s, t, lista_undo)


def ui_actualizeaza_cheltuiala(lista_cheltuieli, lista_undo):
    comenzi_actualizeaza = {
        "zi": srv_actualizeaza_zi,
        "suma": srv_actualizeaza_suma,
        "tip": srv_actualizeaza_tip
    }
    z = int(input("Ziua:"))
    s = float(input("Suma:"))
    t = input("Tipul:")
    poz = gaseste_cheltuiala(lista_cheltuieli, creeaza_cheltuiala(z, s, t))
    cmd = input("Ce doriti sa actualizati?(zi, suma, tip)")
    if cmd in comenzi_actualizeaza:
        val = input("Valoare noua:")
        comenzi_actualizeaza[cmd](lista_cheltuieli, poz, val, lista_undo)
    else:
        print("Comanda invalida!\n")


def comanda_sterge(lista_cheltuieli, lista_undo):
    comenzi_sterge = {
        "1": ui_sterge_zi,
        "2": ui_sterge_interval,
        "3": ui_sterge_tip
    }
    while True:
        print("""1. Sterge toate cheltuielile pentru o zi data
2. Sterge cheltuielile pentru un interval de zile
3. Sterge toate cheltuielile de un anumit tip
4. Inapoi la meniul principal""")
        cmd = input("Introduceti o comanda: ")
        if cmd == "4":
            return
        if cmd in comenzi_sterge:
            comenzi_sterge[cmd](lista_cheltuieli, lista_undo)
        else:
            print("Comanda invalida!\n")


def ui_sterge_zi(lista_cheltuieli, lista_undo):
    z = int(input("Ziua:"))
    srv_sterge_zi(lista_cheltuieli, z, lista_undo)


def ui_sterge_interval(lista_cheltuieli, lista_undo):
    ini = int(input("Inceput interval:"))
    sf = int(input("Sfarsit interval:"))
    srv_sterge_interval(lista_cheltuieli, ini, sf, lista_undo)


def ui_sterge_tip(lista_cheltuieli, lista_undo):
    t = input("Tip:")
    srv_sterge_tip(lista_cheltuieli, t, lista_undo)


def comanda_cautari(lista_cheltuieli):
    comenzi_cautari = {
        "1": ui_cautare_mai_mare_suma,
        "2": ui_cautare_inainte_zi_mai_mic_suma,
        "3": ui_cautare_tip
    }
    while True:
        print("""1. Tipareste toate cheltuielile mai mari decat o suma data
2. Tipareste toate cheltuielile efectuate inainte de o zi data si mai mici decat o suma
3. Tipareste toate cheltuielile de un anumit tip
4. Inapoi la meniul principal""")
        cmd = input("Introduceti comanda: ")
        if cmd == "4":
            return
        if cmd in comenzi_cautari:
            comenzi_cautari[cmd](lista_cheltuieli)
        else:
            print("Comanda invalida!\n")


def ui_cautare_mai_mare_suma(lista_cheltuieli):
    s = float(input("Suma:"))
    lista = srv_cautare_mai_mare_suma(lista_cheltuieli, s)
    if len(lista) > 0:
        ui_print(lista)
    else:
        print("Nu exista cheltuieli mai mari decat suma ", s)


def ui_cautare_inainte_zi_mai_mic_suma(lista_cheltuieli):
    z = int(input("Zi:"))
    s = float(input("Suma:"))
    lista = srv_cautare_inainte_zi_mai_mic_suma(lista_cheltuieli, z, s)
    if len(lista) > 0:
        ui_print(lista)
    else:
        print("Nu exista cheltuieli efectuate inainte de ziua", z, "si mai mici de suma", s)


def ui_cautare_tip(lista_cheltuieli):
    t = input("Tip:")
    lista = srv_cautare_tip(lista_cheltuieli, t)
    if len(lista) > 0:
        ui_print(lista)
    else:
        print("Nu exista cheltuieli de tipul ", t)


def comanda_rapoarte(lista_cheltuieli):
    comenzi_rapoarte = {
        "1": ui_raport_suma_totala_tip,
        "2": ui_raport_zi_cu_suma_maxima,
        "3": ui_raport_cu_suma_data,
        "4": ui_raport_cheltuieli_sortate_tip
    }
    while True:
        print("""1. Tipareste suma totala pentru un anumit tip de cheltuiala
2. Gaseste ziua in care suma cheltuita e maxima
3. Tipareste toate cheltuielile ce au o anumita suma
4. Tipareste toate cheltuielile sortate dupa tip
5. Inapoi la meniul principal""")
        cmd = input("Introduceti comanda: ")
        if cmd == "5":
            return
        if cmd in comenzi_rapoarte:
            pass
            comenzi_rapoarte[cmd](lista_cheltuieli)
        else:
            print("Comanda invalida!\n")


def ui_raport_suma_totala_tip(lista_cheltuieli):
    t = input("Tip:")
    s = srv_raport_suma_totala_tip(lista_cheltuieli, t)
    print("Suma totala pentru tipul ", t, "este ", s)


def ui_raport_zi_cu_suma_maxima(lista_cheltuieli):
    z = srv_raport_zi_cu_suma_maxima(lista_cheltuieli)
    print("Ziua cu suma maxima este: ", z)


def ui_raport_cu_suma_data(lista_cheltuieli):
    s = int(input("Suma:"))
    lista = srv_raport_cu_suma_data(lista_cheltuieli, s)
    if len(lista) > 0:
        ui_print(lista)
    else:
        print("Nu exista cheltuieli cu suma ", s)


def ui_raport_cheltuieli_sortate_tip(lista_cheltuieli):
    ui_print(srv_raport_cheltuieli_sortate_tip(lista_cheltuieli))


def comanda_filtrare(lista_cheltuieli):
    comenzi_filtrare = {
        "1": ui_filtrare_tip,
        "2": ui_filtrare_mai_mici_suma
    }
    while True:
        print("""1. Elimina toate cheltuielile de un anumit tip
2. Elimina toate cheltuielile mai mici decat o suma
3. Inapoi la meniul principal""")
        cmd = input("Introduceti o comanda: ")
        if cmd == "3":
            return
        if cmd in comenzi_filtrare:
            comenzi_filtrare[cmd](lista_cheltuieli)
        else:
            print("Comanda invalida!\n")


def ui_filtrare_tip(lista_cheltuieli):
    t = input("Tipul:")
    ui_print(srv_filtrare_tip(lista_cheltuieli, t))


def ui_filtrare_mai_mici_suma(lista_cheltuieli):
    s = int(input("Suma:"))
    ui_print(srv_filtrare_mai_mici_suma(lista_cheltuieli, s))


def ui_print(lista_cheltuieli):
    if len(lista_cheltuieli) == 0:
        print("Nu exista cheltuieli in lista!")
    else:
        for el in lista_cheltuieli:
            print(el)


def ui_undo(lista_cheltuieli, lista_undo):
    srv_undo(lista_cheltuieli, lista_undo)


def run():
    lista_cheltuieli = []
    lista_undo = []
    comenzi = {
        "1": comanda_adauga_actualizeaza,
        "2": comanda_sterge,
        "3": comanda_cautari,
        "4": comanda_rapoarte,
        "5": comanda_filtrare,
        "6": ui_print,
        "7": ui_undo
    }
    while True:
        print("""1. Adauga/actualizeaza
2. Sterge
3. Cautari
4. Rapoarte
5. Filtrare
6. Printare lista
7. Undo
8. Iesire din aplicatie""")
        cmd = input("Introduceti o comanda: ")
        if cmd == "8":
            print("EXIT")
            return
        if cmd in comenzi:
            try:
                if cmd in ["1", "2", "7"]:
                    comenzi[cmd](lista_cheltuieli, lista_undo)
                else:
                    comenzi[cmd](lista_cheltuieli)
            except ValueError:
                print("Valoare numerica invalida!\n")
            except Exception as ex:
                print(ex)
        else:
            print("Comanda invalida!\n")


def run_all_tests():
    teste_srv()
    teste_val()
    teste_ent()
    teste_col()
