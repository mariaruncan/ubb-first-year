import unittest
from domeniu.entitati import Student, Disciplina, Nota, MedieDTO


class TestStudent(unittest.TestCase):

    def setUp(self):
        self.st1 = Student(664, "Maria")
        self.st2 = Student(546, "Elena")

    def test_get_id_stud(self):
        self.assertEqual(self.st1.get_id_stud(), 664)
        self.assertEqual(self.st2.get_id_stud(), 546)

    def test_get_nume(self):
        self.assertEqual(self.st1.get_nume(), "Maria")
        self.assertEqual(self.st2.get_nume(), "Elena")

    def test_set_nume(self):
        self.st1.set_nume("Adrian")
        self.assertEqual(self.st1.get_nume(), "Adrian")
        self.st2.set_nume("Matei")
        self.assertEqual(self.st2.get_nume(), "Matei")

    def test___str__(self):
        self.assertEqual(str(self.st1), "664 Maria")
        self.assertEqual(str(self.st2), "546 Elena")

    def test___eq__(self):
        self.assertFalse(self.st1 == self.st2)
        st3 = Student(664, "Alex")
        self.assertTrue(self.st1 == st3)


class TestDisciplina(unittest.TestCase):

    def setUp(self):
        self.dis1 = Disciplina(664, "FP", "Maria")
        self.dis2 = Disciplina(546, "Mate", "Elena")

    def test_get_id_disciplina(self):
        self.assertEqual(self.dis1.get_id_disciplina(), 664)
        self.assertEqual(self.dis2.get_id_disciplina(), 546)

    def test_get_nume(self):
        self.assertEqual(self.dis1.get_nume(), "FP")
        self.assertEqual(self.dis2.get_nume(), "Mate")

    def test_get_profesor(self):
        self.assertEqual(self.dis1.get_profesor(), "Maria")
        self.assertEqual(self.dis2.get_profesor(), "Elena")

    def test_set_nume(self):
        self.dis1.set_nume("Info")
        self.assertEqual(self.dis1.get_nume(), "Info")
        self.dis2.set_nume("Algebra")
        self.assertEqual(self.dis2.get_nume(), "Algebra")

    def test_set_profesor(self):
        self.dis1.set_profesor("Adrian")
        self.assertEqual(self.dis1.get_profesor(), "Adrian")
        self.dis2.set_profesor("Matei")
        self.assertEqual(self.dis2.get_profesor(), "Matei")

    def test___str__(self):
        self.assertEqual(str(self.dis1), "664 FP Maria")
        self.assertEqual(str(self.dis2), "546 Mate Elena")

    def test___eq__(self):
        self.assertFalse(self.dis1 == self.dis2)
        dis3 = Disciplina(664, "Analiza", "George")
        self.assertTrue(self.dis1 == dis3)


class TestNota(unittest.TestCase):

    def setUp(self):
        self.n1 = Nota(Student(664, "Gigi"), Disciplina(123, "Algebra", "Alex"), 10)
        self.n2 = Nota(Student(546, "Matei"), Disciplina(987, "ASC", "Adrian"), 8)

    def test_get_student(self):
        self.assertEqual(self.n1.get_student(), Student(664, ""))
        self.assertEqual(self.n2.get_student(), Student(546, ""))

    def test_get_disciplina(self):
        self.assertEqual(self.n1.get_disciplina(), Disciplina(123, "", ""))
        self.assertEqual(self.n2.get_disciplina(), Disciplina(987, "", ""))

    def test_get_valoare(self):
        self.assertEqual(self.n1.get_valoare(), 10)
        self.assertEqual(self.n2.get_valoare(), 8)

    def test_set_student(self):
        self.n1.set_student(Student(664, "Maria"))
        self.assertEqual(self.n1.get_student().get_id_stud(), 664)
        self.assertEqual(self.n1.get_student().get_nume(), "Maria")
        self.n2.set_student(Student(546, "Elena"))
        self.assertEqual(self.n2.get_student().get_id_stud(), 546)
        self.assertEqual(self.n2.get_student().get_nume(), "Elena")

    def test_set_disciplina(self):
        self.n1.set_disciplina(Disciplina(123, "FP", "Maria"))
        self.assertEqual(self.n1.get_disciplina().get_id_disciplina(), 123)
        self.assertEqual(self.n1.get_disciplina().get_nume(), "FP")
        self.assertEqual(self.n1.get_disciplina().get_profesor(), "Maria")
        self.n2.set_disciplina(Disciplina(987, "Mate", "Elena"))
        self.assertEqual(self.n2.get_disciplina().get_id_disciplina(), 987)
        self.assertEqual(self.n2.get_disciplina().get_nume(), "Mate")
        self.assertEqual(self.n2.get_disciplina().get_profesor(), "Elena")

    def test___str__(self):
        self.assertEqual(str(self.n1), "Gigi Algebra 10")
        self.assertEqual(str(self.n2), "Matei ASC 8")

    def test___eq__(self):
        self.assertFalse(self.n1 == self.n2)
        n3 = Nota(Student(664, ""), Disciplina(123, "", ""), 3)
        self.assertTrue(self.n1 == n3)


class TestMedieDTO(unittest.TestCase):

    def setUp(self):
        self.el1 = MedieDTO(Student(664, "Maria"), 8.75)
        self.el2 = MedieDTO(Student(123, "Elena"), 7.33)

    def test_get_student(self):
        self.assertEqual(self.el1.get_student(), Student(664, ""))
        self.assertEqual(self.el2.get_student(), Student(123, ""))

    def test_get_medie(self):
        self.assertEqual(self.el1.get_medie(), 8.75)
        self.assertEqual(self.el2.get_medie(), 7.33)
