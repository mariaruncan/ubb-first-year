import unittest
from business.servicii import ServiceStudenti, ServiceDiscipline, ServiceNote
from domeniu.entitati import Student, Disciplina
from validare.validatori import ValidatorStudent, ValidatorDisciplina, ValidatorNota
from infrastructura.repos import RepositoryStudenti, RepositoryDiscipline, RepositoryNote
from erori.exceptii import RepoError, ValidError


class TestServiceStudenti(unittest.TestCase):

    def setUp(self):
        valid = ValidatorStudent()
        repo = RepositoryStudenti()
        self.srv = ServiceStudenti(valid, repo)
        self.srv.adauga_student(664, "Maria")
        self.srv.adauga_student(123, "Elena")

    def test_adauga_student(self):
        self.srv.adauga_student(450, "Alex")
        with self.assertRaisesRegex(ValidError, "id invalid!\n"):
            self.srv.adauga_student(-20, "Alex")
        with self.assertRaisesRegex(ValidError, "id invalid!\nnume invalid!\n"):
            self.srv.adauga_student(0, "")
        with self.assertRaisesRegex(RepoError, "student existent!\n"):
            self.srv.adauga_student(664, "Carla")

    def test_cauta_student(self):
        st = self.srv.cauta_student(664)
        self.assertTrue(st.get_nume() == "Maria")
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.srv.cauta_student(450)

    def test_get_studenti(self):
        lista = self.srv.get_studenti()
        self.assertTrue(len(lista) == 2)
        self.assertTrue(lista[0].get_id_stud() == 664)
        self.assertTrue(lista[1].get_id_stud() == 123)


class TestServiceDiscipline(unittest.TestCase):

    def setUp(self):
        valid = ValidatorDisciplina()
        repo = RepositoryDiscipline()
        self.srv = ServiceDiscipline(valid, repo)
        self.srv.adauga_disciplina(664, "FP", "Maria")
        self.srv.adauga_disciplina(123, "Mate", "Elena")

    def test_adauga_disciplina(self):
        self.srv.adauga_disciplina(450, "Mate", "Alex")
        with self.assertRaisesRegex(ValidError, "id invalid!\n"):
            self.srv.adauga_disciplina(-20, "Mate", "Alex")
        with self.assertRaisesRegex(ValidError, "id invalid!\nnume invalid!\nprofesor invalid!\n"):
            self.srv.adauga_disciplina(0, "", "")
        with self.assertRaisesRegex(RepoError, "disciplina existenta!\n"):
            self.srv.adauga_disciplina(664, "ASC", "Carla")

    def test_cauta_disciplina(self):
        dis = self.srv.cauta_disciplina(664)
        self.assertTrue(dis.get_nume() == "FP")
        self.assertTrue(dis.get_profesor() == "Maria")
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.srv.cauta_disciplina(450)

    def test_get_discipline(self):
        lista = self.srv.get_discipline()
        self.assertTrue(len(lista) == 2)
        self.assertTrue(lista[0].get_id_disciplina() == 664)
        self.assertTrue(lista[1].get_id_disciplina() == 123)


class TestServiceNote(unittest.TestCase):

    def setUp(self):
        valid_note = ValidatorNota()
        valid_stud = ValidatorStudent()
        valid_dis = ValidatorDisciplina()
        repo_note = RepositoryNote()
        repo_stud = RepositoryStudenti()
        repo_stud.adauga(Student(664, "Maria"))
        repo_stud.adauga(Student(123, "Elena"))
        repo_dis = RepositoryDiscipline()
        repo_dis.adauga(Disciplina(456, "FP", "Matei"))
        repo_dis.adauga(Disciplina(201, "Mate", "Alex"))
        self.srv = ServiceNote(valid_note, valid_stud, valid_dis, repo_note, repo_stud, repo_dis)
        self.srv.adauga_nota(664, 456, 6)
        self.srv.adauga_nota(123, 201, 10)
        self.srv.adauga_nota(123, 456, 8)

    def test_adauga_nota(self):
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.srv.adauga_nota(345, 201, 7)
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.srv.adauga_nota(664, 988, 3)
        with self.assertRaisesRegex(ValidError, "valoare invalida!\n"):
            self.srv.adauga_nota(664, 201, -3)
        with self.assertRaisesRegex(RepoError, "nota existenta!\n"):
            self.srv.adauga_nota(664, 456, 10)
        self.srv.adauga_nota(664, 201, 4)

    def test_sterge_student(self):
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.srv.sterge_student(200)
        self.srv.sterge_student(664)

    def test_modifica_student(self):
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.srv.modifica_student(200, "Alina")
        with self.assertRaisesRegex(ValidError, "nume invalid!\n"):
            self.srv.modifica_student(664, "")
        self.srv.modifica_student(664, "Alina")

    def test_sterge_disciplina(self):
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.srv.sterge_disciplina(200)
        self.srv.sterge_disciplina(201)

    def test_modifica_disciplina(self):
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.srv.modifica_disciplina(200, "ASC", "Maria")
        with self.assertRaisesRegex(ValidError, "nume invalid!\n"):
            self.srv.modifica_disciplina(201, "", "Maria")
        self.srv.modifica_disciplina(201, "ASC", "Alina")

    def test_get_note(self):
        lista = self.srv.get_note()
        self.assertTrue(len(lista) == 3)

    def test_get_note_student(self):
        with self.assertRaisesRegex(RepoError, "student inexistent!\n"):
            self.srv.get_note_student(200)
        lista = self.srv.get_note_student(664)
        self.assertTrue(len(lista) == 1)

    def test_get_note_disciplina(self):
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.srv.get_note_disciplina(200)
        lista = self.srv.get_note_disciplina(201)
        self.assertTrue(len(lista) == 1)

    def test_note_disciplina_sortate(self):
        with self.assertRaisesRegex(RepoError, "disciplina inexistenta!\n"):
            self.srv.note_disciplina_sortate(200)
        lista = self.srv.note_disciplina_sortate(456)
        self.assertTrue(len(lista) == 2)
        self.assertTrue(lista[0].get_valoare() == 8)
        self.assertTrue(lista[1].get_valoare() == 6)

    def test_sortare_stud_dupa_medie(self):
        lista = self.srv.sortare_stud_dupa_medie()
        self.assertTrue(len(lista) == 2)
        self.assertTrue(lista[0].get_student().get_id_stud() == 123)
        self.assertTrue(lista[1].get_student().get_id_stud() == 664)

    def test_medie_in_interval(self):
        with self.assertRaisesRegex(ValidError, "valoare numerica invalida!\n"):
            self.srv.medie_in_interval(-10, 9.6)
        with self.assertRaisesRegex(ValidError, "valoare numerica invalida!\n"):
            self.srv.medie_in_interval(1, 12.3)
        lista = self.srv.medie_in_interval(9.50, 10)
        self.assertTrue(len(lista) == 0)
        lista = self.srv.medie_in_interval(2.5, 10)
        self.assertTrue(len(lista) == 2)
