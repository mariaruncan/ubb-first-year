from domain.entitati import Carte


class ServiceCarti(object):

    def __init__(self, repo, filtru, lista_undo):
        self.__repo = repo
        self.__filtru = filtru
        self.__lista_undo = lista_undo

    def adauga_carte(self, id_carte, titlu, autor, an_aparitie, pret):
        # functia construieste un obiect de tip Carte pe care il adauga in lista
        # date de intrare: id_carte, an_aparitie - int, titlu, autor - string, pret - float
        # date de iesire: -
        # ridica exceptie de tipul Exception cu mesajul "Carte existenta!" daca o carte cu acelasi id se afla deja in
        # lista
        carte = Carte(id_carte, titlu, autor, an_aparitie, pret)
        self.__repo.adauga(carte)

    def sterge_carte_cifra(self, cif):
        # functia sterge cartile din lista care au in anul de aparitie o cifra data
        # date de intrare: cif - int, lista_undo - o lista cu starile anterioare ale listei de carti
        # date de iesire: -
        lista = self.__repo.get_all()
        self.__lista_undo.append(self.__cloneaza_lista(lista))
        for carte in lista:
            an = carte.get_an_aparitie()
            ok = False
            while an != 0 and not ok:
                uc = an % 10
                if uc == cif:
                    self.__repo.sterge_carte(carte)
                    ok = True
                an = an // 10

    def filtrare(self):
        # functia filtreaza lista de carti
        # daca filtrul este de forma ["", -1], atunci se returneaza toata lista
        # altfel se returneaza o lista formata doar din elementele ca au in titlu prima componenta din filtru si pretul
        # lor este mai mic decat a doua componenta din filtru
        # date de intrare: filtru - o lista ce are pe prima pozitie un string si pe a doua un numar real
        # date de iesire: lista de obiecte de tipul Carte care corespund filtrului
        if self.__filtru[0] == "" and self.__filtru[1] == -1:
            return self.__repo.get_all()
        else:
            rezultat = []
            lista = self.__repo.get_all()
            for carte in lista:
                if self.__filtru[0] in carte.get_titlu() and carte.get_pret() < self.__filtru[1]:
                    rezultat.append(carte)
            return rezultat

    def modifica_filtru(self, text, pret_max):
        # functia modifica filtrul
        # date de intrare: text - string, pret_max - float
        # date de iesire: [text, pret_max] - o lista
        self.__filtru = [text, pret_max]
        return self.__filtru

    def undo(self):
        # functia reface ultima operatie de stergere
        # se sterg toate datele existente in fisier si se rescrie fisierul cu ultima stare a listei de carti
        lista = self.__repo.get_all()
        for carte in lista:
            self.__repo.sterge_carte(carte)
        lista = self.__lista_undo[-1]
        for carte in lista:
            self.__repo.adauga(carte)
        del self.__lista_undo[-1]

    def __cloneaza_lista(self, lista):
        # functia returneaza o copie a listei lista
        # date de intrare: lista - o lista de carti
        # date de iesire: rezultat - copia listei
        rezultat = []
        for carte in lista:
            el = self.__cloneaza_carte(carte)
            rezultat.append(el)
        return rezultat

    @staticmethod
    def __cloneaza_carte(carte):
        # functia returneaza o copie a unui obiect de tip carte
        # date de intrare: carte - Carte
        # date de iesire: o copie a obiectului carte
        return Carte(carte.get_id(), carte.get_titlu(), carte.get_autor(), carte.get_an_aparitie(), carte.get_pret())

    def get_filtru(self):
        # functia returneaza filtrul curent
        # date de intrare: -
        # date de iesire: o lista reprezentand filtrul cu prima componenta un string si cea de a doua un nr real
        return self.__filtru
