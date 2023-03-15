from erori.exceptii import ValidError


class ValidatorStudent(object):

    @staticmethod
    def valideaza(student):
        # functia verifica daca un student este valid
        # date de intrare: student
        # date de iesire: -
        # ridica exceptie de tipul ValidError cu mesajul:
        #       - "id invalid!\n", daca id-ul este < 1
        #       - "nume invalid!\n", daca numele este vid
        erori = ""
        if student.get_id_stud() < 1:
            erori += "id invalid!\n"
        if student.get_nume() == "":
            erori += "nume invalid!\n"
        if len(erori) > 0:
            raise ValidError(erori)


class ValidatorDisciplina(object):

    @staticmethod
    def valideaza(disciplina):
        # functia verifica daca o disciplina este valida
        # date de intrare: disciplina
        # date de iesire: -
        # ridica exceptie de tipul ValidError cu mesajul:
        #       - "id invalid!\n", daca id este < 1
        #       - "nume invalid!\n", daca nume este vid
        #       - "profesor invalid!\n", daca profesor este vid
        erori = ""
        if disciplina.get_id_disciplina() < 1:
            erori += "id invalid!\n"
        if disciplina.get_nume() == "":
            erori += "nume invalid!\n"
        if disciplina.get_profesor() == "":
            erori += "profesor invalid!\n"
        if len(erori) > 0:
            raise ValidError(erori)


class ValidatorNota(object):

    @staticmethod
    def valideaza(nota):
        # functia verifica daca o nota este valida
        # date de intrare: nota
        # date de iesire: -
        # ridica exceptie de tipul ValidError cu mesajul:
        #       - "valoare invalida!\n", daca valoarea nu face parte din intervalul [1, 10]
        erori = ""
        if not 1 <= nota.get_valoare() <= 10:
            erori += "valoare invalida!\n"
        if len(erori) > 0:
            raise ValidError(erori)


class ValidatorMedie(object):

    @staticmethod
    def valideaza(val):
        if not 0 <= val <= 10:
            raise ValidError("valoare numerica invalida!\n")
