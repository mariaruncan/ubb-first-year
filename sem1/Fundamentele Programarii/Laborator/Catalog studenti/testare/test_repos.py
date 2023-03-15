import unittest
from domeniu.entitati import Student, Disciplina, Nota
from erori.exceptii import RepoError
from infrastructura.repos import RepositoryStudenti, RepositoryDiscipline, RepositoryNote


class TestRepositoryStudenti(unittest.TestCase):

    def setUp(self):
        self.repo = RepositoryStudenti()
        self.repo.adauga(Student(664, "Maria"))
        self.repo.adauga(Student(123, "Elena"))

    def test_adauga(self):
        self.repo.adauga(Student(789, "Alex"))
        lista = self.repo.get_all()
        self.assertTrue(lista[2].get_id_stud() == 789)
        self.assertTrue(lista[2].get_nume() == "Alex")
        with self.assertRaisesRegex(RepoError, "student existent!\n"):
            self.repo.adauga(Student(664, "Maria"))

    def test_cauta_dupa_id(self):
        st = self.repo.cauta_dupa_id(664)
        self.assertTrue(st.get_nume() == "Maria")
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.repo.cauta_dupa_id(564)

    def test___len__(self):
        self.assertTrue(len(self.repo._elems) == 2)

    def test_get_all(self):
        lista = self.repo.get_all()
        self.assertTrue(len(lista) == 2)
        self.assertTrue(lista[0].get_id_stud() == 664)
        self.assertTrue(lista[1].get_id_stud() == 123)
        self.assertTrue(lista[0].get_nume() == "Maria")
        self.assertTrue(lista[1].get_nume() == "Elena")

    def test_modifica(self):
        st_nou = Student(664, "Alex")
        self.repo.modifica(st_nou)
        self.assertTrue(self.repo._elems[0].get_nume() == "Alex")
        st_nou = Student(201, "Alex")
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.repo.modifica(st_nou)

    def test_sterge_dupa_id(self):
        self.repo.sterge_dupa_id(664)
        self.assertTrue(len(self.repo._elems) == 1)
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.repo.sterge_dupa_id(664)


class TestRepositoryDiscipline(unittest.TestCase):

    def setUp(self):
        self.repo = RepositoryDiscipline()
        self.repo.adauga(Disciplina(664, "FP", "Maria"))
        self.repo.adauga(Disciplina(123, "Mate", "Elena"))

    def test_adauga(self):
        self.repo.adauga(Disciplina(420, "ASC", "Matei"))
        lista = self.repo.get_all()
        self.assertTrue(lista[2].get_id_disciplina() == 420)
        self.assertTrue(lista[2].get_nume() == "ASC")
        self.assertTrue(lista[2].get_profesor() == "Matei")
        with self.assertRaisesRegex(RepoError, "disciplina existenta!\n"):
            self.repo.adauga(Disciplina(664, "FP", "Maria"))

    def test_cauta_dupa_id(self):
        dis = self.repo.cauta_dupa_id(664)
        self.assertTrue(dis.get_nume() == "FP")
        self.assertTrue(dis.get_profesor() == "Maria")
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.repo.cauta_dupa_id(564)

    def test___len__(self):
        self.assertTrue(len(self.repo._elems) == 2)

    def test_get_all(self):
        lista = self.repo.get_all()
        self.assertTrue(len(lista) == 2)
        self.assertTrue(lista[0].get_id_disciplina() == 664)
        self.assertTrue(lista[1].get_id_disciplina() == 123)
        self.assertTrue(lista[0].get_nume() == "FP")
        self.assertTrue(lista[1].get_nume() == "Mate")
        self.assertTrue(lista[0].get_profesor() == "Maria")
        self.assertTrue(lista[1].get_profesor() == "Elena")

    def test_modifica(self):
        dis_noua = Disciplina(664, "Algebra", "Alex")
        self.repo.modifica(dis_noua)
        self.assertTrue(self.repo._elems[0].get_nume() == "Algebra")
        self.assertTrue(self.repo._elems[0].get_profesor() == "Alex")
        dis_noua = Disciplina(201, "Algebra", "Alex")
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.repo.modifica(dis_noua)

    def test_sterge_dupa_id(self):
        self.repo.sterge_dupa_id(664)
        self.assertTrue(len(self.repo._elems) == 1)
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.repo.sterge_dupa_id(664)


class TestRepositoryNote(unittest.TestCase):

    def setUp(self):
        self.st1 = Student(664, "Maria")
        self.st2 = Student(123, "Elena")
        self.dis1 = Disciplina(231, "FP", "Alex")
        self.dis2 = Disciplina(450, "Mate", "Matei")
        self.repo = RepositoryNote()
        self.repo.adauga(Nota(self.st1, self.dis1, 10))
        self.repo.adauga(Nota(self.st1, self.dis2, 8))
        self.repo.adauga(Nota(self.st2, self.dis1, 7))

    def test___len__(self):
        self.assertTrue(len(self.repo._elems) == 3)

    def test_adauga(self):
        self.repo.adauga(Nota(self.st2, self.dis2, 6))
        self.assertTrue(len(self.repo._elems) == 4)
        with self.assertRaisesRegex(RepoError, "nota existenta!\n"):
            self.repo.adauga(Nota(self.st1, self.dis1, 5))

    def test_get_all(self):
        lista = self.repo.get_all()
        self.assertTrue(len(lista) == 3)
        self.assertTrue(lista[0].get_student().get_id_stud() == 664)
        self.assertTrue(lista[0].get_disciplina().get_id_disciplina() == 231)
        self.assertTrue(lista[0].get_valoare() == 10)

    def test_cauta_note(self):
        lista_note = self.repo.cauta_note(self.st1, Disciplina(0, "", ""))
        self.assertTrue(len(lista_note) == 2)
        lista_note = self.repo.cauta_note(Student(0, ""), self.dis2)
        self.assertTrue(len(lista_note) == 1)
        lista_note = self.repo.cauta_note(Student(456, ""), Disciplina(0, "", ""))
        self.assertTrue(len(lista_note) == 0)

    def test_sterge(self):
        self.repo.sterge(self.st2, Disciplina(0, "", ""))
        lista = self.repo.get_all()
        self.assertTrue(len(lista) == 2)
        self.repo.sterge(Student(0, ""), self.dis1)
        lista = self.repo.get_all()
        self.assertTrue(len(lista) == 1)
        self.repo.sterge(Student(456, ""), Disciplina(0, "", ""))
        lista = self.repo.get_all()
        self.assertTrue(len(lista) == 1)

    def test_modifica(self):
        self.repo.modifica(Student(664, "Matei"), Disciplina(0, "", ""))
        lista = self.repo.get_all()
        self.assertTrue(lista[0].get_student().get_nume() == "Matei")
        self.assertTrue(lista[1].get_student().get_nume() == "Matei")
        self.repo.modifica(Student(0, ""), Disciplina(450, "Analiza", "Alex"))
        self.assertTrue(lista[1].get_disciplina().get_nume() == "Analiza")
        self.assertTrue(lista[1].get_disciplina().get_profesor() == "Alex")
