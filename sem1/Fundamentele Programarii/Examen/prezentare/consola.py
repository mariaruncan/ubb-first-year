class UI(object):

    def __init__(self, srv):
        self.__srv = srv

    def __ui_adauga_carte(self):
        id_carte = int(input("Introduceti id:"))
        titlu = input("Introduceti titlu:")
        autor = input("Introduceti autor:")
        an_aparitie = int(input("Introduceti anAparitie:"))
        pret = float(input("Introduceti pret:"))
        self.__srv.adauga_carte(id_carte, titlu, autor, an_aparitie, pret)
        print("Adaugat cu succes!\n")

    def __ui_sterge_carte_cifra(self):
        cif = int(input("Intorduceti cifra:"))
        self.__srv.sterge_carte_cifra(cif)
        print("Stergerea a avut succes!\n")

    def __ui_filtrare(self):
        rezultat = self.__srv.filtrare()
        if len(rezultat) == 0:
            print("Nu exista carti care corespund filtrului!\n", self.__srv.get_filtru())
        else:
            print(self.__srv.get_filtru())
            for carte in rezultat:
                print(carte)

    def __ui_undo(self):
        self.__srv.undo()
        print("Undo a avut loc cu succes!\n")

    def __ui_modificare_filtru(self):
        text = input("Introduceti text:")
        pret_max = float(input("Introduceti pretul maxim:"))
        self.__filtru = self.__srv.modifica_filtru(text, pret_max)
        print(self.__filtru)
        print("Filtru modificat cu succes!\n")

    def run(self):
        while True:
            print("1. Adauga carte")
            print("2. Sterge carte cu o cifra data in an")
            print("3. Filtrare carti dupa titlu si anAparitie")
            print("4. Undo ultima operatie de stergere")
            print("5. Modificare filtru")
            print("6. Exit")
            cmd = input(">>>")
            if cmd == "6":
                return
            try:
                if cmd == "1":
                    self.__ui_adauga_carte()
                elif cmd == "2":
                    self.__ui_sterge_carte_cifra()
                elif cmd == "3":
                    self.__ui_filtrare()
                elif cmd == "4":
                    self.__ui_undo()
                elif cmd == "5":
                    self.__ui_modificare_filtru()
                else:
                    print("Comanda invalida!\n")
            except ValueError:
                print("Valoare numerica invalida!")
            except Exception as ex:
                print(ex)
