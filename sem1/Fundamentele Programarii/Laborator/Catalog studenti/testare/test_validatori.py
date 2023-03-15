import unittest
from domeniu.entitati import Student, Disciplina, Nota
from erori.exceptii import ValidError
from validare.validatori import ValidatorStudent, ValidatorDisciplina, ValidatorNota, ValidatorMedie


class TestValidatorStudent(unittest.TestCase):

    def setUp(self):
        self.valid = ValidatorStudent()
        self.st1 = Student(664, "Maria")
        self.st2 = Student(-123, "Maria")
        self.st3 = Student(-123, "")

    def test_valideaza(self):
        self.valid.valideaza(self.st1)
        with self.assertRaisesRegex(ValidError, "id invalid!\n"):
            self.valid.valideaza(self.st2)
        with self.assertRaisesRegex(ValidError, "id invalid!\nnume invalid!\n"):
            self.valid.valideaza(self.st3)


class TestValidatorDisciplina(unittest.TestCase):

    def setUp(self):
        self.valid = ValidatorDisciplina()
        self.dis1 = Disciplina(644, "FP", "Maria")
        self.dis2 = Disciplina(-664, "Mate", "Elena")
        self.dis3 = Disciplina(0, "", "")

    def test_valideaza(self):
        self.valid.valideaza(self.dis1)
        with self.assertRaisesRegex(ValidError, "id invalid!\n"):
            self.valid.valideaza(self.dis2)
        with self.assertRaisesRegex(ValidError, "id invalid!\nnume invalid!\nprofesor invalid!\n"):
            self.valid.valideaza(self.dis3)


class TestValidatorNota(unittest.TestCase):

    def setUp(self):
        self.valid = ValidatorNota()
        self.n1 = Nota("", "", 8)
        self.n2 = Nota("", "", 0)
        self.n3 = Nota("", "", -6)

    def test_valideaza(self):
        self.valid.valideaza(self.n1)
        with self.assertRaisesRegex(ValidError, "valoare invalida!\n"):
            self.valid.valideaza(self.n2)
        with self.assertRaisesRegex(ValidError, "valoare invalida!\n"):
            self.valid.valideaza(self.n3)


class TestValidatorMedie(unittest.TestCase):

    def setUp(self):
        self.valid = ValidatorMedie()
        self.m1 = 8.75
        self.m2 = 10
        self.m3 = 0
        self.m4 = -6.45

    def test_valideaza(self):
        self.valid.valideaza(self.m1)
        self.valid.valideaza(self.m2)
        self.valid.valideaza(self.m3)
        with self.assertRaisesRegex(ValidError, "valoare numerica invalida!\n"):
            self.valid.valideaza(self.m4)
