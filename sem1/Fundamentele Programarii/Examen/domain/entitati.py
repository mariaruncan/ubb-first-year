class Carte(object):
    # clasa pentru un obiect de tip carte care are ca atribute id, titlu, autor, anAparitie si pret
    def __init__(self, id_carte, titlu, autor, an, pret):
        self.__id = id_carte
        self.__titlu = titlu
        self.__autor = autor
        self.__anAparitie = an
        self.__pret = pret

    def get_id(self):
        return self.__id

    def get_titlu(self):
        return self.__titlu

    def get_autor(self):
        return self.__autor

    def get_an_aparitie(self):
        return self.__anAparitie

    def get_pret(self):
        return self.__pret

    def __eq__(self, other):
        # functia verifica daca doua carti sunt egale prin compararea id-urilor acestora
        # date de intrare: -
        # date de iesire: True, daca cartile au acelasi id
        #                 False, in caz contrar
        return self.get_id() == other.get_id()

    def __str__(self):
        # date de intrare: -
        # date de iesire: un string corespunzator unei carti prin inlantuirea atributelor sale separate prin spatiu
        return str(self.get_id()) + " " + self.get_titlu() + " " + self.get_autor() + " " + \
               str(self.get_an_aparitie()) + " " + str(self.get_pret())
