from business.servicii import ServiceCarti
from domain.entitati import Carte
from infrastructura.file_repo import RepositoryCarti


class Teste(object):

    @staticmethod
    def __test_entitati():
        c1 = Carte(23, "abcd", "def", 1900, 90.4)
        assert(c1.get_id() == 23)
        assert(c1.get_titlu() == "abcd")
        assert(c1.get_autor() == "def")
        assert(abs(c1.get_pret() - 90.4) <= 0)
        c2 = Carte(23, "", "", 0, 0)
        assert(c1 == c2)
        c3 = Carte(57, "", "", 0, 0)
        assert (c1 != c3)
        assert(str(c1) == "23 abcd def 1900 90.4")

    @staticmethod
    def __test_repository_carti():
        repo = RepositoryCarti("test.txt")
        c1 = Carte(56, "xyz", "sqrt", 2001, 75)
        c2 = Carte(63, "gsd", "dfa", 2008, 56)
        repo.adauga(c1)
        repo.adauga(c2)
        try:
            repo.adauga(c1)
        except Exception as ex:
            assert(str(ex) == "Carte existenta!")
        lista = repo.get_all()
        assert(len(lista) == 2)
        assert(lista[1] == c2)
        repo.sterge_carte(c1)
        lista = repo.get_all()
        assert(len(lista) == 1)
        repo.sterge_carte(c1)
        lista = repo.get_all()
        assert (len(lista) == 1)

    @staticmethod
    def __test_service_carti():
        srv = ServiceCarti(RepositoryCarti("test.txt"), ["", -1], [])
        srv.adauga_carte(45, "gssss", "def", 1900, 34.5)
        lista = srv.filtrare()
        assert(len(lista) == 2)
        assert(srv.modifica_filtru("gs", 40) == ["gs", 40])
        lista = srv.filtrare()
        assert(len(lista) == 1)
        srv.sterge_carte_cifra(8)
        srv.modifica_filtru("", -1)
        lista = srv.filtrare()
        assert(len(lista) == 1)
        srv.undo()
        lista = srv.filtrare()
        assert(len(lista) == 2)

    def ruleaza_teste(self):
        self.__test_entitati()
        self.__test_repository_carti()
        self.__test_service_carti()
