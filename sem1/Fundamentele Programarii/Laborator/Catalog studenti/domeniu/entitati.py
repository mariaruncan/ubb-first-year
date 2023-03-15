class Student(object):
    # tip abstract de data pentru un student

    def __init__(self, id_stud, nume):
        # functia initializeaza un student
        # date de intrare: id_stud - int, nume - string
        self.__id_stud = id_stud
        self.__nume = nume

    def get_id_stud(self):
        # metoda getter, returneaza id-ul studentului (id_stud)
        # date de intrare: -
        # date de iesire: id_stud (id-ul studentului - int)
        return self.__id_stud

    def get_nume(self):
        # metoda getter, returneaza numele studentului (nume)
        # date de intrare: -
        # date de iesire: nume (numele studentului - string)
        return self.__nume

    def set_nume(self, value):
        # metoda setter, seteaza numele studentului (nume) cu noua valoare (value)
        # date de intrare: value - string
        # date de iesire: -
        self.__nume = value

    def __str__(self):
        # functia returneaza o reprezentare string a obiectului de tip Student
        # date de intrare: -
        # date de iesire: reprezentare string a unui student
        return str(self.__id_stud) + " " + self.__nume

    def __eq__(self, other):
        # functia verifica daca doi studenti sunt egali
        # date de intrare: -
        # date de iesire: True, daca studentii sunt egali
        #                 False, in caz contrar
        return self.__id_stud == other.__id_stud


class Disciplina(object):
    # tip abstract de data pentru un student

    def __init__(self, id_disciplina, nume, profesor):
        # functia initializeaza o disciplina
        # date de intrare: id_disciplina - int, nume - string, profesor - string
        self.__id_disciplina = id_disciplina
        self.__nume = nume
        self.__profesor = profesor

    def get_id_disciplina(self):
        # metoda getter, returneaza id-ul disciplinei (id_disciplina)
        # date de intrare: -
        # date de iesire: id_disciplina (id-ul disciplinei - int)
        return self.__id_disciplina

    def get_nume(self):
        # metoda getter, returneaza numele disciplinei (nume)
        # date de intrare: -
        # date de iesire: nume (numele disciplinei - string)
        return self.__nume

    def get_profesor(self):
        # metoda getter, returneaza profesorul disciplinei (profesor)
        # date de intrare: -
        # date de iesire: profesor (profesorul disciplinei - string)
        return self.__profesor

    def set_nume(self, value):
        # metoda setter, seteaza numele disciplinei (nume) cu noua valoare (value)
        # date de intrare: value - string
        # date de iesire: -
        self.__nume = value

    def set_profesor(self, value):
        # metoda setter, seteaza profesorul disciplinei (profesor) cu noua valoare (value)
        # date de intrare: value - string
        # date de iesire: -
        self.__profesor = value

    def __str__(self):
        # functia returneaza o reprezentare string a obiectului de tip Disciplina
        # date de intrare: -
        # date de iesire: reprezentare string a unei discipline
        return str(self.__id_disciplina) + " " + self.__nume + " " + self.__profesor

    def __eq__(self, other):
        # functia verifica daca doua discipline sunt egale
        # date de intrare: -
        # date de iesire: True, daca disciplinele sunt egale
        #                 False, in caz contrar
        return self.__id_disciplina == other.__id_disciplina


class Nota(object):
    # tip abstract de data pentru o nota

    def __init__(self, student, disciplina, valoare):
        # functia initializeaza o nota
        # date de intrare: id_nota - int, student - Student, disciplina - Disciplina, valoare - int
        self.__student = student
        self.__disciplina = disciplina
        self.__valoare = valoare

    def get_student(self):
        # metoda getter, returneaza studentul notei (student)
        # date de intrare: -
        # date de iesire: student - Student
        return self.__student

    def get_disciplina(self):
        # metoda getter, returneaza disciplina notei (disciplina)
        # date de intrare: -
        # date de iesire: disciplina - Disciplina
        return self.__disciplina

    def get_valoare(self):
        # metoda getter, returneaza valoarea notei (valoare)
        # date de intrare: -
        # date de iesire: valoare - int
        return self.__valoare

    def set_student(self, value):
        # metoda setter, seteaza studentul notei cu noua valoare value
        # date de intrare: value - Student
        # date de iesire: -
        self.__student = value

    def set_disciplina(self, value):
        # metoda setter, seteaza disciplina notei cu noua valoare value
        # date de intrare: value - Disciplina
        # date de iesire: -
        self.__disciplina = value

    def __str__(self):
        # functia returneaza o reprezentare string a obiectului de tip Nota
        # date de intrare: -
        # date de iesire: reprezentare string a unei note prin scriere id-ului notei, numele studentului,
        # numele disciplinei si valoarea notei
        return self.__student.get_nume() + " " + self.__disciplina.get_nume() + " " + str(self.__valoare)

    def __eq__(self, other):
        # functia verifica daca doua note sunt egale
        # date de intrare: -
        # date de iesire: True, daca notele sunt egale
        #                 False, in caz contrar
        return self.__student.get_id_stud() == other.__student.get_id_stud() and \
               self.__disciplina.get_id_disciplina() == other.__disciplina.get_id_disciplina()


class MedieDTO(object):
    def __init__(self, student, medie):
        self.__student = student
        self.__medie = medie

    def get_student(self):
        return self.__student

    def get_medie(self):
        return self.__medie
