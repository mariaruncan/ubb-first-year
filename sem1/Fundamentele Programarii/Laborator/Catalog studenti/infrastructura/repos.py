from domeniu.entitati import Student, Disciplina
from erori.exceptii import RepoError


class RepositoryStudenti(object):
    # tip abstract de data pentru repo_studenti

    def __init__(self):
        # functia initializeaza un obiect de tip RepositoryStudenti
        # date de intrare: -
        self._elems = []

    def adauga(self, student):
        # functia adauga un student intr-un obiect de tip RepositoryStudenti
        # date de intrare: student - Student
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "student existent!\n", daca studentul se afla deja in repo_studenti
        if student in self._elems:
            raise RepoError("student existent!\n")
        self._elems.append(student)

    def cauta_dupa_id(self, id_stud):
        # functia cauta studentul cu id-ul id_stud intr-un obiect de tip RepositoryStudenti si il returneaza
        # date de intrare: id_stud - int
        # date de iesire: el - unde el este studentul cu id-ul id_stud
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "student inexistent!\n", daca studentul cu id-ul id_stud nu se afla in repo_studenti
        for el in self._elems:
            if el.get_id_stud() == id_stud:
                return el
        raise RepoError("student inexistent!\n")

    def __len__(self):
        # functia returneaza lungimea unui obiect de tip RepositoryStudenti
        # date de intrare: -
        # date de iesire: len(repo_stud) - int
        return len(self._elems)

    def get_all(self):
        # functia returneaza o copie a obiectului de tip RepositoryStudenti
        # date de intrare: -
        # date de iesire: repo_stud[:]
        return self._elems[:]

    def modifica(self, student_nou):
        # functia modifica studentul care are acelasi id ca studentul student_nou
        # date de intrare: student_nou - Student
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "student inexistent!\n", daca nu exista un student cu id-ul studentului student_nou
        if student_nou not in self._elems:
            raise RepoError("student inexistent!\n")
        for i in range(len(self._elems)):
            if self._elems[i] == student_nou:
                self._elems[i] = student_nou
                return

    def sterge_dupa_id(self, id_stud):
        # functia sterge dintr-un obiect de tip RepositoryStudenti studentul care are id-ul id_stud
        # date de intrare: id_stud - int
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "student inexistent!\n", daca nu exista un student cu id-ul id_stud
        for el in self._elems:
            if el.get_id_stud() == id_stud:
                self._elems.remove(el)
                return
        raise RepoError("student inexistent!\n")


class RepositoryDiscipline(object):
    # tip abstract de data pentru un repo_discipline

    def __init__(self):
        # functia initializeaza un obiect de tip RepositoryDiscipline
        # date de intrare: -
        self._elems = []

    def adauga(self, disciplina):
        # functia adauga o discipline intr-un obiect de tip RepositoryDiscipline
        # date de intrare: discipline - Disciplina
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "disciplina existenta!\n", daca disciplina se afla deja in repo_discipline
        if disciplina in self._elems:
            raise RepoError("disciplina existenta!\n")
        self._elems.append(disciplina)

    def cauta_dupa_id(self, id_disciplina):
        # functia cauta disciplina cu id-ul id_dsiciplina intr-un obiect de tip RepositoryDiscipline si o returneaza
        # date de intrare: id_disciplina - int
        # date de iesire: el - unde el este disciplina cu id-ul id_disciplina
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "disciplina inexistenta!\n", daca disciplina cu id-ul id_disciplina nu se afla in repo_discipline
        for el in self._elems:
            if el.get_id_disciplina() == id_disciplina:
                return el
        raise RepoError("disciplina inexistenta!\n")

    def __len__(self):
        # functia returneaza lungimea unui obiect de tip RepositoryDiscipline
        # date de intrare: -
        # date de iesire: len(repo_discipline) - int
        return len(self._elems)

    def get_all(self):
        # functia returneaza o copie a obiectului de tip RepositoryDiscipline
        # date de intrare: -
        # date de iesire: repo_discipline[:]
        return self._elems[:]

    def modifica(self, disciplina_noua):
        # functia modifica disciplina care are acelasi id ca disciplina disciplina_noua
        # date de intrare: disciplina_noua - Disciplina
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "disciplina inexistenta!\n", daca nu exista o disciplina cu id-ul diaciplinei disciplina_noua
        for i in range(len(self._elems)):
            if self._elems[i] == disciplina_noua:
                self._elems[i] = disciplina_noua
                return
        raise RepoError("disciplina inexistenta!\n")

    def sterge_dupa_id(self, id_disciplina):
        # functia sterge dintr-un obiect de tip RepositoryDiscipline disciplina care are id-ul id_disciplina
        # date de intrare: id_disciplina - int
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "disciplina inexistenta!\n", daca nu exista o disciplina cu id-ul id_disciplina
        for el in self._elems:
            if el.get_id_disciplina() == id_disciplina:
                self._elems.remove(el)
                return
        raise RepoError("disciplina inexistenta!\n")


class RepositoryNote(object):
    # tip abstract de data pentru un repo_note

    def __init__(self):
        # functia initializeaza un obiect de tip RepositoryDiscipline
        # date de intrare: -
        self._elems = []

    def __len__(self):
        # functia returneaza lungimea unui obiect de tip RepositoryDiscipline
        # date de intrare: -
        # date de iesire: len(repo_note) - int
        return len(self._elems)

    def adauga(self, nota):
        # functia adauga o nota intr-un obiect de tip RepositoryNote
        # date de intrare: nota - Nota
        # date de iesire: -
        # ridica exceptie de tipul RepoError cu mesajul:
        #       - "nota existenta!\n", daca nota se afla deja in repo_note
        if nota in self._elems:
            raise RepoError("nota existenta!\n")
        self._elems.append(nota)

    def get_all(self):
        # functia returneaza o copie a obiectului de tip RepositoryNote
        # date de intrare: -
        # date de iesire: copie a listei repo_note
        return self._elems[:]

    def cauta_note(self, student, disciplina):
        # functia returneaza o lista cu notela unui student sau o lista cu notele de la o anumita disciplina
        # date de intrare: student, ""    sau     "", disciplina
        # date de iesire: lista corespunzatoare de note
        lista_note = []
        if student != Student(0, ""):
            for el in self._elems:
                if el.get_student() == student:
                    lista_note.append(el)
            return lista_note
        if disciplina != Disciplina(0, "", ""):
            for el in self._elems:
                if el.get_disciplina() == disciplina:
                    lista_note.append(el)
            return lista_note

    def sterge(self, student, disciplina):
        # functia sterge notele care au un student/disciplina data
        # date de intrare: sttudent, ""    sau    "", disciplina
        # date de iesire: -
        if student != Student(0, ""):
            for el in self._elems:
                if el.get_student() == student:
                    self._elems.remove(el)
        if disciplina != Disciplina(0, "", ""):
            for el in self._elems:
                if el.get_disciplina() == disciplina:
                    self._elems.remove(el)

    def modifica(self, student, disciplina):
        # functia modifica studentul/disciplina unor note
        # date de intrare: student, ""   sau    "", disciplina
        # date de iesire: -
        if student != Student(0, ""):
            for el in self._elems:
                if el.get_student() == student:
                    el.set_student(student)
        if disciplina != Disciplina(0, "", ""):
            for el in self._elems:
                if el.get_disciplina() == disciplina:
                    el.set_disciplina(disciplina)
