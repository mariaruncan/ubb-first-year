from domain.entitati import Carte


class RepositoryCarti(object):
    # clasa pentru memorarea unei liste de obiecte de tip Carte
    def __init__(self, filename):
        self.__filename = filename
        self.__elems = []

    def __citeste_tot_din_fisier(self):
        # functia citeste din fisier toate liniile dintr-un fisier si construieste obiectele de tip Carte
        # corespunzatoare pe care le adauga la lista self.__elems
        # date de intrare: -
        # date de iesire: -
        with open(self.__filename, "r") as f:
            self.__elems = []
            linii = f.readlines()
            for linie in linii:
                linie = linie.strip()
                if linie != "":
                    parti = linie.split(",")
                    carte = Carte(int(parti[0]), parti[1], parti[2], int(parti[3]), float(parti[4]))
                    self.__elems.append(carte)

    def __scrie_tot_in_fisier(self):
        # functia scrie intr-un fisier pe linii separate string-urile corespunzatoare obiectelor de tip Carte din lista
        # self.__elems
        # date de intrare: -
        # date de iesire: -
        with open(self.__filename, "w") as f:
            for carte in self.__elems:
                f.write(str(carte.get_id()) + "," + carte.get_titlu() + "," + carte.get_autor() + "," +
                        str(carte.get_an_aparitie()) + "," + str(carte.get_pret()) + "\n")

    def __append_la_fisier(self, carte):
        # functia scrie la sfarsitul unui fisier, pe o linie separata, string-ul corespunzator pentru carte
        # date de intrare: carte - de tip Carte
        # date de iesire: -
        with open(self.__filename, "a") as f:
            f.write(str(carte.get_id()) + "," + carte.get_titlu() + "," + carte.get_autor() + "," +
                    str(carte.get_an_aparitie()) + "," + str(carte.get_pret()) + "\n")

    def __len__(self):
        # functia returneaza numarul de obicte pe care le avem in lista self.__elems
        # date de intrare: -
        # date de iesire: un nr intreg
        return len(self.__elems)

    def adauga(self, carte):
        # functia adauga o carte in fisier
        # date de intrare: carte - de tip Carte
        # date de iesire: -
        # ridica exceptie de tipul Exception cu mesajul "Carte existenta!" daca o carte cu acelasi id se afla deja in
        # lista
        self.__citeste_tot_din_fisier()
        if carte in self.__elems:
            raise Exception("Carte existenta!")
        self.__append_la_fisier(carte)

    def sterge_carte(self, carte):
        # functia sterge din lista si din fisier o anumita carte
        # date de intrare: carte - de tip Carte
        # date de iesire: -
        self.__citeste_tot_din_fisier()
        for el in reversed(self.__elems):
            if el == carte:
                self.__elems.remove(el)
        self.__scrie_tot_in_fisier()

    def get_all(self):
        # functia returneaza lista cu toate cartile
        # date de intrare: -
        # date de iesire: o lista cu elemente de tip Carte
        self.__citeste_tot_din_fisier()
        return self.__elems[:]
