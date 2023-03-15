from ui.consola import ui_print
from business.servicii import srv_adauga_cheltuiala_lista, srv_sterge_zi, srv_undo, srv_cautare_tip


def run_batch_mode():
    lista_cheltuieli = []
    lista_undo = []
    print("""adauga cheltuiala
sterge zi
raport acelasi tip
undo
afisare lista
""")
    comanda = input("Introduceti comenzile:\n")
    lista_comenzi = comanda.split(";")
    for cmd in lista_comenzi:
        var = cmd.split(" ")
        if var[0] == "adauga" and len(var) == 4:
            try:
                srv_adauga_cheltuiala_lista(lista_cheltuieli, int(var[1]), float(var[2]), var[3], lista_undo)
            except ValueError:
                print("Valoare numerica invalida!")
            except Exception as ex:
                print(ex)
        elif var[0] == "sterge" and len(var) == 2:
            try:
                srv_sterge_zi(lista_cheltuieli, int(var[1]), lista_undo)
            except ValueError:
                print("Valoare numerica invalida!")
            except Exception as ex:
                print(ex)
        elif var[0] == "raport" and len(var) == 2:
            lista = srv_cautare_tip(lista_cheltuieli, var[1])
            if len(lista) > 0:
                ui_print(lista)
                print("\n")
            else:
                print("Nu exista cheltuieli de tipul ", var[1])
        elif var[0] == "undo" and len(var) == 1:
            try:
                srv_undo(lista_cheltuieli, lista_undo)
            except Exception as ex:
                print(ex)
        elif var[0] == "afisare" and len(var) == 1:
            ui_print(lista_cheltuieli)
            print("\n")
        else:
            print("Comanda invalida!")


# adauga 12 60 mancare;adauga 5 300 intretinere;adauga 20 60 mancare;adauga 16 80 telefon;afisare;sterge 5;afisare;raport mancare;undo;undo;undo;afisare
